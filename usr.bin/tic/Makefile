#	$NetBSD: Makefile,v 1.2 2012/05/31 20:10:06 joerg Exp $

PROG=		tic
SRCS= tic.c cdbw.c mi_vector_hash.c
WARNS=		4

CPPFLAGS+=	-I${.CURDIR}/../../lib/libterminfo

.ifndef HOSTPROG
LDADD+=		-lterminfo -lutil
DPADD+=		${LIBTERMINFO} ${LIBUTIL}
.endif

.include <bsd.prog.mk>
