/* Job execution and handling for GNU Make.
Copyright (C) 1988-2023 Free Software Foundation, Inc.
This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

GNU Make is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include "makeint.h"

#include <assert.h>
#include <string.h>

#include "job.h"
#include "debug.h"
#include "filedef.h"
#include "commands.h"
#include "variable.h"
#include "os.h"
#include "dep.h"
#include "shuffle.h"

/* Default shell to use.  */
const char *default_shell = "/bin/sh";
int batch_mode_shell = 0;

#if defined (HAVE_FCNTL_H)
# include <fcntl.h>
#endif

#if defined (HAVE_SYS_WAIT_H) || defined (HAVE_UNION_WAIT)
# include <sys/wait.h>
#endif

#ifdef HAVE_WAITPID
# define WAIT_NOHANG(status)    waitpid (-1, (status), WNOHANG)
#else   /* Don't have waitpid.  */
# ifdef HAVE_WAIT3
#  ifndef wait3
extern int wait3 ();
#  endif
#  define WAIT_NOHANG(status)   wait3 ((status), WNOHANG, (struct rusage *) 0)
# endif /* Have wait3.  */
#endif /* Have waitpid.  */

#ifdef USE_POSIX_SPAWN
# include <spawn.h>
# include "findprog.h"
#endif

#if !defined (wait) && !defined (POSIX)
int wait ();
#endif

#ifndef HAVE_UNION_WAIT

# define WAIT_T int

# ifndef WTERMSIG
#  define WTERMSIG(x) ((x) & 0x7f)
# endif
# ifndef WCOREDUMP
#  define WCOREDUMP(x) ((x) & 0x80)
# endif
# ifndef WEXITSTATUS
#  define WEXITSTATUS(x) (((x) >> 8) & 0xff)
# endif
# ifndef WIFSIGNALED
#  define WIFSIGNALED(x) (WTERMSIG (x) != 0)
# endif
# ifndef WIFEXITED
#  define WIFEXITED(x) (WTERMSIG (x) == 0)
# endif

#else   /* Have 'union wait'.  */

# define WAIT_T union wait
# ifndef WTERMSIG
#  define WTERMSIG(x) ((x).w_termsig)
# endif
# ifndef WCOREDUMP
#  define WCOREDUMP(x) ((x).w_coredump)
# endif
# ifndef WEXITSTATUS
#  define WEXITSTATUS(x) ((x).w_retcode)
# endif
# ifndef WIFSIGNALED
#  define WIFSIGNALED(x) (WTERMSIG(x) != 0)
# endif
# ifndef WIFEXITED
#  define WIFEXITED(x) (WTERMSIG(x) == 0)
# endif

#endif  /* Don't have 'union wait'.  */

#if !defined(HAVE_UNISTD_H) && !defined(WINDOWS32)
int dup2 ();
int execve ();
void _exit ();
int geteuid ();
int getegid ();
int setgid ();
int getgid ();
#endif

#if HAVE_SYS_LOADAVG_H
# include <sys/loadavg.h>
#endif

#if HAVE_DECL_GETLOADAVG == 0
int getloadavg (double loadavg[], int nelem);
#endif

/* Different systems have different requirements for pid_t.
   Plus we have to support gettext string translation... Argh.  */
static const char *
pid2str (pid_t pid)
{
  static char pidstring[100];
  sprintf (pidstring, "%lu", (unsigned long) pid);
  return pidstring;
}

static void free_child (struct child *);
static void start_job_command (struct child *child);
static int load_too_high (void);
static int job_next_command (struct child *);
static int start_waiting_job (struct child *);

/* Chain of all live (or recently deceased) children.  */

struct child *children = 0;

/* Number of children currently running.  */

unsigned int job_slots_used = 0;

/* Nonzero if the 'good' standard input is in use.  */

static int good_stdin_used = 0;

/* Chain of children waiting to run until the load average goes down.  */

static struct child *waiting_jobs = 0;

/* Non-zero if we use a *real* shell (always so on Unix).  */

int unixy_shell = 1;

/* Number of jobs started in the current second.  */

unsigned long job_counter = 0;

/* Number of jobserver tokens this instance is currently using.  */

unsigned int jobserver_tokens = 0;


/* determines whether path looks to be a Bourne-like shell. */
int
is_bourne_compatible_shell (const char *path)
{
  /* List of known POSIX (or POSIX-ish) shells.  */
  static const char *unix_shells[] = {
    "sh",
    "bash",
    "dash",
    "ksh",
    "rksh",
    "zsh",
    "ash",
    NULL
  };
  const char **s;

  /* find the last directory separator, or the beginning of the string.  */
  const char *cp = path + strlen (path);

  while (cp > path && !ISDIRSEP (cp[-1]))
    --cp;

  /* this should be able to deal with extensions on Windows-like systems */
  for (s = unix_shells; *s != NULL; ++s)
    {
      if (strcmp (cp, *s) == 0)
        return 1; /* a known unix-style shell */
    }

  /* if not on the list, assume it's not a Bourne-like shell */
  return 0;
}

#ifdef POSIX
extern sigset_t fatal_signal_set;

static void
block_sigs ()
{
  sigprocmask (SIG_BLOCK, &fatal_signal_set, (sigset_t *) 0);
}

static void
unblock_sigs ()
{
  sigprocmask (SIG_UNBLOCK, &fatal_signal_set, (sigset_t *) 0);
}

void
unblock_all_sigs ()
{
  sigset_t empty;
  sigemptyset (&empty);
  sigprocmask (SIG_SETMASK, &empty, (sigset_t *) 0);
}

#elif defined(HAVE_SIGSETMASK)

extern int fatal_signal_mask;

static void
block_sigs ()
{
  sigblock (fatal_signal_mask);
}

static void
unblock_sigs ()
{
  sigsetmask (siggetmask () & ~fatal_signal_mask);
}

void
unblock_all_sigs ()
{
  sigsetmask (0);
}

#else

#define block_sigs()
#define unblock_sigs()

void
unblock_all_sigs ()
{
}

#endif

/* Write an error message describing the exit status given in
   EXIT_CODE, EXIT_SIG, and COREDUMP, for the target TARGET_NAME.
   Append "(ignored)" if IGNORED is nonzero.  */

static void
child_error (struct child *child,
             int exit_code, int exit_sig, int coredump, int ignored)
{
  const char *pre = "*** ";
  const char *post = "";
  const char *dump = "";
  const struct file *f = child->file;
  const floc *flocp = &f->cmds->fileinfo;
  const char *nm;
  const char *smode;
  size_t l;

  if (ignored && run_silent)
    return;

  if (exit_sig && coredump)
    dump = _(" (core dumped)");

  if (ignored)
    {
      pre = "";
      post = _(" (ignored)");
    }

  if (! flocp->filenm)
    nm = _("<builtin>");
  else
    {
      char *a = alloca (strlen (flocp->filenm) + 6 + INTSTR_LENGTH + 1);
      sprintf (a, "%s:%lu", flocp->filenm, flocp->lineno + flocp->offset);
      nm = a;
    }

  l = strlen (pre) + strlen (nm) + strlen (f->name) + strlen (post);

  smode = shuffle_get_mode ();
  if (smode)
    {
#define SHUFFLE_PREFIX " shuffle="
      char *a = alloca (CSTRLEN(SHUFFLE_PREFIX) + strlen (smode) + 1);
      sprintf (a, SHUFFLE_PREFIX "%s", smode);
      smode = a;
      l += strlen (smode);
#undef SHUFFLE_PREFIX
    }

  OUTPUT_SET (&child->output);

  show_goal_error ();

  if (exit_sig == 0)
    error (NILF, l + INTSTR_LENGTH, _("%s[%s: %s] Error %d%s%s"),
           pre, nm, f->name, exit_code, post, smode ? smode : "");
  else
    {
      const char *s = strsignal (exit_sig);
      error (NILF, l + strlen (s) + strlen (dump), "%s[%s: %s] %s%s%s%s",
             pre, nm, f->name, s, dump, post, smode ? smode : "");
    }

  OUTPUT_UNSET ();
}


/* Handle a dead child.  This handler may or may not ever be installed.

   If we're using the jobserver feature without pselect(), we need it.
   First, installing it ensures the read will interrupt on SIGCHLD.  Second,
   we close the dup'd read FD to ensure we don't enter another blocking read
   without reaping all the dead children.  In this case we don't need the
   dead_children count.

   If we don't have either waitpid or wait3, then make is unreliable, but we
   use the dead_children count to reap children as best we can.  */

static unsigned int dead_children = 0;

void
child_handler (int sig UNUSED)
{
  ++dead_children;

  jobserver_signal ();
}

extern pid_t shell_function_pid;

