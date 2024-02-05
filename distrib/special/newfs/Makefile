#	$OpenBSD: Makefile,v 1.3 2014/12/23 17:16:02 deraadt Exp $

PROG=	newfs
SRCS=	dkcksum.c getmntopts.c newfs.c mkfs.c

CFLAGS+= -I${.CURDIR}/../../../usr.sbin/mount

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.PATH:  ${.CURDIR}/../../../usr.sbin/newfs
.PATH:  ${.CURDIR}/../../../usr.sbin/mount
.PATH:	${.CURDIR}/../../../usr.sbin/disklabel
.include <bsd.prog.mk>
