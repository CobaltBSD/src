/* Data base of default implicit rules for GNU Make.
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

#include "filedef.h"
#include "variable.h"
#include "rule.h"
#include "dep.h"
#include "job.h"
#include "commands.h"

/* Define GCC_IS_NATIVE if gcc is the native development environment on
   your system (gcc/bison/flex vs cc/yacc/lex).  */
#if defined(__MSDOS__) || defined(__EMX__)
# define GCC_IS_NATIVE
#endif


/* This is the default list of suffixes for suffix rules.
   '.s' must come last, so that a '.o' file will be made from
   a '.c' or '.p' or ... file rather than from a .s file.  */

static char default_suffixes[]
  = ".out .a .ln .o .c .cc .C .cpp .p .f .F .m .r .y .l .ym .yl .s .S \
.mod .sym .def .h .info .dvi .tex .texinfo .texi .txinfo \
.w .ch .web .sh .elc .el";

static struct pspec default_pattern_rules[] =
  {
    { "(%)", "%",
        "$(AR) $(ARFLAGS) $@ $<" },
    /* The X.out rules are only in BSD's default set because
       BSD Make has no null-suffix rules, so 'foo.out' and
       'foo' are the same thing.  */
    { "%.out", "%",
        "@rm -f $@ \n cp $< $@" },

    /* Syntax is "ctangle foo.w foo.ch foo.c".  */
    { "%.c", "%.w %.ch",
        "$(CTANGLE) $^ $@" },
    { "%.tex", "%.w %.ch",
        "$(CWEAVE) $^ $@" },

    { 0, 0, 0 }
  };

static struct pspec default_terminal_rules[] =
  {
    /* RCS.  */
    { "%", "%,v",
        "$(CHECKOUT,v)" },
    { "%", "RCS/%,v",
        "$(CHECKOUT,v)" },
    { "%", "RCS/%",
        "$(CHECKOUT,v)" },

    /* SCCS.  */
    { "%", "s.%",
        "$(GET) $(GFLAGS) $(SCCS_OUTPUT_OPTION) $<" },
    { "%", "SCCS/s.%",
        "$(GET) $(GFLAGS) $(SCCS_OUTPUT_OPTION) $<" },
    { 0, 0, 0 }
  };

/* Set up the default .SUFFIXES list.  */

void
set_default_suffixes (void)
{
  suffix_file = enter_file (strcache_add (".SUFFIXES"));
  suffix_file->builtin = 1;

  if (no_builtin_rules_flag)
    define_variable_cname ("SUFFIXES", "", o_default, 0);
  else
    {
      struct dep *d;
      const char *p = default_suffixes;
      suffix_file->deps = enter_prereqs (PARSE_SIMPLE_SEQ ((char **)&p, struct dep),
                                         NULL);
      for (d = suffix_file->deps; d; d = d->next)
        d->file->builtin = 1;

      define_variable_cname ("SUFFIXES", default_suffixes, o_default, 0);
    }
}


/* Install the default pattern rules.  */

void
install_default_implicit_rules (void)
{
  struct pspec *p;

  if (no_builtin_rules_flag)
    return;

  for (p = default_pattern_rules; p->target != 0; ++p)
    install_pattern_rule (p, 0);

  for (p = default_terminal_rules; p->target != 0; ++p)
    install_pattern_rule (p, 1);
}
