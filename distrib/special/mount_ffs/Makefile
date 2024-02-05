#	$OpenBSD: Makefile,v 1.2 2023/08/14 08:56:21 kn Exp $

PROG=	mount_ffs
SRCS=	mount_ffs.c getmntopts.c

MOUNT=	${.CURDIR}/../../../usr.sbin/mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}

.PATH:  ${.CURDIR}/../../../usr.sbin/mount_ffs
.include <bsd.prog.mk>
