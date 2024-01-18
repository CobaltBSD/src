ifeq ($(SRCDIR)x,x)
  SRCDIR = $(CURDIR)/../..
  BUILDDIR = $(SRCDIR)
endif
SUBDIR = lib/util
VPATH=.:$(SRCDIR)/$(SUBDIR)

default:all

include $(BUILDDIR)/config.mk

# nstring is required for asprintf(), etc.  Also some systems don't have
# snprintf(), e.g. Solaris 2.5.1.  2002.03.29.
UTILOBJECTS = \
  bitio.o \
  filename.o \
  io.o \
  mallocvar.o \
  matrix.o \
  nsleep.o \
  nstring.o \
  runlength.o \
  shhopt.o \
  token.o \
  vasprintf.o \

MERGE_OBJECTS =

include $(SRCDIR)/common.mk

all: $(UTILOBJECTS)

$(UTILOBJECTS): CFLAGS_TARGET=$(CFLAGS_SHLIB)

$(UTILOBJECTS):%.o:%.c importinc
	$(CC) -c $(INCLUDES) $(CFLAGS_ALL) -o $@ $<

testnstring: test.c nstring.h nstring.o
	$(CC) $(CFLAGS_ALL) -o $@ nstring.o $<