/* Reap all dead children, storing the returned status and the new command
   state ('cs_finished') in the 'file' member of the 'struct child' for the
   dead child, and removing the child from the chain.  In addition, if BLOCK
   nonzero, we block in this function until we've reaped at least one
   complete child, waiting for it to die if necessary.  If ERR is nonzero,
   print an error message first.  */

void
reap_children (int block, int err)
{
  WAIT_T status;
  /* Initially, assume we have some.  */
  int reap_more = 1;

#ifdef WAIT_NOHANG
# define REAP_MORE reap_more
#else
# define REAP_MORE dead_children
#endif

  /* As long as:

       We have at least one child outstanding OR a shell function in progress,
         AND
       We're blocking for a complete child OR there are more children to reap

     we'll keep reaping children.  */

  while ((children != 0 || shell_function_pid != 0)
         && (block || REAP_MORE))
    {
      unsigned int remote = 0;
      pid_t pid;
      int exit_code, exit_sig, coredump;
      struct child *lastc, *c;
      int child_failed;
      int any_remote, any_local;
      int dontcare;

      if (err && block)
        {
          static int printed = 0;

          /* We might block for a while, so let the user know why.
             Only print this message once no matter how many jobs are left.  */
          fflush (stdout);
          if (!printed)
            O (error, NILF, _("*** Waiting for unfinished jobs...."));
          printed = 1;
        }

      /* We have one less dead child to reap.  As noted in
         child_handler() above, this count is completely unimportant for
         all modern, POSIX-y systems that support wait3() or waitpid().
         The rest of this comment below applies only to early, broken
         pre-POSIX systems.  We keep the count only because... it's there...

         The test and decrement are not atomic; if it is compiled into:
                register = dead_children - 1;
                dead_children = register;
         a SIGCHLD could come between the two instructions.
         child_handler increments dead_children.
         The second instruction here would lose that increment.  But the
         only effect of dead_children being wrong is that we might wait
         longer than necessary to reap a child, and lose some parallelism;
         and we might print the "Waiting for unfinished jobs" message above
         when not necessary.  */

      if (dead_children > 0)
        --dead_children;

      any_remote = 0;
      any_local = shell_function_pid != 0;
      lastc = 0;
      for (c = children; c != 0; lastc = c, c = c->next)
        {
          any_remote |= c->remote;
          any_local |= ! c->remote;

          /* If pid < 0, this child never even started.  Handle it.  */
          if (c->pid < 0)
            {
              exit_sig = 0;
              coredump = 0;
              /* According to POSIX, 127 is used for command not found.  */
              exit_code = 127;
              goto process_child;
            }

          DB (DB_JOBS, (_("Live child %p (%s) PID %s %s\n"),
                        c, c->file->name, pid2str (c->pid),
                        c->remote ? _(" (remote)") : ""));
        }

      /* First, check for remote children.  */
      if (any_remote)
        pid = remote_status (&exit_code, &exit_sig, &coredump, 0);
      else
        pid = 0;

      if (pid > 0)
        /* We got a remote child.  */
        remote = 1;
      else if (pid < 0)
        {
          /* A remote status command failed miserably.  Punt.  */
          pfatal_with_name ("remote_status");
        }
      else
        {
          /* No remote children.  Check for local children.  */
          if (any_local)
            {
#ifdef WAIT_NOHANG
              if (!block)
                pid = WAIT_NOHANG (&status);
              else
#endif
                EINTRLOOP (pid, wait (&status));
            }
          else
            pid = 0;

          if (pid < 0)
            {
              /* The wait*() failed miserably.  Punt.  */
              pfatal_with_name ("wait");
            }
          else if (pid > 0)
            {
              /* We got a child exit; chop the status word up.  */
              exit_code = WEXITSTATUS (status);
              exit_sig = WIFSIGNALED (status) ? WTERMSIG (status) : 0;
              coredump = WCOREDUMP (status);
            }
          else
            {
              /* No local children are dead.  */
              reap_more = 0;

              if (!block || !any_remote)
                break;

              /* Now try a blocking wait for a remote child.  */
              pid = remote_status (&exit_code, &exit_sig, &coredump, 1);
              if (pid < 0)
                pfatal_with_name ("remote_status");

              if (pid == 0)
                /* No remote children either.  Finally give up.  */
                break;

              /* We got a remote child.  */
              remote = 1;
            }
        }

      /* Some child finished: increment the command count.  */
      ++command_count;

      /* Check if this is the child of the 'shell' function.  */
      if (!remote && pid == shell_function_pid)
        {
          shell_completed (exit_code, exit_sig);
          break;
        }

      /* Search for a child matching the deceased one.  */
      lastc = 0;
      for (c = children; c != 0; lastc = c, c = c->next)
        if (c->pid == pid && c->remote == remote)
          break;

      if (c == 0)
        /* An unknown child died.
           Ignore it; it was inherited from our invoker.  */
        continue;

      DB (DB_JOBS, (exit_sig == 0 && exit_code == 0
                    ? _("Reaping winning child %p PID %s %s\n")
                    : _("Reaping losing child %p PID %s %s\n"),
                    c, pid2str (c->pid), c->remote ? _(" (remote)") : ""));

      /* If we have started jobs in this second, remove one.  */
      if (job_counter)
        --job_counter;

    process_child:

#if defined(USE_POSIX_SPAWN)
      /* Some versions of posix_spawn() do not detect errors such as command
         not found until after they fork.  In that case they will exit with a
         code of 127.  Try to detect that and provide a useful error message.
         Otherwise we'll just show the error below, as normal.  */
      if (exit_sig == 0 && exit_code == 127 && c->cmd_name)
        {
          const char *e = NULL;
          struct stat st;
          int r;

          /* There are various ways that this will show a different error than
             fork/exec.  To really get the right error we'd have to fall back
             to fork/exec but I don't want to bother with that.  Just do the
             best we can.  */

          EINTRLOOP(r, stat (c->cmd_name, &st));
          if (r < 0)
            e = strerror (errno);
          else if (S_ISDIR(st.st_mode) || !(st.st_mode & S_IXUSR))
            e = strerror (EACCES);
          else if (st.st_size == 0)
            e = strerror (ENOEXEC);

          if (e)
            OSS(error, NILF, "%s: %s", c->cmd_name, e);
        }
#endif

      /* Determine the failure status: 0 for success, 1 for updating target in
         question mode, 2 for anything else.  */
      if (exit_sig == 0 && exit_code == 0)
        child_failed = MAKE_SUCCESS;
      else if (exit_sig == 0 && exit_code == 1 && question_flag && c->recursive)
        child_failed = MAKE_TROUBLE;
      else
        child_failed = MAKE_FAILURE;

      if (c->sh_batch_file)
        {
          int rm_status;

          DB (DB_JOBS, (_("Cleaning up temp batch file %s\n"),
                        c->sh_batch_file));

          errno = 0;
          rm_status = remove (c->sh_batch_file);
          if (rm_status)
            DB (DB_JOBS, (_("Cleaning up temp batch file %s failed (%d)\n"),
                          c->sh_batch_file, errno));

          /* all done with memory */
          free (c->sh_batch_file);
          c->sh_batch_file = NULL;
        }

      /* If this child had the good stdin, say it is now free.  */
      if (c->good_stdin)
        good_stdin_used = 0;

      dontcare = c->dontcare;

      if (child_failed && !c->noerror && !ignore_errors_flag)
        {
          /* The commands failed.  Write an error message,
             delete non-precious targets, and abort.  */
          static int delete_on_error = -1;

          if (!dontcare && child_failed == MAKE_FAILURE)
            child_error (c, exit_code, exit_sig, coredump, 0);

          c->file->update_status = child_failed == MAKE_FAILURE ? us_failed : us_question;
          if (delete_on_error == -1)
            {
              struct file *f = lookup_file (".DELETE_ON_ERROR");
              delete_on_error = f != 0 && f->is_target;
            }
          if (exit_sig != 0 || delete_on_error)
            delete_child_targets (c);
        }
      else
        {
          if (child_failed)
            {
              /* The commands failed, but we don't care.  */
              child_error (c, exit_code, exit_sig, coredump, 1);
              child_failed = 0;
            }

          /* If there are more commands to run, try to start them.  */
          if (job_next_command (c))
            {
              if (handling_fatal_signal)
                {
                  /* Never start new commands while we are dying.
                     Since there are more commands that wanted to be run,
                     the target was not completely remade.  So we treat
                     this as if a command had failed.  */
                  c->file->update_status = us_failed;
                }
              else
                {
                  /* If we're sync'ing per line, write the previous line's
                     output before starting the next one.  */
                  if (output_sync == OUTPUT_SYNC_LINE)
                    output_dump (&c->output);
                  /* Check again whether to start remotely.
                     Whether or not we want to changes over time.
                     Also, start_remote_job may need state set up
                     by start_remote_job_p.  */
                  c->remote = start_remote_job_p (0);
                  start_job_command (c);
                  /* Fatal signals are left blocked in case we were
                     about to put that child on the chain.  But it is
                     already there, so it is safe for a fatal signal to
                     arrive now; it will clean up this child's targets.  */
                  unblock_sigs ();
                  if (c->file->command_state == cs_running)
                    /* We successfully started the new command.
                       Loop to reap more children.  */
                    continue;
                }

              if (c->file->update_status != us_success)
                /* We failed to start the commands.  */
                delete_child_targets (c);
            }
          else
            /* There are no more commands.  We got through them all
               without an unignored error.  Now the target has been
               successfully updated.  */
            c->file->update_status = us_success;
        }

      /* When we get here, all the commands for c->file are finished.  */

      /* Synchronize any remaining parallel output.  */
      output_dump (&c->output);

      /* At this point c->file->update_status is success or failed.  But
         c->file->command_state is still cs_running if all the commands
         ran; notice_finished_file looks for cs_running to tell it that
         it's interesting to check the file's modtime again now.  */

      if (! handling_fatal_signal)
        /* Notice if the target of the commands has been changed.
           This also propagates its values for command_state and
           update_status to its also_make files.  */
        notice_finished_file (c->file);

      /* Block fatal signals while frobnicating the list, so that
         children and job_slots_used are always consistent.  Otherwise
         a fatal signal arriving after the child is off the chain and
         before job_slots_used is decremented would believe a child was
         live and call reap_children again.  */
      block_sigs ();

      if (c->pid > 0)
        {
          DB (DB_JOBS, (_("Removing child %p PID %s%s from chain.\n"),
                        c, pid2str (c->pid), c->remote ? _(" (remote)") : ""));
        }

      /* There is now another slot open.  */
      if (job_slots_used > 0)
        job_slots_used -= c->jobslot;

      /* Remove the child from the chain and free it.  */
      if (lastc == 0)
        children = c->next;
      else
        lastc->next = c->next;

      free_child (c);

      unblock_sigs ();

      /* If the job failed, and the -k flag was not given, die,
         unless we are already in the process of dying.  */
      if (!err && child_failed && !dontcare && !keep_going_flag &&
          /* fatal_error_signal will die with the right signal.  */
          !handling_fatal_signal)
        die (child_failed);

      /* Only block for one child.  */
      block = 0;
    }

  return;
}

