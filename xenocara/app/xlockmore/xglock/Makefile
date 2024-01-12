# $Id : Makefile.in 4.04 1997/07/10 $
#
# xlockmore Makefile.in for autoconf (UNIX/VMS X11 support)
############################################################

# 

srcdir = .
top_srcdir = ..


N=
O=.o
#O=.obj
C=.c
#C=.cc
S=$(N) $(N)
#S=,
E=
#E=.exe

# please define
# C as the C source code extension
# O as the object extension
# S as the separator for object code

####################################################################
# List of object files
XGLOCKOBJS = xglock$(O)

# List of source files
XGLOCKSRCS = $(VPATH)/xglock$(C)

# default target
all : 

# this tells GNU make not to export variables into the environment
# But other makes do not understand its significance, so it must
# not be the first target in the file. So it is here, before
# any variables are created, but after the default target
.NOEXPORT :

SHELL = /bin/sh

prefix = /usr/X11R6
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
datadir = /usr/X11R6
mandir = /usr/X11R6/man/man1

CONFIGDIR = $(srcdir)/config/

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTPGMFLAGS = -s -g auth -m 2755

#CC = cc -g
#CC = cc -Ac -g
#CC = cc -Xc -g
#CC = acc -g
#CC = CC -g
#CC = gcc -g -Wall -ansi -pedantic
#CC = gcc -g -Wall
#CC = g++ -g -Wall
CC = clang.old -Wnested-externs -Wno-format

#LINT = lint
LINT = lint -Ncheck=%all
#LINT = alint

#DEPEND = makedepend
DEPEND = makedepend
DEPEND_FLAGS = 
DEPEND_DEFINES = 

LN_S = ln -s
RM = rm -f
RM_S = $(RM)
ECHO = echo

#BLN_S = set file/enter=[]
#RM = delete/noconfirm/nolog
#RM_S = set file/remove/nolog
#ECHO = write sys$output

DEFS = -DHAVE_CONFIG_H $(DEFINES) -DXGLOCKRC_FILE=\"$(datadir)/xlock/xglockrc\"
XGLOCKINC =  -I.. -I$(top_srcdir)
CFLAGS =  -O2 -pipe  
#CFLAGS = -O
#CFLAGS = -g
XGLOCKLDFLAGS = 
XLIBS = /usr/X11R6/lib
XGLOCKLIBS =   
#If you have purify, and want to use it, uncomment this definition or
# run the make as `make PURIFY=purify'
# or run configure with the --with-purify argument.
PURIFY = 

xglock : $(XGLOCKOBJS)
	$(PURIFY) $(CC) -o $@ $(XGLOCKOBJS) $(XGLOCKLDFLAGS) $(XGLOCKLIBS)
	@ $(ECHO) "$@ BUILD COMPLETE"
	@ $(ECHO) ""

.SUFFIXES : $(C) $(O)

$(C)$(O) :
	$(CC) -c $(CPPFLAGS) $(DEFS) $(XGLOCKINC) $(CFLAGS) $<

install : 

install_xglock : install-program install-man install-ad
	@ $(ECHO) "$@ COMPLETE"
	@ $(ECHO) ""

install-program : xglock
	$(top_srcdir)/mkinstalldirs $(bindir)
	$(INSTALL_PROGRAM) xglock$(E) $(bindir)

install-man :

install-ad :
	$(top_srcdir)/mkinstalldirs $(datadir)/xlock
	$(INSTALL_PROGRAM) $(top_srcdir)/xglock/xglockrc $(datadir)/xlock/xglockrc

uninstall : 

uninstall_xglock : uninstall-program uninstall-man uninstall-ad

uninstall-program :
	$(RM) $(bindir)/xglock$(E)

uninstall-man :

uninstall-ad :
	$(RM) $(datadir)/xlock/xglockrc

install.program : install-program

install.man : install-man

install.ad : install-ad

uninstall.program : uninstall-program

uninstall.man : uninstall-man

uninstall.ad : uninstall-ad

depend :

lint :
	$(LINT) -ax -DLINT $(DEFS) $(XGLOCKINC) $(XGLOCKSRCS)

xrdb :

man :

html :

hlp :

clean :
	$(RM) *.o core *~ *% *.bak *.orig *.rej make.log MakeOut *.patch .pure
	$(RM) xglock xglock.exe

distclean : clean
	$(RM) Makefile

clean.all : distclean

# Adds all current dependencies to Makefile
depend :
	$(DEPEND) -s '# DO NOT DELETE: updated by make depend'              \
	$(DEPEND_FLAGS) --                                                  \
	$(XGLOCKINC) $(DEFS) $(DEPEND_DEFINES) $(CFLAGS) --                 \
	$(XGLOCKSRCS)

# Adds some dependencies to Makefile.in -- not totally accurate, but pretty
# close.  This excludes dependencies on files in /usr/include, etc.  It tries
# to include only dependencies on files which are themselves a part of this
# package. -w 0
distdepend :
	@echo updating dependencies in `pwd`/Makefile.in... ;               \
	$(DEPEND) -w 0 -f -                                                 \
	-s '# DO NOT DELETE: updated by make distdepend' $(DEPEND_FLAGS) -- \
	$(XGLOCKINC) $(DEFS) $(DEPEND_DEFINES) $(CFLAGS) --                 \
	$(XGLOCKSRCS) |                                                     \
	(                                                                   \
	  awk '/^#.*Id : Makefile.in/,/^# DO .*distdepend/' < Makefile.in ; \
	  sed -e 's@ \./@ @g;s@ /[^ ]*@@g;/^.*:$$/d'                        \
	      -e 's@\.\./bitmaps@$$(BITMAPDIR)@g' ;                         \
	  echo ''                                                           \
	) > /tmp/distdepend.$$$$ &&                                         \
	mv Makefile.in Makefile.in.bak &&                                   \
	mv /tmp/distdepend.$$$$ Makefile.in

##############################################################################
#
# DO NOT DELETE: updated by make distdepend

xglock.o: ../config.h
xglock.o: modes.h
xglock.o: logo.h

