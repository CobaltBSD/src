PROG=	syslogd
OBJS=	evbuffer_tls.o log.o parsemsg.o privsep.o privsep_fdpass.o ringbuf.o \
	syslogd.o ttymsg.o
MAN=	syslogd.8 syslog.conf.5
LIBS=	-levent -ltls
BINDIR=${SBINDIR}

include cobalt.prog.mk
