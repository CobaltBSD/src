PROG=	login_lchpass
OBJS=	login_lchpass.o local_passwd.o pwd_check.o
MAN=	login_lchpass.8

CFLAGS+=-Wall -Wno-unused
LIBS=	-lutil

BINOWN=	root
BINGRP= auth
BINMODE=4555
BINDIR= /usr/libexec/auth

include cobalt.prog.mk
