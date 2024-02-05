PROG=		btrace
MAN=		bt.5 btrace.8

OBJS=		bt_parse.o btrace.o ksyms.o map.o printf.o

# Use syscall names generated from sys/kern/makesyscalls.sh
OBJS+=		syscalls.o
CFLAGS+=	-DPTRACE -DKTRACE -DACCOUNTING -DNFSCLIENT -DSYSVSHM -DSYSVSEM
CFLAGS+=	-DSYSVMSG
#.PATH:		${.CURDIR}/../../sys/kern

CFLAGS+=	-W -Wall -Wstrict-prototypes -Wno-unused -Wunused-variable
#CFLAGS+=	-I${CURDIR}

#LDADD+=		-lelf

include cobalt.prog.mk
#TODO
