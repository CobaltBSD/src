# $Id : Makefile.in 4.16 2000/01/17 $
#
# xlockmore Makefile.in for autoconf (UNIX/VMS X11 support)
############################################################

# 

srcdir = .
top_srcdir = ../..

PIXMAPDIR = $(top_srcdir)/pixmaps/
UTILDIR = $(top_srcdir)/xlock/
MODEDIR = $(top_srcdir)/modes/
GLDIR = $(top_srcdir)/modes/glx/
UTILOBJDIR = ../../xlock/
MODEOBJDIR = ../
GLOBJDIR = ./

N=
O=.o
#O=.obj
C=.c
CX=.cc
S=$(N) $(N)
#S=,
M=.xlk
E=
#E=.exe

DU = $(UTILDIR)
DOU = $(UTILOBJDIR)
DG = $(GLDIR)
DOG = $(GLOBJDIR)
OU = $(O)$(S)$(DOU)
OG = $(O)$(S)$(DOG)
CU = $(C) $(DU)
CG = $(C) $(DG)
CXG = $(CX) $(DG)

# please define
# C as the C source code extension
# CX as the C++ source code extension
# O as the object extension
# S as the separator for object code

##CONSTRUCTIONGLOBJS =
##XLOCKUNSTABLEGLOBJS = $(DOG)skewb$(O)$(S)$(CONSTRUCTIONGLOBJS)
#INVERTOBJS = $(DOG)i_figureeight$(O)$(S)\
#$(DOG)i_linkage$(OG)i_sphere$(OG)i_spline$(O)$(S)\
#$(DOG)i_threejet$(OG)i_threejetvec$(O)$(S)\
#$(DOG)i_twojet$(OG)i_twojetvec$(O)
#XLOCKDEPCPPGLOBJS = $(INVERTOBJS)
#XLOCKMULTCPPGLOBJS = $(DOG)invert$(O)
##XLOCKTEXTGLOBJS = $(DOG)text3d$(O)
##XLOCKTEXTGLOBJS = $(DOG)text3d2$(OG)rotator$(O)
#SPROINGIESOBJS = $(DOG)buildlwo$(OG)sproingiewrap$(OG)s1_b$(O)$(S)\
#$(DOG)s1_1$(OG)s1_2$(OG)s1_3$(OG)s1_4$(OG)s1_5$(OG)s1_6$(O)
#ATLANTISOBJS = $(DOG)dolphin$(OG)shark$(OG)swim$(OG)whale$(O)
#ATUNNELSOBJS = $(DOG)tunnel_draw$(O)
#BUBBLE3DOBJS = $(DOG)b_draw$(OG)b_sphere$(OG)b_lockglue$(O)
#GLPLANETOBJS = $(DOG)sphere$(O)
#MOLECULEOBJS = $(DOG)tube$(OG)sphere$(O)
#XLOCKDEPGLOBJS = $(DOG)xpm-ximage$(OG)pipeobjs$(O)$(S)\
#$(SPROINGIESOBJS)$(S)$(ATLANTISOBJS)$(S)$(ATUNNELSOBJS)$(S)\
#$(BUBBLE3DOBJS)$(S)$(MOLECULEOBJS)$(S)$(XLOCKDEPCPPGLOBJS)
#XLOCKNORMGLOBJS = $(DOG)biof$(OG)cage$(OG)gears$(O)$(S)\
#$(DOG)moebius$(OG)morph3d$(OG)noof$(O)$(S)\
#$(DOG)rubik$(OG)sierpinski3d$(OG)stairs$(OG)superquadrics$(O)$(S)\
#$(XLOCKTEXTGLOBJS)$(S)$(XLOCKUNSTABLEGLOBJS)
#XLOCKMULTGLOBJS = $(DOG)fire$(OG)lament$(OG)sballs$(OG)molecule$(O)$(S)\
#$(DOG)pipes$(OG)sproingies$(OG)atlantis$(OG)atunnels$(O)$(S)\
#bubble3d$(OG)glplanet$(O)$(S)$(XLOCKMULTCPPGLOBJS)
XLOCKGLOBJS = $(XLOCKNORMGLOBJS)$(S)\
$(XLOCKDEPGLOBJS)$(S)$(XLOCKMULTGLOBJS)
# default target
all : $(XLOCKGLOBJS)

# this tells GNU make not to export variables into the environment
# But other makes do not understand its significance, so it must
# not be the first target in the file. So it is here, before
# any variables are created, but after the default target
.NOEXPORT :

SHELL = /bin/sh

