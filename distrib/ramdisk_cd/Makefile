OSrev=1.0
OSREV=${OSrev}
MACHINE=amd64
RELEASEDIR=/${DESTDIR}

CDROM=		cd${OSrev}.iso
LISTS=		${CURDIR}/list
UTILS=		${CURDIR}/../../miniroot
MTREE=		${UTILS}/mtree.conf
RAMDISK=	RAMDISK_CD

MOUNT_ARGS_msdos=-o-s

EFIBOOT=	${DESTDIR}/usr/mdec/BOOTX64.EFI ${DESTDIR}/usr/mdec/BOOTIA32.EFI

all: ${CDROM}

${CDROM}: bsd.rd
	rm -rf ${CURDIR}/cd-dir
	mkdir -p ${CURDIR}/cd-dir/etc
	mkdir -p ${CURDIR}/cd-dir/efi/boot
	cp -v \
		/usr/mdec/BOOTIA32.EFI \
		/usr/mdec/BOOTX64.EFI \
		${CURDIR}/cd-dir/efi/boot
	echo "set image /bsd.rd" > ${CURDIR}/cd-dir/etc/boot.conf
	cp ${CURDIR}/bsd.rd ${CURDIR}/cd-dir
	cp ${DESTDIR}/usr/mdec/cdbr ${CURDIR}/cd-dir
	cp ${DESTDIR}/usr/mdec/cdboot ${CURDIR}/cd-dir/cdboot
	dd if=/dev/random of=${CURDIR}/cd-dir/etc/random.seed bs=512 count=1 status=none
	mkhybrid -a -R -T -L -l -d -D -N -o ${CURDIR}/${CDROM} \
	    -A "CobaltBSD ${OSREV} ${MACHINE} bootonly CD" \
	    -P "Copyright (c) `date +%Y` Gary Sneed, The CobaltBSD project" \
	    -p "Gary Sneed <tbd@tbd>" \
	    -V "Cobalt/${MACHINE}   ${OSREV} boot-only CD" \
	    -b cdbr -c boot.catalog \
	    ${CURDIR}/cd-dir

MRDISKTYPE=	rdrootc
MRMAKEFSARGS=	-o disklabel=${MRDISKTYPE},minfree=0,density=4096

bsd.rd: mr.fs
	cp bsd bsd.rd
	rdsetroot bsd.rd mr.fs

#bsd:
#	cd ${CURDIR}/../../../sys/arch/${MACHINE}/compile/${RAMDISK} && \
#	    su ${BUILDUSER} -c '${MAKE} config && ${MAKE} clean && exec ${MAKE}'
#	cp -p ${CURDIR}/../../../sys/arch/${MACHINE}/compile/${RAMDISK}/obj/bsd bsd

