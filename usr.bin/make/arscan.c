/* Library function for scanning an archive file.
Copyright (C) 1987-2023 Free Software Foundation, Inc.
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

#ifdef TEST
/* Hack, the real error() routine eventually pulls in die from main.c */
#define error(a, b, c, d)
#endif

#include <fcntl.h>
#include <sys/file.h>

#ifndef NO_ARCHIVES

/* SCO Unix's compiler defines both of these.  */
#ifdef  M_UNIX
#undef  M_XENIX
#endif

/* On the sun386i and in System V rel 3, ar.h defines two different archive
   formats depending upon whether you have defined PORTAR (normal) or PORT5AR
   (System V Release 1).  There is no default, one or the other must be defined
   to have a nonzero value.  */

#if (!defined (PORTAR) || PORTAR == 0) && (!defined (PORT5AR) || PORT5AR == 0)
#undef  PORTAR
#ifdef M_XENIX
/* According to Jim Sievert <jas1@rsvl.unisys.com>, for SCO XENIX defining
   PORTAR to 1 gets the wrong archive format, and defining it to 0 gets the
   right one.  */
#define PORTAR 0
#else
#define PORTAR 1
#endif
#endif

#  include <ar.h>
# define TOCHAR(_m)     (_m)

/* Cray's <ar.h> apparently defines this.  */
#ifndef AR_HDR_SIZE
# define   AR_HDR_SIZE  (sizeof (struct ar_hdr))
#endif

#include "intprops.h"

#include "output.h"

static uintmax_t
parse_int (const char *ptr, const size_t len, const int base, uintmax_t max,
           const char *type, const char *archive, const char *name)
{
  const char *const ep = ptr + len;
  const int maxchar = '0' + base - 1;
  uintmax_t val = 0;

  /* In all the versions I know of the spaces come last, but be safe.  */
  while (ptr < ep && *ptr == ' ')
    ++ptr;

  while (ptr < ep && *ptr != ' ')
    {
      uintmax_t nv;

      if (*ptr < '0' || *ptr > maxchar)
        OSSS (fatal, NILF,
              _("Invalid %s for archive %s member %s"), type, archive, name);
      nv = (val * base) + (*ptr - '0');
      if (nv < val || nv > max)
        OSSS (fatal, NILF,
              _("Invalid %s for archive %s member %s"), type, archive, name);
      val = nv;
      ++ptr;
    }

  return val;
}

/* Takes three arguments ARCHIVE, FUNCTION and ARG.

   Open the archive named ARCHIVE, find its members one by one,
   and for each one call FUNCTION with the following arguments:
     archive file descriptor for reading the data,
     member name,
     member name might be truncated flag,
     member header position in file,
     member data position in file,
     member data size,
     member date,
     member uid,
     member gid,
     member protection mode,
     ARG.

   The descriptor is poised to read the data of the member
   when FUNCTION is called.  It does not matter how much
   data FUNCTION reads.

   If FUNCTION returns nonzero, we immediately return
   what FUNCTION returned.

   Returns -1 if archive does not exist,
   Returns -2 if archive has invalid format.
   Returns 0 if have scanned successfully.  */

