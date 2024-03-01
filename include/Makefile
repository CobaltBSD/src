FILES=	a.out.h ar.h asr.h assert.h \
	bitstring.h blf.h bsd_auth.h \
	complex.h cpio.h ctype.h curses.h \
	db.h dirent.h dlfcn.h \
	elf.h elf_abi.h err.h errno.h \
	fenv.h float.h fnmatch.h fstab.h fts.h ftw.h \
	getopt.h glob.h grp.h \
	icdb.h ieeefp.h ifaddrs.h inttypes.h iso646.h \
	kvm.h \
	langinfo.h libgen.h limits.h link.h link_elf.h locale.h login_cap.h \
	math.h md5.h memory.h \
	ndbm.h netdb.h netgroup.h nlist.h nl_types.h \
	paths.h poll.h pthread.h pthread_np.h pwd.h \
	ranlib.h readpassphrase.h regex.h resolv.h rmd160.h \
	sched.h search.h setjmp.h semaphore.h sha1.h sha2.h \
	signal.h siphash.h spawn.h stdbool.h stddef.h \
	stdio.h stdlib.h string.h strings.h sysexits.h \
	tar.h tgmath.h tib.h time.h ttyent.h \
	uchar.h unistd.h utime.h utmp.h uuid.h \
	vis.h  \
	wchar.h wctype.h arpa/ftp.h arpa/inet.h arpa/nameser.h arpa/telnet.h arpa/tftp.h protocols/dumprestore.h protocols/routed.h protocols/rwhod.h protocols/talkd.h protocols/timed.h rpc/auth.h rpc/auth_unix.h rpc/clnt.h rpc/pmap_clnt.h rpc/pmap_prot.h rpc/pmap_rmt.h rpc/rpc.h rpc/rpc_des.h rpc/rpc_msg.h rpc/svc.h rpc/svc_auth.h rpc/types.h rpc/xdr.h rpcsvc/yp_prot.h rpcsvc/ypclnt.h

all:

install:
	for I in ${FILES}; do \
		${INSTALL} -D -c -m 444  $$I ${DESTDIR}/usr/include/$$I; \
	done

clean:
