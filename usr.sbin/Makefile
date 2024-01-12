#	$OpenBSD: Makefile,v 1.215 2022/06/28 18:47:54 claudio Exp $

.include <bsd.own.mk>

SUBDIR=	ac accton acpidump adduser apm apmd arp authpf \
	btrace config cron crunchgen dev_mkdb \
	dhcpleasectl \
	hostctl \
	hotplugd ifstated installboot iostat \
	kgmon kvm_mkdb \
	makefs memconfig \
	mkuboot mtree netgroup_mkdb \
	pcidump portmap procmap pstat pwd_mkdb \
	rcctl rdsetroot \
	rmt route6d \
	sa sensorsd \
	syslogc syslogd \
	tcpdrop traceroute \
	usbdevs user vmd vmctl vipw \
	watchdogd wsconscfg wsfontload wsmoused \
	badsect bioctl dhclient dhcpleased disklabel dmesg dump dumpfs fdisk fsck fsck_ext2fs fsck_ffs fsck_hammer2 fsck_msdos fsdb fsirand growfs hammer2 ifconfig init kbd ldattach mknod mount mount_cd9660 mount_ext2fs mount_ffs mount_hammer2 mount_msdos mount_ntfs mount_tmpfs mount_vnd ncheck_ffs newfs newfs_ext2fs newfs_hammer2 newfs_msdos nologin pfctl pflogd ping reboot resolvd restore route savecore scan_ffs scsi shutdown sysctl ttyflags tunefs umount vnconfig wsconsctl

.if (${YP:L} == "yes")
.endif

.include <bsd.subdir.mk>