intmax_t
ar_scan (const char *archive, ar_member_func_t function, const void *arg)
{
#ifdef AIAMAG
  FL_HDR fl_header;
# ifdef AIAMAGBIG
  int big_archive = 0;
  FL_HDR_BIG fl_header_big;
# endif
#endif
  char *namemap = 0;
  unsigned int namemap_size = 0;
  int desc = open (archive, O_RDONLY, 0);
  if (desc < 0)
    return -1;

#ifdef SARMAG
  {
    char buf[SARMAG];
    int nread;
    nread = readbuf (desc, buf, SARMAG);
    if (nread != SARMAG || memcmp (buf, ARMAG, SARMAG))
      goto invalid;
  }
#else
#ifdef AIAMAG
  {
    int nread;
    nread = readbuf (desc, &fl_header, FL_HSZ);
    if (nread != FL_HSZ)
      goto invalid;

#ifdef AIAMAGBIG
    /* If this is a "big" archive, then set the flag and
       re-read the header into the "big" structure. */
    if (!memcmp (fl_header.fl_magic, AIAMAGBIG, SAIAMAG))
      {
        off_t o;

        big_archive = 1;

        /* seek back to beginning of archive */
        EINTRLOOP (o, lseek (desc, 0, 0));
        if (o < 0)
          goto invalid;

        /* re-read the header into the "big" structure */
        nread = readbuf (desc, &fl_header_big, FL_HSZ_BIG);
        if (nread != FL_HSZ_BIG)
          goto invalid;
      }
    else
#endif
       /* Check to make sure this is a "normal" archive. */
      if (memcmp (fl_header.fl_magic, AIAMAG, SAIAMAG))
        goto invalid;
  }
#else
  {
    int buf;
    int nread;
    nread = readbuf (desc, &buf, sizeof (buf));
    if (nread != sizeof (buf) || buf != ARMAG)
      goto invalid;
  }
#endif
#endif

  /* Now find the members one by one.  */
  {
#ifdef SARMAG
    long int member_offset = SARMAG;
#else
#ifdef AIAMAG
    long int member_offset;
    long int last_member_offset;

#ifdef AIAMAGBIG
    if ( big_archive )
      {
        sscanf (fl_header_big.fl_fstmoff, "%20ld", &member_offset);
        sscanf (fl_header_big.fl_lstmoff, "%20ld", &last_member_offset);
      }
    else
#endif
      {
        sscanf (fl_header.fl_fstmoff, "%12ld", &member_offset);
        sscanf (fl_header.fl_lstmoff, "%12ld", &last_member_offset);
      }

    if (member_offset == 0)
      {
        /* Empty archive.  */
        close (desc);
        return 0;
      }
#else
    long int member_offset = sizeof (int);
#endif
#endif

    while (1)
      {
        ssize_t nread;
        struct ar_hdr member_header;
#ifdef AIAMAGBIG
        struct ar_hdr_big member_header_big;
#endif
#ifdef AIAMAG
# define ARNAME_MAX 255
        char name[ARNAME_MAX + 1];
        int name_len;
        intmax_t dateval;
        int uidval, gidval;
        long int data_offset;
#else
# define ARNAME_MAX (int)sizeof(member_header.ar_name)
        char namebuf[ARNAME_MAX + 1];
        char *name;
        int is_namemap;         /* Nonzero if this entry maps long names.  */
        int long_name = 0;
#endif
        long int eltsize;
        unsigned int eltmode;
        intmax_t eltdate;
        int eltuid, eltgid;
        intmax_t fnval;
        off_t o;

        memset(&member_header, '\0', sizeof (member_header));

        EINTRLOOP (o, lseek (desc, member_offset, 0));
        if (o < 0)
          goto invalid;

#ifdef AIAMAG
#define       AR_MEMHDR_SZ(x) (sizeof(x) - sizeof (x._ar_name))

#ifdef AIAMAGBIG
        if (big_archive)
          {
            nread = readbuf (desc, &member_header_big,
                             AR_MEMHDR_SZ(member_header_big));

            if (nread != AR_MEMHDR_SZ(member_header_big))
              goto invalid;

            sscanf (member_header_big.ar_namlen, "%4d", &name_len);
            if (name_len < 1 || name_len > ARNAME_MAX)
              goto invalid;

            nread = readbuf (desc, name, name_len);
            if (nread != name_len)
              goto invalid;

            name[name_len] = '\0';

            sscanf (member_header_big.ar_date, "%12" SCNdMAX, &dateval);
            sscanf (member_header_big.ar_uid, "%12d", &uidval);
            sscanf (member_header_big.ar_gid, "%12d", &gidval);
            sscanf (member_header_big.ar_mode, "%12o", &eltmode);
            sscanf (member_header_big.ar_size, "%20ld", &eltsize);

            data_offset = (member_offset + AR_MEMHDR_SZ(member_header_big)
                           + name_len + 2);
          }
        else
#endif
          {
            nread = readbuf (desc, &member_header,
                             AR_MEMHDR_SZ(member_header));

            if (nread != AR_MEMHDR_SZ(member_header))
              goto invalid;

            sscanf (member_header.ar_namlen, "%4d", &name_len);
            if (name_len < 1 || name_len > ARNAME_MAX)
              goto invalid;

            nread = readbuf (desc, name, name_len);
            if (nread != name_len)
              goto invalid;

            name[name_len] = '\0';

            sscanf (member_header.ar_date, "%12" SCNdMAX, &dateval);
            sscanf (member_header.ar_uid, "%12d", &uidval);
            sscanf (member_header.ar_gid, "%12d", &gidval);
            sscanf (member_header.ar_mode, "%12o", &eltmode);
            sscanf (member_header.ar_size, "%12ld", &eltsize);

            data_offset = (member_offset + AR_MEMHDR_SZ(member_header)
                           + name_len + 2);
          }
        data_offset += data_offset % 2;

        fnval =
          (*function) (desc, name, 0,
                       member_offset, data_offset, eltsize,
                       dateval, uidval, gidval,
                       eltmode, arg);

#else   /* Not AIAMAG.  */
        nread = readbuf (desc, &member_header, AR_HDR_SIZE);
        if (nread == 0)
          /* No data left means end of file; that is OK.  */
          break;

        if (nread != AR_HDR_SIZE
#if defined(ARFMAG) || defined(ARFZMAG)
            || (
# ifdef ARFMAG
                memcmp (member_header.ar_fmag, ARFMAG, 2)
# else
                1
# endif
                &&
# ifdef ARFZMAG
                memcmp (member_header.ar_fmag, ARFZMAG, 2)
# else
                1
# endif
               )
#endif
            )
          goto invalid;

        name = namebuf;
        memcpy (name, member_header.ar_name, sizeof member_header.ar_name);
        {
          char *p = name + sizeof member_header.ar_name;
          do
            *p = '\0';
          while (p > name && *--p == ' ');

#ifndef AIAMAG
          /* If the member name is "//" or "ARFILENAMES/" this may be
             a list of file name mappings.  The maximum file name
             length supported by the standard archive format is 14
             characters.  This member will actually always be the
             first or second entry in the archive, but we don't check
             that.  */
          is_namemap = (!strcmp (name, "//")
                        || !strcmp (name, "ARFILENAMES/"));
#endif  /* Not AIAMAG. */

          /* On some systems, there is a slash after each member name.  */
          if (*p == '/')
            *p = '\0';

#ifndef AIAMAG
          /* If the member name starts with a space or a slash, this
             is an index into the file name mappings (used by GNU ar).
             Otherwise if the member name looks like #1/NUMBER the
             real member name appears in the element data (used by
             4.4BSD).  */
          if (! is_namemap
              && (name[0] == ' ' || name[0] == '/')
              && namemap != 0)
            {
              const char* err;
              unsigned int name_off = make_toui (name + 1, &err);
              size_t name_len;

              if (err|| name_off >= namemap_size)
                goto invalid;

              name = namemap + name_off;
              name_len = strlen (name);
              if (name_len < 1)
                goto invalid;
              long_name = 1;
            }
          else if (name[0] == '#'
                   && name[1] == '1'
                   && name[2] == '/')
            {
              const char* err;
              unsigned int name_len = make_toui (name + 3, &err);

              if (err || name_len == 0 || name_len >= MIN (PATH_MAX, INT_MAX))
                goto invalid;

              name = alloca (name_len + 1);
              nread = readbuf (desc, name, name_len);
              if (nread < 0 || (unsigned int) nread != name_len)
                goto invalid;

              name[name_len] = '\0';

              long_name = 1;
            }
#endif /* Not AIAMAG. */
        }

#define PARSE_INT(_m, _t, _b, _n) \
        (_t) parse_int (TOCHAR (member_header._m), sizeof (member_header._m), \
                        _b, TYPE_MAXIMUM (_t), _n, archive, name)

        eltmode = PARSE_INT (ar_mode, unsigned int, 8, "mode");
        eltsize = PARSE_INT (ar_size, long, 10, "size");
        eltdate = PARSE_INT (ar_date, intmax_t, 10, "date");
        eltuid = PARSE_INT (ar_uid, int, 10, "uid");
        eltgid = PARSE_INT (ar_gid, int, 10, "gid");
#undef PARSE_INT

        fnval =
          (*function) (desc, name, ! long_name, member_offset,
                       member_offset + AR_HDR_SIZE, eltsize,
                       eltdate, eltuid, eltgid,
                       eltmode, arg);

#endif  /* AIAMAG.  */

        if (fnval)
          {
            (void) close (desc);
            return fnval;
          }

#ifdef AIAMAG
        if (member_offset == last_member_offset)
          /* End of the chain.  */
          break;

#ifdef AIAMAGBIG
        if (big_archive)
         sscanf (member_header_big.ar_nxtmem, "%20ld", &member_offset);
        else
#endif
          sscanf (member_header.ar_nxtmem, "%12ld", &member_offset);

        if (lseek (desc, member_offset, 0) != member_offset)
          goto invalid;
#else

        /* If this member maps archive names, we must read it in.  The
           name map will always precede any members whose names must
           be mapped.  */
        if (is_namemap)
          {
            char *clear;
            char *limit;

            if (eltsize > INT_MAX)
              goto invalid;
            namemap = alloca (eltsize + 1);
            nread = readbuf (desc, namemap, eltsize);
            if (nread != eltsize)
              goto invalid;
            namemap_size = eltsize;

            /* The names are separated by newlines.  Some formats have
               a trailing slash.  Null terminate the strings for
               convenience.  */
            limit = namemap + eltsize;
            for (clear = namemap; clear < limit; clear++)
              {
                if (*clear == '\n')
                  {
                    *clear = '\0';
                    if (clear[-1] == '/')
                      clear[-1] = '\0';
                  }
              }
            *limit = '\0';

            is_namemap = 0;
          }

        member_offset += AR_HDR_SIZE + eltsize;
        if (member_offset % 2 != 0)
          member_offset++;
#endif
      }
  }

  close (desc);
  return 0;

 invalid:
  close (desc);
  return -2;
}