/* Free the storage allocated for CHILD.  */

void
free_childbase (struct childbase *child)
{
  if (child->environment != 0)
    {
      char **ep = child->environment;
      while (*ep != 0)
        free (*ep++);
      free (child->environment);
    }

  free (child->cmd_name);
}

static void
free_child (struct child *child)
{
  output_close (&child->output);

  if (!jobserver_tokens)
    ONS (fatal, NILF, "INTERNAL: Freeing child %p (%s) but no tokens left",
         child, child->file->name);

  /* If we're using the jobserver and this child is not the only outstanding
     job, put a token back into the pipe for it.  */

  if (jobserver_enabled () && jobserver_tokens > 1)
    {
      jobserver_release (1);
      DB (DB_JOBS, (_("Released token for child %p (%s).\n"),
                    child, child->file->name));
    }

  --jobserver_tokens;

  if (handling_fatal_signal) /* Don't bother free'ing if about to die.  */
    return;

  if (child->command_lines != 0)
    {
      unsigned int i;
      for (i = 0; i < child->file->cmds->ncommand_lines; ++i)
        free (child->command_lines[i]);
      free (child->command_lines);
    }

  free_childbase ((struct childbase*)child);

  free (child);
}


/* Start a job to run the commands specified in CHILD.
   CHILD is updated to reflect the commands and ID of the child process.

   NOTE: On return fatal signals are blocked!  The caller is responsible
   for calling 'unblock_sigs', once the new child is safely on the chain so
   it can be cleaned up in the event of a fatal signal.  */

static void
start_job_command (struct child *child)
{
  int flags;
  char *p;
# define FREE_ARGV(_a) do{ if (_a) { free ((_a)[0]); free (_a); } }while(0)
  char **argv;

  /* If we have a completely empty commandset, stop now.  */
  if (!child->command_ptr)
    goto next_command;

  /* Combine the flags parsed for the line itself with
     the flags specified globally for this target.  */
  flags = (child->file->command_flags
           | child->file->cmds->lines_flags[child->command_line - 1]);

  p = child->command_ptr;
  child->noerror = ANY_SET (flags, COMMANDS_NOERROR);

  while (*p != '\0')
    {
      if (*p == '@')
        flags |= COMMANDS_SILENT;
      else if (*p == '+')
        flags |= COMMANDS_RECURSE;
      else if (*p == '-')
        child->noerror = 1;
      /* Don't skip newlines.  */
      else if (!ISBLANK (*p))
        break;
      ++p;
    }

  child->recursive = ANY_SET (flags, COMMANDS_RECURSE);

  /* Update the file's command flags with any new ones we found.  We only
     keep the COMMANDS_RECURSE setting.  Even this isn't 100% correct; we are
     now marking more commands recursive than should be in the case of
     multiline define/endef scripts where only one line is marked "+".  In
     order to really fix this, we'll have to keep a lines_flags for every
     actual line, after expansion.  */
  child->file->cmds->lines_flags[child->command_line - 1] |= flags & COMMANDS_RECURSE;

  /* POSIX requires that a recipe prefix after a backslash-newline should
     be ignored.  Remove it now so the output is correct.  */
  {
    char prefix = child->file->cmds->recipe_prefix;
    char *p1, *p2;
    p1 = p2 = p;
    while (*p1 != '\0')
      {
        *(p2++) = *p1;
        if (p1[0] == '\n' && p1[1] == prefix)
          ++p1;
        ++p1;
      }
    *p2 = *p1;
  }

  /* Figure out an argument list from this command line.  */
  {
    char *end = 0;
    argv = construct_command_argv (p, &end, child->file,
                                   child->file->cmds->lines_flags[child->command_line - 1],
                                   &child->sh_batch_file);
    if (end == NULL)
      child->command_ptr = NULL;
    else
      {
        *end++ = '\0';
        child->command_ptr = end;
      }
  }

  /* If -q was given, say that updating 'failed' if there was any text on the
     command line, or 'succeeded' otherwise.  The exit status of 1 tells the
     user that -q is saying 'something to do'; the exit status for a random
     error is 2.  */
  if (argv != 0 && question_flag && NONE_SET (flags, COMMANDS_RECURSE))
    {
      FREE_ARGV (argv);
          child->file->update_status = us_question;
          notice_finished_file (child->file);
          return;
    }

  if (touch_flag && NONE_SET (flags, COMMANDS_RECURSE))
    {
      /* Go on to the next command.  It might be the recursive one.
         We construct ARGV only to find the end of the command line.  */
      FREE_ARGV (argv);
      argv = 0;
    }

  if (argv == 0)
    {
    next_command:
      /* This line has no commands.  Go to the next.  */
      if (job_next_command (child))
        start_job_command (child);
      else
        {
          /* No more commands.  Make sure we're "running"; we might not be if
             (e.g.) all commands were skipped due to -n.  */
          set_command_state (child->file, cs_running);
          child->file->update_status = us_success;
          notice_finished_file (child->file);
        }

      OUTPUT_UNSET();
      return;
    }

  /* Are we going to synchronize this command's output?  Do so if either we're
     in SYNC_RECURSE mode or this command is not recursive.  We'll also check
     output_sync separately below in case it changes due to error.  */
  child->output.syncout = output_sync && (output_sync == OUTPUT_SYNC_RECURSE
                                          || NONE_SET (flags, COMMANDS_RECURSE));

  OUTPUT_SET (&child->output);

  if (! child->output.syncout)
    /* We don't want to sync this command: to avoid misordered
       output ensure any already-synced content is written.  */
    output_dump (&child->output);

  /* Print the command if appropriate.  */
  if (just_print_flag || ISDB (DB_PRINT)
      || (NONE_SET (flags, COMMANDS_SILENT) && !run_silent))
    OS (message, 0, "%s", p);

  /* Tell update_goal_chain that a command has been started on behalf of
     this target.  It is important that this happens here and not in
     reap_children (where we used to do it), because reap_children might be
     reaping children from a different target.  We want this increment to
     guaranteedly indicate that a command was started for the dependency
     chain (i.e., update_file recursion chain) we are processing.  */

  ++commands_started;

  /* Optimize an empty command.  People use this for timestamp rules,
     so avoid forking a useless shell.  Do this after we increment
     commands_started so make still treats this special case as if it
     performed some action (makes a difference as to what messages are
     printed, etc.  */

  if (
      (argv[0] && is_bourne_compatible_shell (argv[0]))
      && (argv[1] && argv[1][0] == '-'
        &&
            ((argv[1][1] == 'c' && argv[1][2] == '\0')
          ||
             (argv[1][1] == 'e' && argv[1][2] == 'c' && argv[1][3] == '\0')))
      && (argv[2] && argv[2][0] == ':' && argv[2][1] == '\0')
      && argv[3] == NULL)
    {
      FREE_ARGV (argv);
      goto next_command;
    }

  /* If -n was given, recurse to get the next line in the sequence.  */

  if (just_print_flag && NONE_SET (flags, COMMANDS_RECURSE))
    {
      FREE_ARGV (argv);
      goto next_command;
    }

  /* We're sure we're going to invoke a command: set up the output.  */
  output_start ();

  /* Flush the output streams so they won't have things written twice.  */

  fflush (stdout);
  fflush (stderr);

  /* Decide whether to give this child the 'good' standard input
     (one that points to the terminal or whatever), or the 'bad' one
     that points to the read side of a broken pipe.  */

  child->good_stdin = !good_stdin_used;
  if (child->good_stdin)
    good_stdin_used = 1;

  child->deleted = 0;

  /* Set up the environment for the child.
     It's a slight inaccuracy to set the environment for recursive make even
     for command lines that aren't recursive, but I don't want to have to
     recompute the target environment for each command.  Better would be to
     keep a separate entry for MAKEFLAGS in the environment so it could be
     replaced on its own.  For now just set it for all lines.
   */
  if (child->environment == 0)
    child->environment = target_environment (child->file,
                                             child->file->cmds->any_recurse);

  /* start_waiting_job has set CHILD->remote if we can start a remote job.  */
  if (child->remote)
    {
      int is_remote, used_stdin;
      pid_t id;
      if (start_remote_job (argv, child->environment,
                            child->good_stdin ? 0 : get_bad_stdin (),
                            &is_remote, &id, &used_stdin))
        /* Don't give up; remote execution may fail for various reasons.  If
           so, simply run the job locally.  */
        goto run_local;
      else
        {
          if (child->good_stdin && !used_stdin)
            {
              child->good_stdin = 0;
              good_stdin_used = 0;
            }
          child->remote = is_remote;
          child->pid = id;
        }
    }
  else
    {
      /* Fork the child process.  */
    run_local:
      block_sigs ();

      child->remote = 0;

      jobserver_pre_child (ANY_SET (flags, COMMANDS_RECURSE));

      child->pid = child_execute_job ((struct childbase *)child,
                                      child->good_stdin, argv);

      jobserver_post_child (ANY_SET (flags, COMMANDS_RECURSE));
    }

  /* Bump the number of jobs started in this second.  */
  if (child->pid >= 0)
    ++job_counter;

  /* Set the state to running.  */
  set_command_state (child->file, cs_running);

  /* Free the storage used by the child's argument list.  */
  FREE_ARGV (argv);

  OUTPUT_UNSET();

#undef FREE_ARGV
}