#mr.fs: bsd
mr.fs:
	rm -rf $@.d
	install -d -o root -g wheel $@.d
	mtree -def ${MTREE} -p $@.d -u
	#CURDIR=${.CURDIR} OBJDIR=${.OBJDIR} OSrev=${OSrev} \
	#    TARGDIR=$@.d UTILS=${UTILS} RELEASEDIR=${RELEASEDIR} \
	#    sh ${UTILS}/runlist.sh ${LISTS}
	# Prepare ramdisk filesystem
	#XXX
	cp -v \
		/dev/MAKEDEV \
		$@.d/dev
	cp -v \
		/bin/ksh \
		/bin/sh \
		/bin/rm \
		/bin/chmod \
		/bin/find \
		/bin/mktemp \
		/bin/cat \
		$@.d/bin
	cp -v \
		/usr/bin/ls \
		/usr/bin/df \
		/usr/bin/du \
		/usr/bin/mkdir \
		/usr/bin/ln \
		/usr/bin/grep \
		/usr/bin/uname \
		/usr/bin/sed \
		/usr/bin/su \
		/usr/bin/clear \
		/usr/bin/install \
		/usr/bin/cp \
		/usr/bin/mv \
		/usr/bin/unpigz \
		/usr/bin/gunzip \
		/usr/bin/tcc \
		/usr/bin/make \
		/usr/bin/cc \
		/usr/bin/tar \
		/usr/bin/bsdtar \
		/usr/bin/chgrp \
		/usr/bin/basename \
		/usr/bin/strip \
		/usr/bin/egrep \
		/usr/bin/fgrep \
		/usr/bin/zgrep \
		/usr/bin/zegrep \
		/usr/bin/zfgrep \
		/usr/bin/sort \
		/usr/bin/yacc \
		/usr/bin/lex \
		$@.d/usr/bin
	cp -v \
		/sbin/init \
		/sbin/swapctl \
		/sbin/fsck \
		/sbin/mount \
		/sbin/fsck_ffs \
		/sbin/sysctl \
		/sbin/ifconfig \
		/sbin/ldconfig \
		/sbin/chown \
		/sbin/dev_mkdb \
		/sbin/mount_ffs \
		/sbin/umount \
		$@.d/sbin
	cp -v \
		/usr/sbin/disklabel \
		/usr/sbin/mknod \
		/usr/sbin/user \
		/usr/sbin/mount_tmpfs \
		/usr/sbin/dmesg \
		/usr/sbin/ttyflags \
		/usr/sbin/fdisk \
		/usr/sbin/installboot \
		/usr/sbin/newfs \
		/usr/sbin/chroot \
		/usr/sbin/mount_msdos \
		$@.d/usr/sbin
	cp -rv \
		/usr/libexec/ld.so \
		/usr/libexec/reorder_kernel \
		$@.d/usr/libexec
	cp -rv \
		/usr/mdec \
		$@.d/usr
	cp -rv \
		/usr/lib/libc.so.97.1 \
		/usr/lib/libutil.so.18.0 \
		/usr/lib/libncursestw.so.6 \
		/usr/lib/libpthread.so.27.1 \
		/usr/lib/libutil.so.17.0 \
		/usr/lib/libz.so.7.0 \
		/usr/lib/libm.so.10.1 \
		/usr/lib/tcc \
		/usr/lib/crt0.o \
		/usr/lib/crtbegin.o \
		/usr/lib/crtend.o \
		/usr/lib/libarchive.so.20.2 \
		/usr/lib/libcrypto.so.52.0 \
		/usr/lib/libexpat.so.14.0 \
		/usr/lib/liblzma.so.9.5 \
		/usr/lib/libbz2.so.1.0 \
		/usr/lib/crtbeginS.o \
		/usr/lib/crtendS.o \
		/usr/lib/libbfd-2.17.so \
		/usr/lib/libiberty.so.12.0 \
		/usr/lib/libelf.so.3.0 \
		/usr/lib/libkvm.so.17.0 \
		/usr/lib/libc.a \
		/usr/lib/libedit.so.5.2 \
		/usr/lib/libevent.so.4.1 \
		/usr/lib/libcurses.so.14.0 \
		/usr/lib/libsndio.so.7.2 \
		/usr/lib/libusbhid.so.7.1 \
		/usr/lib/libutil.a \
		/usr/lib/libdialog.a \
		$@.d/usr/lib
	cp -rv \
		/etc/rc \
		${CURDIR}/passwd \
		${CURDIR}/group \
		/etc/shells \
		/etc/gettytab \
		/etc/ttys \
		/etc/login.conf \
		${CURDIR}/issue \
		${CURDIR}/master.passwd \
		/etc/pwd.db \
		/etc/spwd.db \
		$@.d/etc
	cp -rv \
		${CURDIR}/../../../include \
		$@.d/usr
	rm -v $@.d/usr/include/Makefile
	cp -rv \
		${CURDIR}/../../../sys/sys \
		${CURDIR}/../../../lib/libutil/util.h \
		${CURDIR}/../../../lib/libedit/histedit.h \
		${CURDIR}/../../../lib/libz/zlib.h \
		${CURDIR}/../../../lib/libz/zconf.h \
		${CURDIR}/../../../lib/libelf/gelf.h \
		${CURDIR}/../../../lib/libelf/libelf.h \
		${CURDIR}/../../../lib/libevent/event.h \
		/usr/include/ncurses.h \
		/usr/include/ncurses_dll.h \
		/usr/include/term.h \
		/usr/include/dialog.h \
		/usr/include/dlg_config.h \
		${CURDIR}/../../../lib/libutil/ohash.h \
		${CURDIR}/../../../lib/libutil/imsg.h \
		/usr/include/sndio.h \
		/usr/include/unctrl.h \
		/usr/include/usbhid.h \
		$@.d/usr/include
	mkdir $@.d/usr/include/uvm
	cp -v \
		${CURDIR}/../../../sys/uvm/*.h \
		$@.d/usr/include/uvm
	mkdir $@.d/usr/include/netinet
	cp -v \
		${CURDIR}/../../../sys/netinet/*.h \
		$@.d/usr/include/netinet
	mkdir $@.d/usr/include/netinet6
	cp -v \
		${CURDIR}/../../../sys/netinet6/*.h \
		$@.d/usr/include/netinet6
	mkdir $@.d/usr/include/scsi
	cp -v \
		${CURDIR}/../../../sys/scsi/*.h \
		$@.d/usr/include/scsi
	mkdir -p $@.d/usr/include/ufs/{ext2fs,ffs,mfs,ufs}
	cp -v \
		${CURDIR}/../../../sys/ufs/ext2fs/*.h \
		$@.d/usr/include/ufs/ext2fs
	cp -v \
		${CURDIR}/../../../sys/ufs/ffs/*.h \
		$@.d/usr/include/ufs/ffs
	cp -v \
		${CURDIR}/../../../sys/ufs/mfs/*.h \
		$@.d/usr/include/ufs/mfs
	cp -v \
		${CURDIR}/../../../sys/ufs/ufs/*.h \
		$@.d/usr/include/ufs/ufs
	mkdir $@.d/usr/include/net
	cp -v \
		${CURDIR}/../../../sys/net/*.h \
		$@.d/usr/include/net
	mkdir -p $@.d/usr/include/dev/{usb,hid,pv,pci,wscons}
	cp -v \
		/usr/include/dev/usb/usb.h \
		/usr/include/dev/usb/usbhid.h \
		$@.d/usr/include/dev/usb
	cp -v \
		/usr/include/dev/hid/hid.h \
		$@.d/usr/include/dev/hid
	cp -v \
		/usr/include/dev/pv/pvvar.h \
		$@.d/usr/include/dev/pv
	cp -v \
		/usr/include/dev/pci/pcireg.h \
		/usr/include/dev/pci/pcidevs.h \
		/usr/include/dev/pci/pcidevs_data.h \
		$@.d/usr/include/dev/pci
	cp -v \
		/usr/include/dev/wscons/wsconsio.h \
		/usr/include/dev/wscons/wsksymvar.h \
		$@.d/usr/include/dev/wscons
	cp -v \
		/usr/include/dev/biovar.h \
		/usr/include/dev/vndioctl.h \
		/usr/include/dev/softraidvar.h \
		$@.d/usr/include/dev
	mkdir $@.d/usr/include/nfs
	cp -v \
		${CURDIR}/../../../sys/nfs/*.h \
		$@.d/usr/include/nfs
	mkdir $@.d/usr/include/net80211
	cp -v \
		${CURDIR}/../../../sys/net80211/*.h \
		$@.d/usr/include/net80211
	mkdir $@.d/usr/include/msdosfs
	cp -v \
		${CURDIR}/../../../sys/msdosfs/*.h \
		$@.d/usr/include/msdosfs
	mkdir -p $@.d/usr/include/isofs/cd9660
	cp -v \
		${CURDIR}/../../../sys/isofs/cd9660/*.h \
		$@.d/usr/include/isofs/cd9660
	mkdir $@.d/usr/include/netmpls
	cp -v \
		${CURDIR}/../../../sys/netmpls/*.h \
		$@.d/usr/include/netmpls
	mkdir $@.d/usr/share/dict
	cp -v \
		/usr/share/dict/words \
		$@.d/usr/share/dict
	cp -rv \
		${CURDIR}/../../../sys/arch/amd64/include \
		$@.d/usr/include/amd64
	ln -s sys/fcntl.h $@.d/usr/include
	ln -s sys/endian.h $@.d/usr/include
	ln -s machine/frame.h $@.d/usr/include
	ln -s amd64 $@.d/usr/include/machine
	ln -s sys/stdarg.h $@.d/usr/include
	ln -s sys/stdint.h $@.d/usr/include
	ln -s sys/syslog.h $@.d/usr/include
	ln -s sys/termios.h $@.d/usr/include
	ln -s sys/varargs.h $@.d/usr/include
	cp -rv \
		/usr/share/terminfo \
		/usr/share/mk \
		$@.d/usr/share
	cp -v \
		${CURDIR}/README \
		$@.d/
	dd if=/dev/random of=$@.d/etc/random.seed bs=512 count=1 status=none
	(cd $@.d/dev && sh MAKEDEV all)
	cp -rv \
		${CURDIR}/rc \
		$@.d/etc
	mkdir $@.d/etc/rc.d
	gzip -c ${CURDIR}/../../../sys/arch/amd64/compile/GENERIC.MP/bsd > $@.d/bsd.gz # For installing onto disk
	echo > $@.d/etc/fstab
	makefs ${MRMAKEFSARGS} $@ $@.d

clean:
	rm -f mr.fs bsd.rd bsd.gz bsd.strip ${CDROM} boot
	#rm -f bsd
	rm -rf mr.fs.d cd-dir