/* Return nonzero iff NAME matches MEM.
   If TRUNCATED is nonzero, MEM may be truncated to
   sizeof (struct ar_hdr.ar_name) - 1.  */

int
ar_name_equal (const char *name, const char *mem, int truncated)
{
  const char *p;

  p = strrchr (name, '/');
  if (p != 0)
    name = p + 1;

  if (truncated)
    {
#ifdef AIAMAG
      /* TRUNCATED should never be set on this system.  */
      abort ();
#else
      struct ar_hdr hdr;
      return strneq (name, mem, sizeof (hdr.ar_name) - 1);
#endif /* !AIAMAG */
    }

  return !strcmp (name, mem);
}

/* ARGSUSED */
static intmax_t
ar_member_pos (int desc UNUSED, const char *mem, int truncated,
               long int hdrpos, long int datapos UNUSED, long int size UNUSED,
               intmax_t date UNUSED, int uid UNUSED, int gid UNUSED,
               unsigned int mode UNUSED, const void *name)
{
  if (!ar_name_equal (name, mem, truncated))
    return 0;
  return hdrpos;
}

/* Set date of member MEMNAME in archive ARNAME to current time.
   Returns 0 if successful,
   -1 if file ARNAME does not exist,
   -2 if not a valid archive,
   -3 if other random system call error (including file read-only),
   1 if valid but member MEMNAME does not exist.  */

