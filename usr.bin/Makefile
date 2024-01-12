#	$OpenBSD: Makefile,v 1.168 2022/06/29 08:39:49 job Exp $

.include <bsd.own.mk>

# tail tcpbench tee time timeout
# top touch tr true ts tsort tty usbhidaction usbhidctl
#TODO: replace `compress` with `pigz`

SUBDIR= apply at audioctl awk \
	cal calendar cap_mkdb cdio chpass col colrm \
	column crontab csplit ctags ctfconv ctfdump \
	cu \
	deroff diff3 dig du encrypt env expand file \
	find fgen finger fmt from fstat gencat getcap \
	getconf getent gprof grep head hexdump id \
	ipcrm ipcs \
	join kdump kstat ktrace \
	last lastcomm \
	lndir \
	locate lock login look lorder \
	m4 make \
	mixerctl mkdep netstat \
	newsyslog \
	nice nm nohup pagesize passwd paste patch pctr \
	pkill \
	pr \
	renice rpcgen rpcinfo \
	sdiff script sed shar signify \
	sort spell stat su systat \
	tail tcpbench tee time \
	top ts usbhidaction usbhidctl \
	ul unexpand \
	users uudecode uuencode vmstat w \
	what which who whois xargs xinstall \
	yacc \
	chmod df ps sync \
	chio mt stty test banner2 factor fortune grdc morse number primes tetris worm

.if (${YP:L} == "yes")
.endif

.include <bsd.subdir.mk>