/* Try to start a child running.
   Returns nonzero if the child was started (and maybe finished), or zero if
   the load was too high and the child was put on the 'waiting_jobs' chain.  */

static int
start_waiting_job (struct child *c)
{
  struct file *f = c->file;

  /* If we can start a job remotely, we always want to, and don't care about
     the local load average.  We record that the job should be started
     remotely in C->remote for start_job_command to test.  */

  c->remote = start_remote_job_p (1);

  /* If we are running at least one job already and the load average
     is too high, make this one wait.  */
  if (!c->remote
      && ((job_slots_used > 0 && load_too_high ())
          ))
    {
      /* Put this child on the chain of children waiting for the load average
         to go down.  */
      set_command_state (f, cs_running);
      c->next = waiting_jobs;
      waiting_jobs = c;
      return 0;
    }

  /* Start the first command; reap_children will run later command lines.  */
  start_job_command (c);

  switch (f->command_state)
    {
    case cs_running:
      c->next = children;
      if (c->pid > 0)
        {
          DB (DB_JOBS, (_("Putting child %p (%s) PID %s%s on the chain.\n"),
                        c, c->file->name, pid2str (c->pid),
                        c->remote ? _(" (remote)") : ""));
          /* One more job slot is in use.  */
          ++job_slots_used;
          assert (c->jobslot == 0);
          c->jobslot = 1;
        }
      children = c;
      unblock_sigs ();
      break;

    case cs_not_started:
      /* All the command lines turned out to be empty.  */
      f->update_status = us_success;
      /* FALLTHROUGH */

    case cs_finished:
      notice_finished_file (f);
      free_child (c);
      break;

    default:
      assert (f->command_state == cs_finished);
      break;
    }

  return 1;
}

/* Create a 'struct child' for FILE and start its commands running.  */

void
new_job (struct file *file)
{
  struct commands *cmds = file->cmds;
  struct child *c;
  char **lines;
  unsigned int i;

  /* Let any previously decided-upon jobs that are waiting
     for the load to go down start before this new one.  */
  start_waiting_jobs ();

  /* Reap any children that might have finished recently.  */
  reap_children (0, 0);

  /* Chop the commands up into lines if they aren't already.  */
  chop_commands (cmds);

  /* Start the command sequence, record it in a new
     'struct child', and add that to the chain.  */

  c = xcalloc (sizeof (struct child));
  output_init (&c->output);

  c->file = file;
  c->sh_batch_file = NULL;

  /* Cache dontcare flag because file->dontcare can be changed once we
     return. Check dontcare inheritance mechanism for details.  */
  c->dontcare = file->dontcare;

  /* Start saving output in case the expansion uses $(info ...) etc.  */
  OUTPUT_SET (&c->output);

  /* Expand the command lines and store the results in LINES.  */
  lines = xmalloc (cmds->ncommand_lines * sizeof (char *));
  for (i = 0; i < cmds->ncommand_lines; ++i)
    {
      /* Collapse backslash-newline combinations that are inside variable
         or function references.  These are left alone by the parser so
         that they will appear in the echoing of commands (where they look
         nice); and collapsed by construct_command_argv when it tokenizes.
         But letting them survive inside function invocations loses because
         we don't want the functions to see them as part of the text.  */

      char *in, *out, *ref;

      /* IN points to where in the line we are scanning.
         OUT points to where in the line we are writing.
         When we collapse a backslash-newline combination,
         IN gets ahead of OUT.  */

      in = out = cmds->command_lines[i];
      while ((ref = strchr (in, '$')) != 0)
        {
          ++ref;                /* Move past the $.  */

          if (out != in)
            /* Copy the text between the end of the last chunk
               we processed (where IN points) and the new chunk
               we are about to process (where REF points).  */
            memmove (out, in, ref - in);

          /* Move both pointers past the boring stuff.  */
          out += ref - in;
          in = ref;

          if (*ref == '(' || *ref == '{')
            {
              char openparen = *ref;
              char closeparen = openparen == '(' ? ')' : '}';
              char *outref;
              int count;
              char *p;

              *out++ = *in++;   /* Copy OPENPAREN.  */
              outref = out;
              /* IN now points past the opening paren or brace.
                 Count parens or braces until it is matched.  */
              count = 0;
              while (*in != '\0')
                {
                  if (*in == closeparen && --count < 0)
                    break;
                  else if (*in == '\\' && in[1] == '\n')
                    {
                      /* We have found a backslash-newline inside a
                         variable or function reference.  Eat it and
                         any following whitespace.  */

                      int quoted = 0;
                      for (p = in - 1; p > ref && *p == '\\'; --p)
                        quoted = !quoted;

                      if (quoted)
                        /* There were two or more backslashes, so this is
                           not really a continuation line.  We don't collapse
                           the quoting backslashes here as is done in
                           collapse_continuations, because the line will
                           be collapsed again after expansion.  */
                        *out++ = *in++;
                      else
                        {
                          /* Skip the backslash, newline, and whitespace.  */
                          in += 2;
                          NEXT_TOKEN (in);

                          /* Discard any preceding whitespace that has
                             already been written to the output.  */
                          while (out > outref && ISBLANK (out[-1]))
                            --out;

                          /* Replace it all with a single space.  */
                          *out++ = ' ';
                        }
                    }
                  else
                    {
                      if (*in == openparen)
                        ++count;

                      *out++ = *in++;
                    }
                }
            }
        }

      /* There are no more references in this line to worry about.
         Copy the remaining uninteresting text to the output.  */
      if (out != in)
        memmove (out, in, strlen (in) + 1);

      /* Finally, expand the line.  */
      cmds->fileinfo.offset = i;
      lines[i] = allocated_variable_expand_for_file (cmds->command_lines[i],
                                                     file);
    }

  cmds->fileinfo.offset = 0;
  c->command_lines = lines;

  /* Fetch the first command line to be run.  */
  job_next_command (c);

  /* Wait for a job slot to be freed up.  If we allow an infinite number
     don't bother; also job_slots will == 0 if we're using the jobserver.  */

  if (job_slots != 0)
    while (job_slots_used == job_slots)
      reap_children (1, 0);

#ifdef MAKE_JOBSERVER
  /* If we are controlling multiple jobs make sure we have a token before
     starting the child. */

  /* This can be inefficient.  There's a decent chance that this job won't
     actually have to run any subprocesses: the command script may be empty
     or otherwise optimized away.  It would be nice if we could defer
     obtaining a token until just before we need it, in start_job_command.
     To do that we'd need to keep track of whether we'd already obtained a
     token (since start_job_command is called for each line of the job, not
     just once).  Also more thought needs to go into the entire algorithm;
     this is where the old parallel job code waits, so...  */

  else if (jobserver_enabled ())
    while (1)
      {
        int got_token;

        DB (DB_JOBS, ("Need a job token; we %shave children\n",
                      children ? "" : "don't "));

        /* If we don't already have a job started, use our "free" token.  */
        if (!jobserver_tokens)
          break;

        /* Prepare for jobserver token acquisition.  */
        jobserver_pre_acquire ();

        /* Reap anything that's currently waiting.  */
        reap_children (0, 0);

        /* Kick off any jobs we have waiting for an opportunity that
           can run now (i.e., waiting for load). */
        start_waiting_jobs ();

        /* If our "free" slot is available, use it; we don't need a token.  */
        if (!jobserver_tokens)
          break;

        /* There must be at least one child already, or we have no business
           waiting for a token. */
        if (!children)
          O (fatal, NILF, "INTERNAL: no children as we go to sleep on read");

        /* Get a token.  */
        got_token = jobserver_acquire (waiting_jobs != NULL);

        /* If we got one, we're done here.  */
        if (got_token == 1)
          {
            DB (DB_JOBS, (_("Obtained token for child %p (%s).\n"),
                          c, c->file->name));
            break;
          }
      }
#endif

  ++jobserver_tokens;

  /* Trace the build.
     Use message here so that changes to working directories are logged.  */
  if (ISDB (DB_WHY))
    {
      const char *nm;

      if (! cmds->fileinfo.filenm)
        nm = _("<builtin>");
      else
        {
          char *n = alloca (strlen (cmds->fileinfo.filenm) + 1 + 11 + 1);
          sprintf (n, "%s:%lu", cmds->fileinfo.filenm, cmds->fileinfo.lineno);
          nm = n;
        }

      if (c->file->phony)
        OSS (message, 0, _("%s: update target '%s' due to: target is .PHONY"),
             nm, c->file->name);
      else if (c->file->last_mtime == NONEXISTENT_MTIME)
        OSS (message, 0,
             _("%s: update target '%s' due to: target does not exist"),
             nm, c->file->name);
      else
        {
          char *newer = allocated_variable_expand_for_file ("$?", c->file);
          if (newer[0] != '\0')
            {
              OSSS (message, 0, _("%s: update target '%s' due to: %s"),
                    nm, c->file->name, newer);
              free (newer);
            }
          else
            {
              /* One or more files didn't exist, and didn't get created.  */
              size_t len = 0;
              struct dep *d;

              for (d = c->file->deps; d != NULL; d = d->next)
                if (d->file->last_mtime == NONEXISTENT_MTIME)
                  len += strlen (d->file->name) + 1;

              if (!len)
                OSS (message, 0,
                     _("%s: update target '%s' due to: unknown reasons"),
                     nm, c->file->name);
              else
                {
                  char *cp = newer = alloca (len);
                  for (d = c->file->deps; d != NULL; d = d->next)
                    if (d->file->last_mtime == NONEXISTENT_MTIME)
                      {
                        if (cp > newer)
                          *(cp++) = ' ';
                        cp = stpcpy (cp, d->file->name);
                      }
                  OSSS (message, 0, _("%s: update target '%s' due to: %s"),
                        nm, c->file->name, newer);
                }
            }
        }
    }

  /* The job is now primed.  Start it running.
     (This will notice if there is in fact no recipe.)  */
  start_waiting_job (c);

  if (job_slots == 1 || not_parallel)
    /* Since there is only one job slot, make things run linearly.
       Wait for the child to die, setting the state to 'cs_finished'.  */
    while (file->command_state == cs_running)
      reap_children (1, 0);

  OUTPUT_UNSET ();
  return;
}

/* Move CHILD's pointers to the next command for it to execute.
   Returns nonzero if there is another command.  */

static int
job_next_command (struct child *child)
{
  while (child->command_ptr == 0 || *child->command_ptr == '\0')
    {
      /* There are no more lines in the expansion of this line.  */
      if (child->command_line == child->file->cmds->ncommand_lines)
        {
          /* There are no more lines to be expanded.  */
          child->command_ptr = 0;
          child->file->cmds->fileinfo.offset = 0;
          return 0;
        }
      else
        /* Get the next line to run.  */
        child->command_ptr = child->command_lines[child->command_line++];
    }

  child->file->cmds->fileinfo.offset = child->command_line - 1;
  return 1;
}

/* Determine if the load average on the system is too high to start a new job.

   On systems which provide /proc/loadavg (e.g., Linux), we use an idea
   provided by Sven C. Dack <sven.c.dack@sky.com>: retrieve the current number
   of runnable processes, if it's greater than the requested load we don't
   allow another job to start.  We allow a job to start with equal processes
   since one of those will be for make itself, which will then pause waiting
   for jobs to clear.

   If /proc/loadavg is not available for some reason, we obtain the system
   load average and compare that.

   The system load average is only recomputed once every N (N>=1) seconds.
   However, a very parallel make can easily start tens or even hundreds of
   jobs in a second, which brings the system to its knees for a while until
   that first batch of jobs clears out.

   To avoid this we use a weighted algorithm to try to account for jobs which
   have been started since the last second, and guess what the load average
   would be now if it were computed.

   This algorithm was provided by Thomas Riedl <thomas.riedl@siemens.com>,
   based on load average being recomputed once per second, which is
   (apparently) how Solaris operates.  Linux recomputes only once every 5
   seconds, but Linux is handled by the /proc/loadavg algorithm above.

   Thomas writes:

!      calculate something load-oid and add to the observed sys.load,
!      so that latter can catch up:
!      - every job started increases jobctr;
!      - every dying job decreases a positive jobctr;
!      - the jobctr value gets zeroed every change of seconds,
!        after its value*weight_b is stored into the 'backlog' value last_sec
!      - weight_a times the sum of jobctr and last_sec gets
!        added to the observed sys.load.
!
!      The two weights have been tried out on 24 and 48 proc. Sun Solaris-9
!      machines, using a several-thousand-jobs-mix of cpp, cc, cxx and smallish
!      sub-shelled commands (rm, echo, sed...) for tests.
!      lowering the 'direct influence' factor weight_a (e.g. to 0.1)
!      resulted in significant excession of the load limit, raising it
!      (e.g. to 0.5) took bad to small, fast-executing jobs and didn't
!      reach the limit in most test cases.
!
!      lowering the 'history influence' weight_b (e.g. to 0.1) resulted in
!      exceeding the limit for longer-running stuff (compile jobs in
!      the .5 to 1.5 sec. range),raising it (e.g. to 0.5) overrepresented
!      small jobs' effects.

 */

#define LOAD_WEIGHT_A           0.25
#define LOAD_WEIGHT_B           0.25