int
ar_member_touch (const char *arname, const char *memname)
{
  intmax_t pos = ar_scan (arname, ar_member_pos, memname);
  off_t opos;
  int fd;
  struct ar_hdr ar_hdr;
  off_t o;
  int r;
  int datelen;
  struct stat statbuf;

  if (pos < 0)
    return (int) pos;
  if (!pos)
    return 1;

  opos = (off_t) pos;

  EINTRLOOP (fd, open (arname, O_RDWR, 0666));
  if (fd < 0)
    return -3;
  /* Read in this member's header */
  EINTRLOOP (o, lseek (fd, opos, 0));
  if (o < 0)
    goto lose;
  r = readbuf (fd, &ar_hdr, AR_HDR_SIZE);
  if (r != AR_HDR_SIZE)
    goto lose;
  /* The file's mtime is the time we we want.  */
  EINTRLOOP (r, fstat (fd, &statbuf));
  if (r < 0)
    goto lose;
  /* Advance member's time to that time */
#if defined(ARFMAG) || defined(ARFZMAG) || defined(AIAMAG) || defined(WINDOWS32)
  datelen = snprintf (TOCHAR (ar_hdr.ar_date), sizeof ar_hdr.ar_date,
                      "%" PRIdMAX, (intmax_t) statbuf.st_mtime);
  if (! (0 <= datelen && datelen < (int) sizeof ar_hdr.ar_date))
    goto lose;
  memset (ar_hdr.ar_date + datelen, ' ', sizeof ar_hdr.ar_date - datelen);
#else
  ar_hdr.ar_date = statbuf.st_mtime;
#endif
  /* Write back this member's header */
  EINTRLOOP (o, lseek (fd, opos, 0));
  if (o < 0)
    goto lose;
  r = writebuf (fd, &ar_hdr, AR_HDR_SIZE);
  if (r != AR_HDR_SIZE)
    goto lose;
  close (fd);
  return 0;

 lose:
  r = errno;
  close (fd);
  errno = r;
  return -3;
}

#ifdef TEST

intmax_t
describe_member (int desc, const char *name, int truncated,
                 long int hdrpos, long int datapos, long int size,
                 intmax_t date, int uid, int gid, unsigned int mode,
                 const void *arg)
{
  extern char *ctime ();
  time_t d = date;
  char const *ds;

  printf (_("Member '%s'%s: %ld bytes at %ld (%ld).\n"),
          name, truncated ? _(" (name might be truncated)") : "",
          size, hdrpos, datapos);
  ds = ctime (&d);
  printf (_("  Date %s"), ds ? ds : "?");
  printf (_("  uid = %d, gid = %d, mode = 0%o.\n"), uid, gid, mode);

  return 0;
}

int
main (int argc, char **argv)
{
  ar_scan (argv[1], describe_member, NULL);
  return 0;
}

#endif  /* TEST.  */
#endif  /* NO_ARCHIVES.  */
