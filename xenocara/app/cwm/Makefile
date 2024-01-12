# $OpenBSD: Makefile,v 1.25 2017/07/14 17:23:38 okan Exp $

.include <bsd.xconf.mk>

PROG=		cwm

SRCS=		calmwm.c screen.c xmalloc.c client.c menu.c \
		search.c util.c xutil.c conf.c xevents.c group.c \
		kbfunc.c parse.y

CPPFLAGS+=	-I${X11BASE}/include -I${X11BASE}/include/freetype2 -I${.CURDIR}

CFLAGS+=	-Wall
YFLAGS=
LDADD+=		-L${X11BASE}/lib -lXft -lXrender -lX11 -lxcb -lXau -lXdmcp \
		-lfontconfig -lexpat -lfreetype -lz -lXrandr -lXext

MANDIR=		${X11BASE}/man/man
MAN=		cwm.1 cwmrc.5

obj: _xenocara_obj

.include <bsd.prog.mk>
.include <bsd.xorg.mk>