static int
load_too_high (void)
{
  static double last_sec;
  static time_t last_now;
  static int proc_fd = -2;

  double load, guess;
  time_t now;

  if (max_load_average < 0)
    return 0;

  /* If we haven't tried to open /proc/loadavg, try now.  */
#define LOADAVG "/proc/loadavg"
  if (proc_fd == -2)
    {
      EINTRLOOP (proc_fd, open (LOADAVG, O_RDONLY));
      if (proc_fd < 0)
        DB (DB_JOBS, ("Using system load detection method.\n"));
      else
        {
          DB (DB_JOBS, ("Using " LOADAVG " load detection method.\n"));
          fd_noinherit (proc_fd);
        }
    }

  /* Try to read /proc/loadavg if we managed to open it.  */
  if (proc_fd >= 0)
    {
      int r;

      EINTRLOOP (r, lseek (proc_fd, 0, SEEK_SET));
      if (r >= 0)
        {
#define PROC_LOADAVG_SIZE 64
          char avg[PROC_LOADAVG_SIZE+1];

          EINTRLOOP (r, read (proc_fd, avg, PROC_LOADAVG_SIZE));
          if (r >= 0)
            {
              const char *p;

              /* The syntax of /proc/loadavg is:
                    <1m> <5m> <15m> <running>/<total> <pid>
                 The load is considered too high if there are more jobs
                 running than the requested average.  */

              avg[r] = '\0';
              p = strchr (avg, ' ');
              if (p)
                p = strchr (p+1, ' ');
              if (p)
                p = strchr (p+1, ' ');

              if (p && ISDIGIT(p[1]))
                {
                  unsigned int cnt = make_toui (p+1, NULL);
                  DB (DB_JOBS, ("Running: system = %u / make = %u (max requested = %f)\n",
                                cnt, job_slots_used, max_load_average));
                  return (double)cnt > max_load_average;
                }

              DB (DB_JOBS, ("Failed to parse " LOADAVG ": %s\n", avg));
            }
        }

      /* If we got here, something went wrong.  Give up on this method.  */
      if (r < 0)
        DB (DB_JOBS, ("Failed to read " LOADAVG ": %s\n", strerror (errno)));

      close (proc_fd);
      proc_fd = -1;
    }

  /* Find the real system load average.  */
  errno = 0;
  if (getloadavg (&load, 1) != 1)
    {
      static int lossage = -1;
      /* Complain only once for the same error.  */
      if (lossage == -1 || errno != lossage)
        {
          if (errno == 0)
            /* An errno value of zero means getloadavg is just unsupported.  */
            O (error, NILF,
               _("cannot enforce load limits on this operating system"));
          else
            perror_with_name (_("cannot enforce load limit: "), "getloadavg");
        }
      lossage = errno;
      load = 0;
    }

  /* If we're in a new second zero the counter and correct the backlog
     value.  Only keep the backlog for one extra second; after that it's 0.  */
  now = time (NULL);
  if (last_now < now)
    {
      if (last_now == now - 1)
        last_sec = LOAD_WEIGHT_B * job_counter;
      else
        last_sec = 0.0;

      job_counter = 0;
      last_now = now;
    }

  /* Try to guess what the load would be right now.  */
  guess = load + (LOAD_WEIGHT_A * (job_counter + last_sec));

  DB (DB_JOBS, ("Estimated system load = %f (actual = %f) (max requested = %f)\n",
                guess, load, max_load_average));

  return guess >= max_load_average;
}

/* Start jobs that are waiting for the load to be lower.  */

void
start_waiting_jobs (void)
{
  struct child *job;

  if (waiting_jobs == 0)
    return;

  do
    {
      /* Check for recently deceased descendants.  */
      reap_children (0, 0);

      /* Take a job off the waiting list.  */
      job = waiting_jobs;
      waiting_jobs = job->next;

      /* Try to start that job.  We break out of the loop as soon
         as start_waiting_job puts one back on the waiting list.  */
    }
  while (start_waiting_job (job) && waiting_jobs != 0);

  return;
}

/* POSIX:
   Create a child process executing the command in ARGV.
   Returns the PID or -1.  */
pid_t
child_execute_job (struct childbase *child, int good_stdin, char **argv)
{
  const int fdin = good_stdin ? FD_STDIN : get_bad_stdin ();
  int fdout = FD_STDOUT;
  int fderr = FD_STDERR;
  pid_t pid = -1;
  int r;
#if defined(USE_POSIX_SPAWN)
  char *cmd;
  posix_spawnattr_t attr;
  posix_spawn_file_actions_t fa;
  short flags = 0;
#endif

  /* Divert child output if we want to capture it.  */
  if (child->output.syncout)
    {
      if (child->output.out >= 0)
        fdout = child->output.out;
      if (child->output.err >= 0)
        fderr = child->output.err;
    }

#if !defined(USE_POSIX_SPAWN)

  {
    /* The child may clobber environ so remember ours and restore it.  */
    char **parent_env = environ;
    pid = vfork ();
    if (pid != 0)
      {
        environ = parent_env;
        return pid;
      }
  }

  /* We are the child.  */
  unblock_all_sigs ();

#ifdef SET_STACK_SIZE
  /* Reset limits, if necessary.  */
  if (stack_limit.rlim_cur)
    setrlimit (RLIMIT_STACK, &stack_limit);
#endif

  /* For any redirected FD, dup2() it to the standard FD.
     They are all marked close-on-exec already.  */
  if (fdin >= 0 && fdin != FD_STDIN)
    EINTRLOOP (r, dup2 (fdin, FD_STDIN));
  if (fdout != FD_STDOUT)
    EINTRLOOP (r, dup2 (fdout, FD_STDOUT));
  if (fderr != FD_STDERR)
    EINTRLOOP (r, dup2 (fderr, FD_STDERR));

  /* Run the command.  */
  exec_command (argv, child->environment);
  _exit (127);

#else /* USE_POSIX_SPAWN */

  if ((r = posix_spawnattr_init (&attr)) != 0)
    goto done;

  if ((r = posix_spawn_file_actions_init (&fa)) != 0)
    {
      posix_spawnattr_destroy (&attr);
      goto done;
    }

  /* Unblock all signals.  */
#ifdef HAVE_POSIX_SPAWNATTR_SETSIGMASK
  {
    sigset_t mask;
    sigemptyset (&mask);
    r = posix_spawnattr_setsigmask (&attr, &mask);
    if (r != 0)
      goto cleanup;
    flags |= POSIX_SPAWN_SETSIGMASK;
  }
#endif /* have posix_spawnattr_setsigmask() */

  /* USEVFORK can give significant speedup on systems where it's available.  */
#ifdef POSIX_SPAWN_USEVFORK
  flags |= POSIX_SPAWN_USEVFORK;
#endif

  /* For any redirected FD, dup2() it to the standard FD.
     They are all marked close-on-exec already.  */
  if (fdin >= 0 && fdin != FD_STDIN)
    if ((r = posix_spawn_file_actions_adddup2 (&fa, fdin, FD_STDIN)) != 0)
      goto cleanup;
  if (fdout != FD_STDOUT)
    if ((r = posix_spawn_file_actions_adddup2 (&fa, fdout, FD_STDOUT)) != 0)
      goto cleanup;
  if (fderr != FD_STDERR)
    if ((r = posix_spawn_file_actions_adddup2 (&fa, fderr, FD_STDERR)) != 0)
      goto cleanup;

  /* We can't use the POSIX_SPAWN_RESETIDS flag: when make is invoked under
     restrictive environments like unshare it will fail with EINVAL.  */

  /* Apply the spawn flags.  */
  if ((r = posix_spawnattr_setflags (&attr, flags)) != 0)
    goto cleanup;

  /* Look up the program on the child's PATH, if needed.  */
  {
    const char *p = NULL;
    char **pp;

    for (pp = child->environment; *pp != NULL; ++pp)
      if ((*pp)[0] == 'P' && (*pp)[1] == 'A' && (*pp)[2] == 'T'
          && (*pp)[3] == 'H' &&(*pp)[4] == '=')
        {
          p = (*pp) + 5;
          break;
        }

    /* execvp() will use a default PATH if none is set; emulate that.  */
    if (p == NULL)
      {
        size_t l = confstr (_CS_PATH, NULL, 0);
        if (l)
          {
            char *dp = alloca (l);
            confstr (_CS_PATH, dp, l);
            p = dp;
          }
      }

    cmd = (char *)find_in_given_path (argv[0], p, NULL, 0);
  }

  if (!cmd)
    {
      r = errno;
      goto cleanup;
    }

  /* Start the program.  */
  while ((r = posix_spawn (&pid, cmd, &fa, &attr, argv,
                           child->environment)) == EINTR)
    ;

  /* posix_spawn() doesn't provide sh fallback like exec() does; implement
     it here.  POSIX doesn't specify the path to sh so use the default.  */

  if (r == ENOEXEC)
    {
      char **nargv;
      char **pp;
      size_t l = 0;

      for (pp = argv; *pp != NULL; ++pp)
        ++l;

      nargv = xmalloc (sizeof (char *) * (l + 3));
      nargv[0] = (char *)default_shell;
      nargv[1] = cmd;
      memcpy (&nargv[2], &argv[1], sizeof (char *) * l);

      while ((r = posix_spawn (&pid, nargv[0], &fa, &attr, nargv,
                               child->environment)) == EINTR)
        ;

      free (nargv);
    }

  if (r == 0)
    {
      /* Spawn succeeded but may fail later: remember the command.  */
      free (child->cmd_name);
      if (cmd != argv[0])
        child->cmd_name = cmd;
      else
        child->cmd_name = xstrdup(cmd);
    }

 cleanup:
  posix_spawn_file_actions_destroy (&fa);
  posix_spawnattr_destroy (&attr);

 done:
  if (r != 0)
    pid = -1;

#endif /* USE_POSIX_SPAWN */

  if (pid < 0)
    OSS (error, NILF, "%s: %s", argv[0], strerror (r));

  return pid;
}