prefix = /usr/X11R6
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
mandir = /usr/X11R6/man/man1
xapploaddir = /usr/X11R6/share/X11/app-defaults

#CC = cc -g
#CC = cc -Ac -g
#CC = cc -Xc -g
#CC = acc -g
#CC = CC -g
#CC = gcc -g -Wall -ansi -pedantic
#CC = gcc -g -Wall -Wstrict-prototypes -Wnested-externs -Wno-format
#CC = gcc -g -Wall -W -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings -Waggregate-return -Wmissing-prototypes -Wstrict-prototypes
#CC = g++ -g -Wall
CC = clang.old -Wnested-externs -Wno-format
#CXX = g++ -fpermissive
#CXX = g++ -g -Wall -Wstrict-prototypes -Wnested-externs -Wno-format
CXX = c++.old

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

DEFINES = -DDEF_FILESEARCHPATH=\"$(xapploaddir)/%N%C%S:$(xapploaddir)/%N%S\"
DEFS = -DHAVE_CONFIG_H $(DEFINES)
XLOCKINC = -I. -I.. -I../.. -I$(UTILDIR) -I$(top_srcdir) -I/usr/X11R6/include  -I/usr/X11R6/include -I/usr/X11R6/include/freetype2 -I/usr/X11R6/include
CFLAGS = -O2 -pipe  
CXXFLAGS = -O2 -pipe 
#CXXFLAGS = $(CPPFLAGS) $(DEFS) $(XLOCKINC) $(CFLAGS) # Why ???? The rule doesn't
#CFLAGS = -O
#CFLAGS = -g

#If you have purify, and want to use it, uncomment this definition or
# run the make as `make PURIFY=purify'
# or run configure with the --with-purify argument.
PURIFY = 

.SUFFIXES : $(C) $(CX) $(O)

$(C)$(O) :
	$(CC) -c $(CPPFLAGS) $(DEFS) $(XLOCKINC) $(CFLAGS) $<

$(CX)$(O) :
	$(CXX) -c $(CPPFLAGS) $(DEFS) $(XLOCKINC) $(CXXFLAGS) $<

install :

install-program :

install-man :

install-ad :

uninstall :

uninstall-program :

uninstall-man :

uninstall-ad :

install.program : install-program

install.man : install-man

install.ad : install-ad

uninstall.program : uninstall-program

uninstall.man : uninstall-man

uninstall.ad : uninstall-ad

lint :

xrdb :

man :

html :

hlp :

clean :
	$(RM) *.o *.xlk core *~ *% *.bak *.orig *.rej *.patch .pure
	$(RM) make.log MakeOut Makefile.dep

distclean : clean
	$(RM) Makefile

clean.all : distclean

# Adds all current dependencies to Makefile
depend :
	$(DEPEND) -s '# DO NOT DELETE: updated by make depend'              \
	$(DEPEND_FLAGS) --                                                  \
	$(XLOCKINC) $(DEFS) $(DEPEND_DEFINES) $(CFLAGS) --                  \
	$(XLOCKGLSRCS)

# Adds some dependencies to Makefile.in -- not totally accurate, but pretty
# close.  This excludes dependencies on files in /usr/include, etc.  It tries
# to include only dependencies on files which are themselves a part of this
# package.
distdepend :
	@echo updating dependencies in `pwd`/Makefile.in... ;               \
	$(DEPEND) -w 0 -f -                                                 \
	-s '# DO NOT DELETE: updated by make distdepend' $(DEPEND_FLAGS) -- \
	$(XLOCKINC) $(DEFS) $(DEPEND_DEFINES) $(CFLAGS) --                  \
	$(XLOCKGLSRCS) |                                                    \
	(                                                                   \
	  awk '/^#.*Id : Makefile.in/,/^# DO .*distdepend/' < Makefile.in ; \
	  sed -e 's@ \./@ @g;s@ /[^ ]*@@g;/^.*:$$/d'                        \
	      -e 's@^\.\./\.\./modes/glx@$$(GLOBJDIR)@'                     \
	      -e 's@\.\./\.\./pixmaps@$$(PIXMAPDIR)@g'                      \
	      -e 's@\.\./\.\./xlock@$$(UTILDIR)@g' ;                        \
	  echo ''                                                           \
	) > /tmp/distdepend.$$$$ &&                                         \
	mv Makefile.in Makefile.in.bak &&                                   \
	mv /tmp/distdepend.$$$$ Makefile.in

##############################################################################
#
# DO NOT DELETE: updated by make distdepend

