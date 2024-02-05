OSrev=1.0
OSREV=${OSrev}
MACHINE=amd64
RELEASEDIR=/${DESTDIR}

FS=		miniroot${OSrev}.img
FSSIZE=		113920
CDROM=		cd${OSrev}.iso
MOUNT_POINT=	/mnt
LISTS=		${CURDIR}/list
UTILS=		${CURDIR}/../../miniroot
MTREE=		${UTILS}/mtree.conf
RAMDISK=	RAMDISK_CD

MOUNT_ARGS_msdos=-o-s

EFIBOOT=	${DESTDIR}/usr/mdec/BOOTX64.EFI ${DESTDIR}/usr/mdec/BOOTIA32.EFI

all: ${FS} ${CDROM}

${FS}: bsd.gz
	dd if=/dev/zero of=${FS} bs=512 count=${FSSIZE}
	vnconfig -v ${FS} > vnd
	fdisk -yi -l ${FSSIZE} -b 960 -f ${DESTDIR}/usr/mdec/mbr `cat vnd`
	echo '/ *' | disklabel -wAT- `cat vnd`
	newfs -t msdos /dev/r`cat vnd`i
	mount ${MOUNT_ARGS_msdos} /dev/`cat vnd`i ${MOUNT_POINT}
	mkdir -p ${MOUNT_POINT}/efi/boot
	cp ${EFIBOOT} ${MOUNT_POINT}/efi/boot
	umount ${MOUNT_POINT}
	newfs -O 1 -m 0 -o space -i 524288 -c ${FSSIZE} /dev/r`cat vnd`a
	mount /dev/`cat vnd`a ${MOUNT_POINT}
	objcopy -S -R .comment ${DESTDIR}/usr/mdec/boot ${CURDIR}/boot
	installboot -v -r ${MOUNT_POINT} `cat vnd` \
	    ${DESTDIR}/usr/mdec/biosboot ${CURDIR}/boot
	install -c -m 555 -o root -g wheel bsd.gz ${MOUNT_POINT}/bsd
	df -i ${MOUNT_POINT}
	umount ${MOUNT_POINT}
	vnconfig -u `cat vnd`
	rm -f vnd

${CDROM}: bsd.rd
	rm -rf ${CURDIR}/cd-dir
	mkdir -p ${CURDIR}/cd-dir/${OSREV}/${MACHINE}
	mkdir -p ${CURDIR}/cd-dir/etc
	echo "set image /${OSREV}/${MACHINE}/bsd.rd" > ${CURDIR}/cd-dir/etc/boot.conf
	cp ${CURDIR}/bsd.rd ${CURDIR}/cd-dir/${OSREV}/${MACHINE}
	cp ${DESTDIR}/usr/mdec/cdbr ${CURDIR}/cd-dir/${OSREV}/${MACHINE}
	#cp ${DESTDIR}/usr/mdec/cdboot ${CURDIR}/cd-dir/${OSREV}/${MACHINE}/cdboot
	cp ${DESTDIR}/usr/mdec/cdboot ${CURDIR}/cd-dir/cdboot
	mkhybrid -a -R -T -L -l -d -D -N -o ${CURDIR}/${CDROM} \
	    -A "CobaltBSD ${OSREV} ${MACHINE} bootonly CD" \
	    -P "Copyright (c) `date +%Y` Gary Sneed, The CobaltBSD project" \
	    -p "Gary Sneed <tbd@tbd>" \
	    -V "CobaltBSD/${MACHINE}   ${OSREV} boot-only CD" \
	    -b ${OSREV}/${MACHINE}/cdbr -c ${OSREV}/${MACHINE}/boot.catalog \
	    ${CURDIR}/cd-dir

MRDISKTYPE=	rdrootc
MRMAKEFSARGS=	-o disklabel=${MRDISKTYPE},minfree=0,density=4096

bsd.gz: bsd.rd
	objcopy -g -x -R .comment -R .SUNW_ctf \
	    -K rd_root_size -K rd_root_image \
	    bsd.rd bsd.strip
	gzip -9cn bsd.strip > bsd.gz

bsd.rd: mr.fs
	cp bsd bsd.rd
	rdsetroot bsd.rd mr.fs

#bsd:
#	cd ${CURDIR}/../../../sys/arch/${MACHINE}/compile/${RAMDISK} && \
#	    su ${BUILDUSER} -c '${MAKE} config && ${MAKE} clean && exec ${MAKE}'
#	cp -p ${CURDIR}/../../../sys/arch/${MACHINE}/compile/${RAMDISK}/obj/bsd bsd

#mr.fs: instbin bsd
mr.fs:
	rm -rf $@.d
	install -d -o root -g wheel $@.d
	mtree -def ${MTREE} -p $@.d -u
	#CURDIR=${.CURDIR} OBJDIR=${.OBJDIR} OSrev=${OSrev} \
	#    TARGDIR=$@.d UTILS=${UTILS} RELEASEDIR=${RELEASEDIR} \
	#    sh ${UTILS}/runlist.sh ${LISTS}
	cp -v \
		/bin/ksh \
		/bin/sh \
		$@.d/bin
	cp -v \
		/usr/bin/ls \
		/usr/bin/df \
		/usr/bin/du \
		$@.d/usr/bin
	cp -v \
		/sbin/init \
		$@.d/sbin
	cp -v \
		/usr/mdec/mbr \
		$@.d/usr/mdec
	cp -v \
		/dev/MAKEDEV \
		$@.d/dev
	(cd $@.d/dev && sh MAKEDEV std)
	cp -rv \
		/etc/rc \
		$@.d/etc
	makefs ${MRMAKEFSARGS} $@ $@.d

unconfig:
	-umount -f ${MOUNT_POINT}
	-[ -f vnd ] && vnconfig -u `cat vnd` && rm -f vnd

install:
	cp bsd.gz ${RELEASEDIR}/bsd.rd
	chmod a+r ${RELEASEDIR}/bsd.rd
	cp ${FS} ${RELEASEDIR}
	cp ${CDROM} ${RELEASEDIR}

clean:
	rm -f mr.fs bsd.rd bsd.gz bsd.strip vnd ${FS} ${CDROM}
	#rm -f bsd
	rm -rf mr.fs.d cd-dir

#.include <bsd.obj.mk>