/* Replace the current process with one running the command in ARGV,
   with environment ENVP.  This function does not return.  */

pid_t
exec_command (char **argv, char **envp)
{
  pid_t pid = -1;

  /* Run the program.  Don't use execvpe() as we want the search for argv[0]
     to use the new PATH, but execvpe() searches before resetting PATH.  */
  environ = envp;
  execvp (argv[0], argv);

  switch (errno)
    {
    case ENOENT:
      OSS (error, NILF, "%s: %s", argv[0], strerror (errno));
      break;
    case ENOEXEC:
      {
        /* The file was not a program.  Try it as a shell script.  */
        const char *shell;
        char **new_argv;
        int argc;
        int i=1;

        shell = getenv ("SHELL");
        if (shell == 0)
          shell = default_shell;

        argc = 1;
        while (argv[argc] != 0)
          ++argc;

        new_argv = alloca ((1 + argc + 1) * sizeof (char *));
        new_argv[0] = (char *)shell;

        new_argv[i] = argv[0];
        while (argc > 0)
          {
            new_argv[i + argc] = argv[argc];
            --argc;
          }

        execvp (shell, new_argv);
        OSS (error, NILF, "%s: %s", new_argv[0], strerror (errno));
        break;
      }

    default:
      OSS (error, NILF, "%s: %s", argv[0], strerror (errno));
      break;
    }

  return pid;
}

/* Figure out the argument list necessary to run LINE as a command.  Try to
   avoid using a shell.  This routine handles only ' quoting, and " quoting
   when no backslash, $ or ' characters are seen in the quotes.  Starting
   quotes may be escaped with a backslash.  If any of the characters in
   sh_chars is seen, or any of the builtin commands listed in sh_cmds is the
   first word of a line, the shell is used.

   If RESTP is not NULL, *RESTP is set to point to the first newline in LINE.
   If *RESTP is NULL, newlines will be ignored.

   SHELL is the shell to use, or nil to use the default shell.
   IFS is the value of $IFS, or nil (meaning the default).

   FLAGS is the value of lines_flags for this command line.  It is used in the
   WINDOWS32 port to check whether + or $(MAKE) were found in this command
   line, in which case the effect of just_print_flag is overridden.

   The returned value is either NULL if the line was empty, or else a pointer
   to an array of strings.  The fist pointer points to the memory used by all
   the strings, so to free you free the 0'th element then the returned pointer
   (see the FREE_ARGV macro).  */

