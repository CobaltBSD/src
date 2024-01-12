#	$OpenBSD: Makefile,v 1.8 2010/06/05 07:36:23 jsing Exp $

PROG=	fsdb
MAN=	fsdb.8
SRCS=	fsdb.c fsdbutil.c fsutil.c \
	dir.c inode.c pass1.c pass1b.c pass2.c pass3.c pass4.c \
	pass5.c preen.c setup.c utilities.c ffs_subr.c ffs_tables.c
CFLAGS+= -I${.CURDIR}/../../usr.sbin/fsck -I${.CURDIR}/../../usr.sbin/fsck_ffs
LDADD+= -ledit -lcurses -lutil
DPADD+=	${LIBEDIT} ${LIBCURSES} ${LIBUTIL}
.PATH:	${.CURDIR}/../../usr.sbin/fsck ${.CURDIR}/../../usr.sbin/fsck_ffs ${.CURDIR}/../../sys/ufs/ffs

.include <bsd.prog.mk>
