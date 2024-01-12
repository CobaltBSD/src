#	$OpenBSD: Makefile,v 1.55 2021/05/01 16:10:33 visa Exp $

SUBDIR=	special notes

.if	make(obj)
SUBDIR+=amd64 armv7 arm64 i386
.elif exists(${MACHINE})
SUBDIR+=${MACHINE}
.endif

.include <bsd.subdir.mk>
