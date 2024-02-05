#	$OpenBSD: Makefile,v 1.2 2023/08/14 08:56:20 kn Exp $

PROG=	fsck
SRCS=	fsck.c fsutil.c preen.c
DPADD=	${LIBUTIL}
LDADD=	-lutil

.PATH:  ${.CURDIR}/../../../usr.sbin/fsck
.include <bsd.prog.mk>
