PROG=	user
OBJS=	user.o main.o

LIBS=	-lutil

BINDIR=${SBINDIR}
SYMLINKS+=	${SBINDIR}/useradd
SYMLINKS+=	${SBINDIR}/userdel
SYMLINKS+=	${SBINDIR}/usermod
SYMLINKS+=	${SBINDIR}/group
SYMLINKS+=	${SBINDIR}/groupadd
SYMLINKS+=	${SBINDIR}/groupdel
SYMLINKS+=	${SBINDIR}/groupmod
SYMLINKS+=	${SBINDIR}/userinfo
SYMLINKS+=	${SBINDIR}/groupinfo

MAN=	usermgmt.conf.5 user.8 useradd.8 userdel.8 usermod.8 userinfo.8 \
	group.8 groupadd.8 groupdel.8 groupmod.8 groupinfo.8

include cobalt.prog.mk