static char **
construct_command_argv_internal (char *line, char **restp, const char *shell,
                                 const char *shellflags, const char *ifs,
                                 int flags, char **batch_filename UNUSED)
{
  static const char *sh_chars = "#;\"*?[]&|<>(){}$`^~!";
  static const char *sh_cmds[] =
    { ".", ":", "alias", "bg", "break", "case", "cd", "command", "continue",
      "eval", "exec", "exit", "export", "fc", "fg", "for", "getopts", "hash",
      "if", "jobs", "login", "logout", "read", "readonly", "return", "set",
      "shift", "test", "times", "trap", "type", "ulimit", "umask", "unalias",
      "unset", "wait", "while", 0 };

  size_t i;
  char *p;
#ifndef NDEBUG
  char *end;
#endif
  char *ap;
  const char *cap;
  const char *cp;
  int instring, word_has_equals, seen_nonequals, last_argument_was_empty;
  char **new_argv = 0;
  char *argstr = 0;

  if (restp != NULL)
    *restp = NULL;

  /* Make sure not to bother processing an empty line but stop at newline.  */
  while (ISBLANK (*line))
    ++line;
  if (*line == '\0')
    return 0;

  if (shellflags == 0)
    shellflags = posix_pedantic && NONE_SET (flags, COMMANDS_NOERROR) ? "-ec" : "-c";

  /* See if it is safe to parse commands internally.  */
  if (shell == 0)
    shell = default_shell;
  else if (strcmp (shell, default_shell))
    goto slow;

  if (ifs)
    for (cap = ifs; *cap != '\0'; ++cap)
      if (*cap != ' ' && *cap != '\t' && *cap != '\n')
        goto slow;

  if (shellflags)
    if (shellflags[0] != '-'
        || ((shellflags[1] != 'c' || shellflags[2] != '\0')
            && (shellflags[1] != 'e' || shellflags[2] != 'c' || shellflags[3] != '\0')))
      goto slow;

  i = strlen (line) + 1;

  /* More than 1 arg per character is impossible.  */
  new_argv = xmalloc (i * sizeof (char *));

  /* All the args can fit in a buffer as big as LINE is.   */
  ap = new_argv[0] = argstr = xmalloc (i);
#ifndef NDEBUG
  end = ap + i;
#endif

  /* I is how many complete arguments have been found.  */
  i = 0;
  instring = word_has_equals = seen_nonequals = last_argument_was_empty = 0;
  for (p = line; *p != '\0'; ++p)
    {
      assert (ap <= end);

      if (instring)
        {
          /* Inside a string, just copy any char except a closing quote
             or a backslash-newline combination.  */
          if (*p == instring)
            {
              instring = 0;
              if (ap == new_argv[0] || *(ap-1) == '\0')
                last_argument_was_empty = 1;
            }
          else if (*p == '\\' && p[1] == '\n')
            {
              /* Backslash-newline is handled differently depending on what
                 kind of string we're in: inside single-quoted strings you
                 keep them; in double-quoted strings they disappear.  For
                 DOS/Windows/OS2, if we don't have a POSIX shell, we keep the
                 pre-POSIX behavior of removing the backslash-newline.  */
              if (instring == '"'
                  )
                ++p;
              else
                {
                  *(ap++) = *(p++);
                  *(ap++) = *p;
                }
            }
          else if (*p == '\n' && restp != NULL)
            {
              /* End of the command line.  */
              *restp = p;
              goto end_of_line;
            }
          /* Backslash, $, and ` are special inside double quotes.
             If we see any of those, punt.
             But on MSDOS, if we use COMMAND.COM, double and single
             quotes have the same effect.  */
          else if (instring == '"' && strchr ("\\$`", *p) != 0 && unixy_shell)
            goto slow;
          else
            *ap++ = *p;
        }
      else if (strchr (sh_chars, *p) != 0)
        /* Not inside a string, but it's a special char.  */
        goto slow;
      else if (one_shell && *p == '\n')
        /* In .ONESHELL mode \n is a separator like ; or && */
        goto slow;
      else
        /* Not a special char.  */
        switch (*p)
          {
          case '=':
            /* Equals is a special character in leading words before the
               first word with no equals sign in it.  This is not the case
               with sh -k, but we never get here when using nonstandard
               shell flags.  */
            if (! seen_nonequals && unixy_shell)
              goto slow;
            word_has_equals = 1;
            *ap++ = '=';
            break;

          case '\\':
            /* Backslash-newline has special case handling, ref POSIX.
               We're in the fastpath, so emulate what the shell would do.  */
            if (p[1] == '\n')
              {
                /* Throw out the backslash and newline.  */
                ++p;

                /* At the beginning of the argument, skip any whitespace other
                   than newline before the start of the next word.  */
                if (ap == new_argv[i])
                  while (ISBLANK (p[1]))
                    ++p;
              }
            else if (p[1] != '\0')
              {
                /* Copy and skip the following char.  */
                *ap++ = *++p;
              }
            break;

          case '\'':
          case '"':
            instring = *p;
            break;

          case '\n':
            if (restp != NULL)
              {
                /* End of the command line.  */
                *restp = p;
                goto end_of_line;
              }
            else
              /* Newlines are not special.  */
              *ap++ = '\n';
            break;

          case ' ':
          case '\t':
            /* We have the end of an argument.
               Terminate the text of the argument.  */
            *ap++ = '\0';
            new_argv[++i] = ap;
            last_argument_was_empty = 0;

            /* Update SEEN_NONEQUALS, which tells us if every word
               heretofore has contained an '='.  */
            seen_nonequals |= ! word_has_equals;
            if (word_has_equals && ! seen_nonequals)
              /* An '=' in a word before the first
                 word without one is magical.  */
              goto slow;
            word_has_equals = 0; /* Prepare for the next word.  */

            /* If this argument is the command name,
               see if it is a built-in shell command.
               If so, have the shell handle it.  */
            if (i == 1)
              {
                int j;
                for (j = 0; sh_cmds[j] != 0; ++j)
                  {
                    if (streq (sh_cmds[j], new_argv[0]))
                      goto slow;
                  }
              }

            /* Skip whitespace chars, but not newlines.  */
            while (ISBLANK (p[1]))
              ++p;
            break;

          default:
            *ap++ = *p;
            break;
          }
    }
 end_of_line:

  if (instring)
    /* Let the shell deal with an unterminated quote.  */
    goto slow;

  /* Terminate the last argument and the argument list.  */

  *ap = '\0';
  if (new_argv[i][0] != '\0' || last_argument_was_empty)
    ++i;
  new_argv[i] = 0;

  if (i == 1)
    {
      int j;
      for (j = 0; sh_cmds[j] != 0; ++j)
        if (streq (sh_cmds[j], new_argv[0]))
          goto slow;
    }

  if (new_argv[0] == 0)
    {
      /* Line was empty.  */
      free (argstr);
      free (new_argv);
      return 0;
    }

  return new_argv;

 slow:;
  /* We must use the shell.  */

  if (new_argv != 0)
    {
      /* Free the old argument list we were working on.  */
      free (argstr);
      free (new_argv);
    }

  {
    /* SHELL may be a multi-word command.  Construct a command line
       "$(SHELL) $(.SHELLFLAGS) LINE", with all special chars in LINE escaped.
       Then recurse, expanding this command line to get the final
       argument list.  */

    char *new_line;
    size_t shell_len = strlen (shell);
    size_t line_len = strlen (line);
    size_t sflags_len = shellflags ? strlen (shellflags) : 0;

    /* In .ONESHELL mode we are allowed to throw the entire current
        recipe string at a single shell and trust that the user
        has configured the shell and shell flags, and formatted
        the string, appropriately. */
    if (one_shell)
      {
        /* If the shell is Bourne compatible, we must remove and ignore
           interior special chars [@+-] because they're meaningless to
           the shell itself. If, however, we're in .ONESHELL mode and
           have changed SHELL to something non-standard, we should
           leave those alone because they could be part of the
           script. In this case we must also leave in place
           any leading [@+-] for the same reason.  */

        /* Remove and ignore interior prefix chars [@+-] because they're
             meaningless given a single shell. */
        if (is_bourne_compatible_shell (shell)
            )
          {
            const char *f = line;
            char *t = line;

            /* Copy the recipe, removing and ignoring interior prefix chars
               [@+-]: they're meaningless in .ONESHELL mode.  */
            while (f[0] != '\0')
              {
                int esc = 0;

                /* This is the start of a new recipe line.  Skip whitespace
                   and prefix characters but not newlines.  */
                while (ISBLANK (*f) || *f == '-' || *f == '@' || *f == '+')
                  ++f;

                /* Copy until we get to the next logical recipe line.  */
                while (*f != '\0')
                  {
                    *(t++) = *(f++);
                    if (f[-1] == '\\')
                      esc = !esc;
                    else
                      {
                        /* On unescaped newline, we're done with this line.  */
                        if (f[-1] == '\n' && ! esc)
                          break;

                        /* Something else: reset the escape sequence.  */
                        esc = 0;
                      }
                  }
              }
            *t = '\0';
          }
        /* Create an argv list for the shell command line.  */
        {
          int n = 1;
          char *nextp;

          new_argv = xmalloc ((4 + sflags_len/2) * sizeof (char *));

          nextp = new_argv[0] = xmalloc (shell_len + sflags_len + line_len + 3);
          nextp = mempcpy (nextp, shell, shell_len + 1);

          /* Chop up the shellflags (if any) and assign them.  */
          if (! shellflags)
            {
              new_argv[n++] = nextp;
              *(nextp++) = '\0';
            }
          else
            {
              /* Parse shellflags using construct_command_argv_internal to
                 handle quotes. */
              char **argv;
              char *f = alloca (sflags_len + 1);
              memcpy (f, shellflags, sflags_len + 1);
              argv = construct_command_argv_internal (f, 0, 0, 0, 0, flags, 0);
              if (argv)
                {
                  char **a;
                  for (a = argv; *a; ++a)
                    {
                      new_argv[n++] = nextp;
                      nextp = stpcpy (nextp, *a) + 1;
                    }
                  free (argv[0]);
                  free (argv);
                }
            }

          /* Set the command to invoke.  */
          new_argv[n++] = nextp;
          memcpy(nextp, line, line_len + 1);
          new_argv[n++] = NULL;
        }
        return new_argv;
      }

    new_line = xmalloc ((shell_len*2) + 1 + sflags_len + 1
                        + (line_len*2) + 1);
    ap = new_line;
    /* Copy SHELL, escaping any characters special to the shell.  If
       we don't escape them, construct_command_argv_internal will
       recursively call itself ad nauseam, or until stack overflow,
       whichever happens first.  */
    for (cp = shell; *cp != '\0'; ++cp)
      {
        if (strchr (sh_chars, *cp) != 0)
          *(ap++) = '\\';
        *(ap++) = *cp;
      }
    *(ap++) = ' ';
    if (shellflags)
      {
        ap = mempcpy (ap, shellflags, sflags_len);
        *(ap++) = ' ';
      }
    for (p = line; *p != '\0'; ++p)
      {
        if (restp != NULL && *p == '\n')
          {
            *restp = p;
            break;
          }
        else if (*p == '\\' && p[1] == '\n')
          {
            /* POSIX says we keep the backslash-newline.  If we don't have a
               POSIX shell on DOS/Windows/OS2, mimic the pre-POSIX behavior
               and remove the backslash/newline.  */
# define PRESERVE_BSNL  1
            if (PRESERVE_BSNL)
              {
                *(ap++) = '\\';
                /* Only non-batch execution needs another backslash,
                   because it will be passed through a recursive
                   invocation of this function.  */
                if (!batch_mode_shell)
                  *(ap++) = '\\';
                *(ap++) = '\n';
              }
            ++p;
            continue;
          }

        /* DOS shells don't know about backslash-escaping.  */
        if (unixy_shell && !batch_mode_shell &&
            (*p == '\\' || *p == '\'' || *p == '"'
             || ISSPACE (*p)
             || strchr (sh_chars, *p) != 0))
          *ap++ = '\\';
        *ap++ = *p;
      }
    if (ap == new_line + shell_len + sflags_len + 2)
      {
        /* Line was empty.  */
        free (new_line);
        return 0;
      }
    *ap = '\0';

    if (unixy_shell)
      new_argv = construct_command_argv_internal (new_line, 0, 0, 0, 0,
                                                  flags, 0);

    else
      fatal (NILF, CSTRLEN (__FILE__) + INTSTR_LENGTH,
             _("%s (line %d) Bad shell context (!unixy && !batch_mode_shell)\n"),
            __FILE__, __LINE__);

    free (new_line);
  }

  return new_argv;
}

/* Figure out the argument list necessary to run LINE as a command.  Try to
   avoid using a shell.  This routine handles only ' quoting, and " quoting
   when no backslash, $ or ' characters are seen in the quotes.  Starting
   quotes may be escaped with a backslash.  If any of the characters in
   sh_chars is seen, or any of the builtin commands listed in sh_cmds
   is the first word of a line, the shell is used.

   If RESTP is not NULL, *RESTP is set to point to the first newline in LINE.
   If *RESTP is NULL, newlines will be ignored.

   FILE is the target whose commands these are.  It is used for
   variable expansion for $(SHELL) and $(IFS).  */

char **
construct_command_argv (char *line, char **restp, struct file *file,
                        int cmd_flags, char **batch_filename)
{
  char *shell, *ifs, *shellflags;
  char **argv;

  {
    struct variable *var;
    /* Turn off --warn-undefined-variables while we expand SHELL and IFS.  */
    int save = warn_undefined_variables_flag;
    warn_undefined_variables_flag = 0;

    shell = allocated_variable_expand_for_file ("$(SHELL)", file);

    var = lookup_variable_for_file (STRING_SIZE_TUPLE (".SHELLFLAGS"), file);
    if (!var)
      shellflags = xstrdup ("");
    else if (posix_pedantic && var->origin == o_default)
      /* In POSIX mode we default to -ec, unless we're ignoring errors.  */
      shellflags = xstrdup (ANY_SET (cmd_flags, COMMANDS_NOERROR) ? "-c" : "-ec");
    else
      shellflags = allocated_variable_expand_for_file (var->value, file);

    ifs = allocated_variable_expand_for_file ("$(IFS)", file);

    warn_undefined_variables_flag = save;
  }

  argv = construct_command_argv_internal (line, restp, shell, shellflags, ifs,
                                          cmd_flags, batch_filename);

  free (shell);
  free (shellflags);
  free (ifs);

  return argv;
}

#if !defined(HAVE_DUP2) && !defined(_AMIGA)
int
dup2 (int old, int new)
{
  int fd;

  (void) close (new);
  EINTRLOOP (fd, dup (old));
  if (fd != new)
    {
      (void) close (fd);
      errno = EMFILE;
      return -1;
    }

  return fd;
}
#endif /* !HAVE_DUP2 && !_AMIGA */

/* On VMS systems, include special VMS functions.  */
