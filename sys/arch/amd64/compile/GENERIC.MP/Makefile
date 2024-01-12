IDENT=-DDDB -DDIAGNOSTIC -DKTRACE -DACCOUNTING -DKMEMSTATS -DPTRACE -DPOOL_DEBUG -DCRYPTO -DSYSVMSG -DSYSVSEM -DSYSVSHM -DUVM_SWAP_ENCRYPT -DFFS -DFFS2 -DFFS_SOFTUPDATES -DUFS_DIRHASH -DQUOTA -DEXT2FS -DMFS -DNFSCLIENT -DNFSSERVER -DCD9660 -DUDF -DMSDOSFS -DFIFO -DFUSE -DHAMMER2 -DSOCKET_SPLICE -DTCP_ECN -DTCP_SIGNATURE -DINET6 -DIPSEC -DPPP_BSDCOMP -DPPP_DEFLATE -DPIPEX -DMROUTING -DMPLS -DBOOT_CONFIG -DUSER_PCICONF -DAPERTURE -DMTRR -DNTFS -DSUSPEND -DHIBERNATE -DPCIVERBOSE -DUSBVERBOSE -DWSDISPLAY_COMPAT_USL -DWSDISPLAY_COMPAT_RAWKBD -DWSDISPLAY_DEFAULTSCREENS="6" -DX86EMU -DONEWIREVERBOSE -DMULTIPROCESSOR
PARAM=-DMAXUSERS=80
S=	/home/tmp/new/src/cobaltbsd/sys
_mach=amd64
_arch=amd64
#	$OpenBSD: Makefile.amd64,v 1.134 2023/09/06 01:47:36 jsg Exp $

# For instructions on building kernels consult the config(8) and options(4)
# manual pages.
#
# N.B.: NO DEPENDENCIES ON FOLLOWING FLAGS ARE VISIBLE TO MAKEFILE
#	IF YOU CHANGE THE DEFINITION OF ANY OF THESE RECOMPILE EVERYTHING
# DEBUG is set to -g by config if debugging is requested (config -g).
# PROF is set to -pg by config if profiling is requested (config -p).

.include <bsd.own.mk>

SIZE?=	size
STRIP?=	ctfstrip

# source tree is located via $S relative to the compilation directory
.ifndef S
S!=	cd ../../../..; pwd
.endif

_machdir?=	$S/arch/${_mach}
_archdir?=	$S/arch/${_arch}

INCLUDES=	-nostdinc -I$S -I${.OBJDIR} -I$S/arch \
		-I$S/dev/pci/drm/include \
		-I$S/dev/pci/drm/include/uapi \
		-I$S/dev/pci/drm/amd/include/asic_reg \
		-I$S/dev/pci/drm/amd/include \
		-I$S/dev/pci/drm/amd/amdgpu \
		-I$S/dev/pci/drm/amd/display \
		-I$S/dev/pci/drm/amd/display/include \
		-I$S/dev/pci/drm/amd/display/dc \
		-I$S/dev/pci/drm/amd/display/amdgpu_dm \
		-I$S/dev/pci/drm/amd/pm/inc \
		-I$S/dev/pci/drm/amd/pm/legacy-dpm \
		-I$S/dev/pci/drm/amd/pm/swsmu \
		-I$S/dev/pci/drm/amd/pm/swsmu/inc \
		-I$S/dev/pci/drm/amd/pm/swsmu/smu11 \
		-I$S/dev/pci/drm/amd/pm/swsmu/smu12 \
		-I$S/dev/pci/drm/amd/pm/swsmu/smu13 \
		-I$S/dev/pci/drm/amd/pm/powerplay/inc \
		-I$S/dev/pci/drm/amd/pm/powerplay/hwmgr \
		-I$S/dev/pci/drm/amd/pm/powerplay/smumgr \
		-I$S/dev/pci/drm/amd/pm/swsmu/inc \
		-I$S/dev/pci/drm/amd/pm/swsmu/inc/pmfw_if \
		-I$S/dev/pci/drm/amd/display/dc/inc \
		-I$S/dev/pci/drm/amd/display/dc/inc/hw \
		-I$S/dev/pci/drm/amd/display/dc/clk_mgr \
		-I$S/dev/pci/drm/amd/display/modules/inc \
		-I$S/dev/pci/drm/amd/display/modules/hdcp \
		-I$S/dev/pci/drm/amd/display/dmub/inc \
		-I$S/dev/pci/drm/i915
CPPFLAGS=	${INCLUDES} ${IDENT} ${PARAM} -D_KERNEL -MD -MP
CWARNFLAGS=	-Werror -Wall -Wimplicit-function-declaration \
		-Wno-pointer-sign \
		-Wframe-larger-than=2047

CMACHFLAGS=	-mcmodel=kernel -mno-red-zone -mno-sse2 -mno-sse -mno-3dnow \
		-mno-mmx -msoft-float -fno-omit-frame-pointer
CMACHFLAGS+=	-ffreestanding ${NOPIE_FLAGS}
SORTR=		sort -R
.if ${IDENT:M-DNO_PROPOLICE}
CMACHFLAGS+=	-fno-stack-protector
.endif
.if ${IDENT:M-DDDB}
CMACHFLAGS+=	-msave-args
.endif
.if ${IDENT:M-DSMALL_KERNEL}
SORTR=		cat
COPTIMIZE=	-Oz
.if ${COMPILER_VERSION:Mclang}
CMACHFLAGS+=	-mno-retpoline -fcf-protection=none
.endif
.else
CMACHFLAGS+=	-mretpoline-external-thunk -fcf-protection=branch
.endif
.if ${COMPILER_VERSION:Mclang}
NO_INTEGR_AS=	-no-integrated-as
CWARNFLAGS+=	-Wno-address-of-packed-member -Wno-constant-conversion \
		-Wno-unused-but-set-variable -Wno-gnu-folding-constant
.endif

DEBUG?=		-g
COPTIMIZE?=	-O2
CFLAGS=		${DEBUG} ${CWARNFLAGS} ${CMACHFLAGS} ${COPTIMIZE} ${COPTS} ${PIPE}
AFLAGS=		-D_LOCORE -x assembler-with-cpp ${CWARNFLAGS} ${CMACHFLAGS}
LINKFLAGS=	-T ld.script -X --warn-common -nopie

HOSTCC?=	${CC}
HOSTED_CPPFLAGS=${CPPFLAGS:S/^-nostdinc$//}
HOSTED_CFLAGS=	${CFLAGS}
HOSTED_C=	${HOSTCC} ${HOSTED_CFLAGS} ${HOSTED_CPPFLAGS} -c $<

NORMAL_C_NOP=	${CC} ${CFLAGS} ${CPPFLAGS} -fno-ret-protector -c $<
NORMAL_C=	${CC} ${CFLAGS} ${CPPFLAGS} ${PROF} -c $<
NORMAL_S=	${CC} ${AFLAGS} ${CPPFLAGS} ${PROF} -c $<

OBJS=	smc93cx6.o pcdisplay_subr.o pcdisplay_chars.o drm_drv.o \
	vga.o vga_subr.o edid.o vesagtf.o videomode.o mii_bitbang.o \
	wdc.o aic7xxx.o aic7xxx_openbsd.o aic7xxx_seeprom.o \
	aic79xx.o aic79xx_openbsd.o aic6360.o adw.o gdt_common.o \
	twe.o ciss.o ami.o mfi.o qlw.o qla.o ahci.o nvme.o mpi.o \
	sili.o ncr53c9x.o siop_common.o siop.o elink3.o if_wi.o \
	if_wi_hostap.o an.o xl.o fxp.o rtl81x9.o re.o dc.o \
	smc91cxx.o smc83c170.o ne2000.o dl10019.o ax88190.o gem.o \
	ti.o com.o pckbc.o ac97.o cy.o lpt.o iha.o lm78.o \
	ar5xxx.o ar5210.o ar5211.o ar5212.o ath.o athn.o ar5008.o \
	ar5416.o ar9280.o ar9285.o ar9287.o ar9003.o ar9380.o \
	bwfm.o atw.o rtw.o rtwn.o rt2560.o rt2661.o rt2860.o \
	acx.o acx111.o acx100.o pgt.o aic6915.o malo.o bwi.o \
	iosf.o uhci.o ohci.o ehci.o xhci.o ccp.o sdhc.o rtsx.o \
	radio.o ipmi.o vscsi.o mpath.o softraid.o softraid_concat.o \
	softraid_crypto.o softraid_raid0.o softraid_raid1.o \
	softraid_raid5.o softraid_raid6.o softraid_raid1c.o spdmem.o \
	dwiic.o dwqe.o ksyms.o kstat.o fuse_device.o fuse_file.o \
	fuse_lookup.o fuse_vfsops.o fuse_vnops.o fusebuf.o pf.o \
	pf_norm.o pf_ruleset.o pf_ioctl.o pf_table.o pf_osfp.o \
	pf_if.o pf_lb.o pf_syncookies.o hfsc.o fq_codel.o \
	if_pflog.o if_pfsync.o if_pflow.o bio.o hotplug.o \
	if_pppoe.o dt_dev.o dt_prov_profile.o dt_prov_syscall.o \
	dt_prov_static.o dt_prov_kprobe.o db_access.o db_break.o \
	db_command.o db_ctf.o db_dwarf.o db_elf.o db_examine.o \
	db_expr.o db_hangman.o db_input.o db_lex.o db_output.o \
	db_rint.o db_run.o db_sym.o db_trap.o db_variables.o \
	db_watch.o db_usrreq.o audio.o cons.o diskmap.o firmload.o \
	dp8390.o rtl80x9.o midi.o mulaw.o vnd.o rnd.o video.o \
	cd9660_bmap.o cd9660_lookup.o cd9660_node.o cd9660_rrip.o \
	cd9660_util.o cd9660_vfsops.o cd9660_vnops.o udf_subr.o \
	udf_vfsops.o udf_vnops.o clock_subr.o exec_conf.o exec_elf.o \
	exec_script.o exec_subr.o init_main.o init_sysent.o \
	kern_acct.o kern_bufq.o kern_clock.o kern_clockintr.o \
	kern_descrip.o kern_event.o kern_exec.o kern_exit.o \
	kern_fork.o kern_kthread.o kern_ktrace.o kern_lock.o \
	kern_malloc.o kern_rwlock.o kern_physio.o kern_proc.o \
	kern_prot.o kern_resource.o kern_pledge.o kern_unveil.o \
	kern_sched.o kern_intrmap.o kern_sensors.o kern_sig.o \
	kern_smr.o kern_subr.o kern_sysctl.o kern_synch.o kern_tc.o \
	kern_time.o kern_timeout.o kern_uuid.o kern_watchdog.o \
	kern_task.o kern_srp.o kern_xxx.o sched_bsd.o \
	subr_autoconf.o subr_blist.o subr_disk.o subr_evcount.o \
	subr_extent.o subr_suspend.o subr_hibernate.o subr_log.o \
	subr_percpu.o subr_poison.o subr_pool.o subr_tree.o \
	dma_alloc.o subr_prf.o subr_prof.o subr_userconf.o \
	subr_xxx.o sys_futex.o sys_generic.o sys_pipe.o \
	sys_process.o sys_socket.o sysv_ipc.o sysv_msg.o sysv_sem.o \
	sysv_shm.o tty.o tty_conf.o tty_pty.o tty_nmea.o tty_msts.o \
	tty_endrun.o tty_subr.o tty_tty.o uipc_domain.o uipc_mbuf.o \
	uipc_mbuf2.o uipc_proto.o uipc_socket.o uipc_socket2.o \
	uipc_syscalls.o uipc_usrreq.o vfs_bio.o vfs_biomem.o \
	vfs_cache.o vfs_default.o vfs_init.o vfs_lockf.o \
	vfs_lookup.o vfs_subr.o vfs_sync.o vfs_syscalls.o vfs_vops.o \
	vfs_vnops.o vfs_getcwd.o spec_vnops.o dead_vnops.o \
	fifo_vnops.o msdosfs_conv.o msdosfs_denode.o msdosfs_fat.o \
	msdosfs_lookup.o msdosfs_vfsops.o msdosfs_vnops.o \
	ntfs_compr.o ntfs_conv.o ntfs_ihash.o ntfs_subr.o \
	ntfs_vfsops.o ntfs_vnops.o hammer2_admin.o hammer2_bulkfree.o \
	hammer2_chain.o hammer2_cluster.o hammer2_flush.o \
	hammer2_freemap.o hammer2_inode.o hammer2_io.o \
	hammer2_ioctl.o hammer2_lz4.o hammer2_ondisk.o \
	hammer2_strategy.o hammer2_subr.o hammer2_vfsops.o \
	hammer2_vnops.o hammer2_xops.o xxhash.o art.o bpf.o \
	bpf_filter.o if.o ifq.o if_ethersubr.o if_etherip.o \
	if_spppsubr.o if_loop.o if_media.o if_ppp.o ppp_tty.o \
	bsd-comp.o ppp-deflate.o if_tun.o if_bridge.o bridgectl.o \
	bridgestp.o if_etherbridge.o if_veb.o if_vlan.o pipex.o \
	radix.o rtable.o route.o rtsock.o slcompress.o if_enc.o \
	if_gre.o if_trunk.o trunklacp.o if_aggr.o if_tpmr.o \
	if_mpe.o if_mpw.o if_mpip.o if_bpe.o if_vether.o if_pair.o \
	if_pppx.o if_vxlan.o if_wg.o wg_noise.o wg_cookie.o \
	toeplitz.o ieee80211.o ieee80211_amrr.o ieee80211_crypto.o \
	ieee80211_crypto_bip.o ieee80211_crypto_ccmp.o \
	ieee80211_crypto_tkip.o ieee80211_crypto_wep.o \
	ieee80211_input.o ieee80211_ioctl.o ieee80211_node.o \
	ieee80211_output.o ieee80211_pae_input.o \
	ieee80211_pae_output.o ieee80211_proto.o ieee80211_ra.o \
	ieee80211_ra_vht.o ieee80211_rssadapt.o ieee80211_regdomain.o \
	if_ether.o igmp.o in.o in_pcb.o in_proto.o inet_nat64.o \
	inet_ntop.o ip_divert.o ip_icmp.o ip_id.o ip_input.o \
	ip_mroute.o ip_output.o raw_ip.o tcp_debug.o tcp_input.o \
	tcp_output.o tcp_subr.o tcp_timer.o tcp_usrreq.o \
	udp_usrreq.o ip_gre.o ip_ipsp.o ip_spd.o ip_ipip.o \
	ipsec_input.o ipsec_output.o ip_esp.o ip_ah.o ip_carp.o \
	ip_ipcomp.o aes.o rijndael.o md5.o rmd160.o sha1.o sha2.o \
	blf.o cast.o ecb_enc.o set_key.o ecb3_enc.o crypto.o \
	criov.o cryptosoft.o xform.o xform_ipcomp.o arc4.o \
	michael.o cmac.o hmac.o gmac.o key_wrap.o idgen.o \
	chachapoly.o poly1305.o siphash.o blake2s.o curve25519.o \
	mpls_input.o mpls_output.o mpls_proto.o mpls_raw.o \
	mpls_shim.o krpc_subr.o nfs_bio.o nfs_boot.o nfs_debug.o \
	nfs_node.o nfs_kq.o nfs_serv.o nfs_socket.o nfs_srvcache.o \
	nfs_subs.o nfs_syscalls.o nfs_vfsops.o nfs_vnops.o \
	ffs_alloc.o ffs_balloc.o ffs_inode.o ffs_subr.o \
	ffs_softdep_stub.o ffs_tables.o ffs_vfsops.o ffs_vnops.o \
	ffs_softdep.o mfs_vfsops.o mfs_vnops.o ufs_bmap.o \
	ufs_dirhash.o ufs_ihash.o ufs_inode.o ufs_lookup.o \
	ufs_quota.o ufs_quota_stub.o ufs_vfsops.o ufs_vnops.o \
	ext2fs_alloc.o ext2fs_balloc.o ext2fs_bmap.o ext2fs_bswap.o \
	ext2fs_extents.o ext2fs_inode.o ext2fs_lookup.o \
	ext2fs_readwrite.o ext2fs_subr.o ext2fs_vfsops.o \
	ext2fs_vnops.o uvm_addr.o uvm_amap.o uvm_anon.o uvm_aobj.o \
	uvm_device.o uvm_fault.o uvm_glue.o uvm_init.o uvm_io.o \
	uvm_km.o uvm_map.o uvm_meter.o uvm_mmap.o uvm_object.o \
	uvm_page.o uvm_pager.o uvm_pdaemon.o uvm_pmemrange.o \
	uvm_swap.o uvm_swap_encrypt.o uvm_unix.o uvm_vnode.o \
	if_gif.o if_sec.o ip_ecn.o in6_pcb.o in6.o ip6_divert.o \
	in6_ifattach.o in6_cksum.o in6_src.o in6_proto.o dest6.o \
	frag6.o icmp6.o ip6_id.o ip6_input.o ip6_forward.o \
	ip6_mroute.o ip6_output.o route6.o mld6.o nd6.o nd6_nbr.o \
	nd6_rtr.o raw_ip6.o udp6_output.o pfkeyv2.o \
	pfkeyv2_parsemessage.o pfkeyv2_convert.o x86emu.o \
	x86emu_util.o getsn.o random.o explicit_bzero.o \
	timingsafe_bcmp.o icrc32.o strchr.o strrchr.o imax.o imin.o \
	lmax.o lmin.o max.o min.o ulmax.o ulmin.o memchr.o \
	memcmp.o bcmp.o bzero.o bcopy.o memcpy.o memmove.o ffs.o \
	fls.o flsl.o memset.o strcmp.o strlcat.o strlcpy.o \
	strlen.o strncmp.o strncpy.o strnlen.o scanc.o skpc.o \
	htonl.o htons.o strncasecmp.o adler32.o crc32.o infback.o \
	inffast.o inflate.o inftrees.o deflate.o zutil.o zopenbsd.o \
	trees.o compress.o autoconf.o conf.o disksubr.o gdt.o \
	machdep.o hibernate_machdep.o identcpu.o tsc.o via.o \
	locore.o aes_intel.o aesni.o amd64errata.o ucode.o mem.o \
	amd64_mem.o mtrr.o pmap.o process_machdep.o sys_machdep.o \
	trap.o vm_machdep.o fpu.o softintr.o i8259.o cacheinfo.o \
	vector.o copy.o spl.o mds.o intr.o bus_space.o bus_dma.o \
	mptramp.o ipifuncs.o ipi.o mp_setperf.o apic.o consinit.o \
	cninit.o dkcsum.o db_disasm.o db_interface.o db_memrw.o \
	db_trace.o in_cksum.o in4_cksum.o clock.o powernow-k8.o \
	est.o k1x-pstate.o rasops.o rasops8.o rasops15.o rasops24.o \
	rasops32.o wsfont.o mii.o mii_physubr.o ukphy_subr.o \
	nsphy.o nsphyter.o gentbi.o qsphy.o inphy.o iophy.o \
	eephy.o exphy.o rlphy.o lxtphy.o luphy.o mtdphy.o icsphy.o \
	sqphy.o tqphy.o ukphy.o dcphy.o bmtphy.o brgphy.o xmphy.o \
	amphy.o acphy.o nsgphy.o urlphy.o rgephy.o ciphy.o \
	ipgphy.o etphy.o jmphy.o atphy.o scsi_base.o scsi_ioctl.o \
	scsiconf.o cd.o ch.o sd.o st.o uk.o safte.o ses.o \
	mpath_sym.o mpath_rdac.o mpath_emc.o mpath_hds.o atapiscsi.o \
	wd.o ata_wdc.o ata.o atascsi.o mainbus.o codepatch.o \
	bios.o mpbios.o mpbios_intr_fixup.o cpu.o lapic.o ioapic.o \
	efifb.o pvbus.o pvclock.o vmt.o xen.o xenstore.o if_xnf.o \
	xbf.o hyperv.o hypervic.o if_hvn.o hvs.o virtio.o if_vio.o \
	vioblk.o viomb.o viornd.o vioscsi.o vmmci.o pci.o \
	pci_map.o pci_quirks.o pci_subr.o vga_pci.o vga_pci_common.o \
	cy82c693.o ahc_pci.o ahd_pci.o adw_pci.o adwlib.o \
	adwmcode.o twe_pci.o arc.o jmb.o ahci_pci.o nvme_pci.o \
	ami_pci.o mfi_pci.o mfii.o ips.o eap.o auacer.o auich.o \
	azalia.o azalia_codec.o envy.o emuxki.o auixp.o cs4280.o \
	yds.o auvia.o gdt_pci.o ciss_pci.o qlw_pci.o qla_pci.o \
	qle.o mpi_pci.o mpii.o sili_pci.o if_aq_pci.o if_de.o \
	if_ep_pci.o if_pcn.o siop_pci_common.o siop_pci.o pciide.o \
	ppb.o cy_pci.o if_rl_pci.o if_re_pci.o if_vr.o if_txp.o \
	bktr_audio.o bktr_card.o bktr_core.o bktr_os.o bktr_tuner.o \
	if_xl_pci.o if_fxp_pci.o if_em.o if_em_hw.o if_em_soc.o \
	if_ixgb.o ixgb_ee.o ixgb_hw.o if_ix.o ixgbe.o ixgbe_82598.o \
	ixgbe_82599.o ixgbe_x540.o ixgbe_x550.o ixgbe_phy.o if_ixl.o \
	if_dwqe_pci.o if_xge.o if_tht.o if_myx.o if_oce.o \
	if_dc_pci.o if_epic_pci.o if_ti_pci.o if_ne_pci.o \
	if_gem_pci.o if_cas.o if_sf_pci.o if_sis.o if_se.o mbg.o \
	uhci_pci.o ohci_pci.o ehci_pci.o xhci_pci.o pccbb.o if_sk.o \
	if_msk.o puc.o pucdata.o com_puc.o lpt_puc.o if_wi_pci.o \
	if_an_pci.o if_iwi.o if_wpi.o if_iwn.o if_iwm.o if_iwx.o \
	cmpci.o iha_pci.o pcscp.o if_bge.o if_bnx.o if_vge.o \
	if_stge.o if_nfe.o if_et.o if_jme.o if_age.o if_alc.o \
	if_ale.o amdpm.o if_bce.o if_ath_pci.o if_athn_pci.o \
	if_atw_pci.o if_rtw_pci.o if_rtwn.o if_ral_pci.o \
	if_acx_pci.o if_pgt_pci.o if_malo_pci.o if_bwi_pci.o \
	piixpm.o if_vic.o if_vmx.o vmwpvs.o if_lii.o ichiic.o \
	viapm.o amdiic.o nviic.o sdhc_pci.o kate.o km.o ksmn.o \
	iosf_pci.o itherm.o pchtemp.o rtsx_pci.o xspd.o \
	virtio_pci.o dwiic_pci.o if_bwfm_pci.o ccp_pci.o if_bnxt.o \
	if_mcx.o if_iavf.o if_rge.o if_igc.o igc_api.o igc_base.o \
	igc_i225.o igc_mac.o igc_nvm.o igc_phy.o if_ngbe.o \
	com_pci.o agp.o agp_i810.o dma-resv.o drm_agpsupport.o \
	drm_aperture.o drm_atomic.o drm_atomic_helper.o \
	drm_atomic_state_helper.o drm_atomic_uapi.o drm_auth.o \
	drm_blend.o drm_bridge.o drm_buddy.o drm_cache.o \
	drm_client.o drm_client_modeset.o drm_color_mgmt.o \
	drm_connector.o drm_crtc.o drm_crtc_helper.o \
	drm_damage_helper.o drm_displayid.o drm_dumb_buffers.o \
	drm_edid.o drm_encoder.o drm_encoder_slave.o drm_fb_helper.o \
	drm_file.o drm_flip_work.o drm_format_helper.o drm_fourcc.o \
	drm_framebuffer.o drm_gem.o drm_gem_atomic_helper.o \
	drm_gem_framebuffer_helper.o drm_hashtab.o drm_ioctl.o \
	drm_kms_helper_common.o drm_linux.o drm_managed.o \
	drm_memory.o drm_mipi_dsi.o drm_mm.o drm_mode_config.o \
	drm_mode_object.o drm_modes.o drm_modeset_helper.o \
	drm_modeset_lock.o drm_mtrr.o drm_panel.o \
	drm_panel_orientation_quirks.o drm_pci.o drm_plane.o \
	drm_plane_helper.o drm_prime.o drm_print.o drm_probe_helper.o \
	drm_property.o drm_rect.o drm_self_refresh_helper.o \
	drm_syncobj.o drm_trace_points.o drm_vblank.o \
	drm_vblank_work.o drm_vma_manager.o hdmi.o linux_list_sort.o \
	linux_radix.o linux_sort.o drm_dp_dual_mode_helper.o \
	drm_dp_helper.o drm_dp_mst_topology.o drm_dsc_helper.o \
	drm_hdcp_helper.o drm_hdmi_helper.o drm_scdc_helper.o \
	drm_gem_ttm_helper.o ttm_agp_backend.o ttm_bo.o ttm_bo_util.o \
	ttm_bo_vm.o ttm_device.o ttm_execbuf_util.o ttm_module.o \
	ttm_pool.o ttm_range_manager.o ttm_resource.o \
	ttm_sys_manager.o ttm_tt.o sched_entity.o sched_fence.o \
	sched_main.o dvo_ch7017.o dvo_ch7xxx.o dvo_ivch.o \
	dvo_ns2501.o dvo_sil164.o dvo_tfp410.o g4x_dp.o g4x_hdmi.o \
	hsw_ips.o i9xx_plane.o icl_dsi.o intel_atomic.o \
	intel_atomic_plane.o intel_audio.o intel_backlight.o \
	intel_bios.o intel_bw.o intel_cdclk.o intel_color.o \
	intel_combo_phy.o intel_connector.o intel_crt.o intel_crtc.o \
	intel_crtc_state_dump.o intel_cursor.o intel_ddi.o \
	intel_ddi_buf_trans.o intel_display.o intel_display_power.o \
	intel_display_power_map.o intel_display_power_well.o \
	intel_dkl_phy.o intel_dmc.o intel_dp.o intel_dp_aux.o \
	intel_dp_aux_backlight.o intel_dp_hdcp.o \
	intel_dp_link_training.o intel_dp_mst.o intel_dpio_phy.o \
	intel_dpll.o intel_dpll_mgr.o intel_dpt.o intel_drrs.o \
	intel_dsb.o intel_dsi.o intel_dsi_dcs_backlight.o \
	intel_dsi_vbt.o intel_dvo.o intel_fb.o intel_fb_pin.o \
	intel_fbc.o intel_fbdev.o intel_fdi.o intel_fifo_underrun.o \
	intel_frontbuffer.o intel_global_state.o intel_gmbus.o \
	intel_hdcp.o intel_hdmi.o intel_hotplug.o intel_lpe_audio.o \
	intel_lspcon.o intel_lvds.o intel_modeset_setup.o \
	intel_modeset_verify.o intel_opregion.o intel_overlay.o \
	intel_panel.o intel_pch_display.o intel_pch_refclk.o \
	intel_plane_initial.o intel_pps.o intel_psr.o \
	intel_qp_tables.o intel_quirks.o intel_sdvo.o \
	intel_snps_phy.o intel_sprite.o intel_tc.o intel_tv.o \
	intel_vdsc.o intel_vga.o intel_vrr.o skl_scaler.o \
	skl_universal_plane.o skl_watermark.o vlv_dsi.o vlv_dsi_pll.o \
	i915_gem_busy.o i915_gem_clflush.o i915_gem_context.o \
	i915_gem_create.o i915_gem_dmabuf.o i915_gem_domain.o \
	i915_gem_execbuffer.o i915_gem_internal.o i915_gem_lmem.o \
	i915_gem_mman.o i915_gem_object.o i915_gem_pages.o \
	i915_gem_phys.o i915_gem_pm.o i915_gem_region.o \
	i915_gem_shmem.o i915_gem_shrinker.o i915_gem_stolen.o \
	i915_gem_throttle.o i915_gem_tiling.o i915_gem_ttm.o \
	i915_gem_ttm_move.o i915_gem_ttm_pm.o i915_gem_userptr.o \
	i915_gem_wait.o i915_gemfs.o agp_intel_gtt.o gen2_engine_cs.o \
	gen6_engine_cs.o gen6_ppgtt.o gen6_renderstate.o \
	gen7_renderclear.o gen7_renderstate.o gen8_engine_cs.o \
	gen8_ppgtt.o gen8_renderstate.o gen9_renderstate.o \
	intel_breadcrumbs.o intel_context.o intel_context_sseu.o \
	intel_engine_cs.o intel_engine_heartbeat.o intel_engine_pm.o \
	intel_engine_user.o intel_execlists_submission.o intel_ggtt.o \
	intel_ggtt_fencing.o intel_ggtt_gmch.o intel_gsc.o intel_gt.o \
	intel_gt_buffer_pool.o intel_gt_clock_utils.o \
	intel_gt_debugfs.o intel_gt_engines_debugfs.o intel_gt_irq.o \
	intel_gt_mcr.o intel_gt_pm.o intel_gt_pm_debugfs.o \
	intel_gt_pm_irq.o intel_gt_requests.o intel_gt_sysfs.o \
	intel_gt_sysfs_pm.o intel_gtt.o intel_llc.o intel_lrc.o \
	intel_migrate.o intel_mocs.o intel_ppgtt.o intel_rc6.o \
	intel_region_lmem.o intel_renderstate.o intel_reset.o \
	intel_ring.o intel_ring_submission.o intel_rps.o \
	intel_sa_media.o intel_sseu.o intel_sseu_debugfs.o \
	intel_timeline.o intel_workarounds.o shmem_utils.o \
	sysfs_engines.o intel_guc.o intel_guc_ads.o \
	intel_guc_capture.o intel_guc_ct.o intel_guc_debugfs.o \
	intel_guc_fw.o intel_guc_hwconfig.o intel_guc_log.o \
	intel_guc_log_debugfs.o intel_guc_rc.o intel_guc_slpc.o \
	intel_guc_submission.o intel_huc.o intel_huc_debugfs.o \
	intel_huc_fw.o intel_uc.o intel_uc_debugfs.o intel_uc_fw.o \
	i915_active.o i915_cmd_parser.o i915_config.o i915_deps.o \
	i915_driver.o i915_drm_client.o i915_gem.o i915_gem_evict.o \
	i915_gem_gtt.o i915_gem_ww.o i915_getparam.o i915_gpu_error.o \
	i915_ioctl.o i915_irq.o i915_memcpy.o i915_mitigations.o \
	i915_mm.o i915_module.o i915_params.o i915_pci.o i915_perf.o \
	i915_query.o i915_request.o i915_scatterlist.o \
	i915_scheduler.o i915_suspend.o i915_sw_fence.o \
	i915_sw_fence_work.o i915_switcheroo.o i915_syncmap.o \
	i915_sysfs.o i915_ttm_buddy_manager.o i915_user_extensions.o \
	i915_utils.o i915_vgpu.o i915_vma.o i915_vma_resource.o \
	intel_device_info.o intel_dram.o intel_memory_region.o \
	intel_pch.o intel_pcode.o intel_pm.o intel_region_ttm.o \
	intel_runtime_pm.o intel_sbi.o intel_step.o intel_stolen.o \
	intel_uncore.o intel_wakeref.o intel_wopcm.o vlv_sideband.o \
	vlv_suspend.o atom.o atombios_crtc.o atombios_dp.o \
	atombios_encoders.o atombios_i2c.o btc_dpm.o ci_dpm.o \
	ci_smc.o cik.o cik_sdma.o cypress_dpm.o dce3_1_afmt.o \
	dce6_afmt.o evergreen.o evergreen_cs.o evergreen_dma.o \
	evergreen_hdmi.o kv_dpm.o kv_smc.o ni.o ni_dma.o ni_dpm.o \
	r100.o r200.o r300.o r420.o r520.o r600.o r600_cs.o \
	r600_dma.o r600_dpm.o r600_hdmi.o radeon_acpi.o radeon_agp.o \
	radeon_asic.o radeon_atombios.o radeon_audio.o \
	radeon_benchmark.o radeon_bios.o radeon_clocks.o \
	radeon_combios.o radeon_connectors.o radeon_cs.o \
	radeon_cursor.o radeon_device.o radeon_display.o \
	radeon_dp_auxch.o radeon_drv.o radeon_encoders.o radeon_fb.o \
	radeon_fence.o radeon_gart.o radeon_gem.o radeon_i2c.o \
	radeon_ib.o radeon_irq_kms.o radeon_kms.o \
	radeon_legacy_crtc.o radeon_legacy_encoders.o \
	radeon_legacy_tv.o radeon_object.o radeon_pm.o radeon_prime.o \
	radeon_ring.o radeon_sa.o radeon_semaphore.o radeon_sync.o \
	radeon_test.o radeon_ttm.o radeon_ucode.o radeon_uvd.o \
	radeon_vce.o radeon_vm.o rs400.o rs600.o rs690.o \
	rs780_dpm.o rv515.o rv6xx_dpm.o rv730_dpm.o rv740_dpm.o \
	rv770.o rv770_dma.o rv770_dpm.o rv770_smc.o si.o si_dma.o \
	si_dpm.o si_smc.o sumo_dpm.o sumo_smc.o trinity_dpm.o \
	trinity_smc.o uvd_v1_0.o uvd_v2_2.o uvd_v3_1.o uvd_v4_2.o \
	vce_v1_0.o vce_v2_0.o aldebaran.o aldebaran_reg_init.o \
	amdgpu_acpi.o amdgpu_afmt.o amdgpu_amdkfd.o amdgpu_atom.o \
	amdgpu_atombios.o amdgpu_atombios_crtc.o amdgpu_atombios_dp.o \
	amdgpu_atombios_encoders.o amdgpu_atombios_i2c.o \
	amdgpu_atomfirmware.o amdgpu_benchmark.o amdgpu_bios.o \
	amdgpu_bo_list.o amdgpu_cgs.o amdgpu_connectors.o amdgpu_cs.o \
	amdgpu_csa.o amdgpu_ctx.o amdgpu_debugfs.o amdgpu_device.o \
	amdgpu_discovery.o amdgpu_display.o amdgpu_dma_buf.o \
	amdgpu_drv.o amdgpu_eeprom.o amdgpu_encoders.o \
	amdgpu_fdinfo.o amdgpu_fence.o amdgpu_fru_eeprom.o \
	amdgpu_fw_attestation.o amdgpu_gart.o amdgpu_gem.o \
	amdgpu_gfx.o amdgpu_gmc.o amdgpu_gtt_mgr.o amdgpu_i2c.o \
	amdgpu_ib.o amdgpu_ids.o amdgpu_ih.o amdgpu_irq.o \
	amdgpu_job.o amdgpu_jpeg.o amdgpu_kms.o amdgpu_lsdma.o \
	amdgpu_mca.o amdgpu_mes.o amdgpu_nbio.o amdgpu_object.o \
	amdgpu_pll.o amdgpu_preempt_mgr.o amdgpu_psp.o \
	amdgpu_psp_ta.o amdgpu_rap.o amdgpu_ras.o amdgpu_ras_eeprom.o \
	amdgpu_reset.o amdgpu_ring.o amdgpu_rlc.o amdgpu_sa.o \
	amdgpu_sched.o amdgpu_sdma.o amdgpu_securedisplay.o \
	amdgpu_sync.o amdgpu_trace_points.o amdgpu_ttm.o \
	amdgpu_ucode.o amdgpu_umc.o amdgpu_uvd.o amdgpu_vce.o \
	amdgpu_vcn.o amdgpu_vf_error.o amdgpu_virt.o amdgpu_vkms.o \
	amdgpu_vm.o amdgpu_vm_cpu.o amdgpu_vm_pt.o amdgpu_vm_sdma.o \
	amdgpu_vram_mgr.o amdgpu_xgmi.o arct_reg_init.o athub_v1_0.o \
	athub_v2_0.o athub_v2_1.o athub_v3_0.o cz_ih.o dce_v10_0.o \
	dce_v11_0.o df_v1_7.o df_v3_6.o dimgrey_cavefish_reg_init.o \
	emu_soc.o gfx_v10_0.o gfx_v11_0.o gfx_v8_0.o gfx_v9_0.o \
	gfx_v9_4.o gfx_v9_4_2.o gfxhub_v1_0.o gfxhub_v1_1.o \
	gfxhub_v2_0.o gfxhub_v2_1.o gfxhub_v3_0.o gfxhub_v3_0_3.o \
	gmc_v10_0.o gmc_v11_0.o gmc_v7_0.o gmc_v8_0.o gmc_v9_0.o \
	hdp_v4_0.o hdp_v5_0.o hdp_v5_2.o hdp_v6_0.o iceland_ih.o \
	ih_v6_0.o imu_v11_0.o imu_v11_0_3.o jpeg_v1_0.o jpeg_v2_0.o \
	jpeg_v2_5.o jpeg_v3_0.o jpeg_v4_0.o lsdma_v6_0.o mca_v3_0.o \
	mes_v10_1.o mes_v11_0.o mmhub_v1_0.o mmhub_v1_7.o \
	mmhub_v2_0.o mmhub_v2_3.o mmhub_v3_0.o mmhub_v3_0_1.o \
	mmhub_v3_0_2.o mmhub_v9_4.o mxgpu_ai.o mxgpu_nv.o mxgpu_vi.o \
	navi10_ih.o nbio_v2_3.o nbio_v4_3.o nbio_v6_1.o nbio_v7_0.o \
	nbio_v7_2.o nbio_v7_4.o nbio_v7_7.o nv.o psp_v10_0.o \
	psp_v11_0.o psp_v11_0_8.o psp_v12_0.o psp_v13_0.o \
	psp_v13_0_4.o psp_v3_1.o sdma_v2_4.o sdma_v3_0.o sdma_v4_0.o \
	sdma_v4_4.o sdma_v5_0.o sdma_v5_2.o sdma_v6_0.o \
	sienna_cichlid.o smu_v11_0_i2c.o smuio_v11_0.o \
	smuio_v11_0_6.o smuio_v13_0.o smuio_v13_0_6.o smuio_v9_0.o \
	soc15.o soc21.o tonga_ih.o umc_v6_0.o umc_v6_1.o umc_v6_7.o \
	umc_v8_10.o umc_v8_7.o uvd_v5_0.o uvd_v6_0.o uvd_v7_0.o \
	vce_v3_0.o vce_v4_0.o vcn_sw_ring.o vcn_v1_0.o vcn_v2_0.o \
	vcn_v2_5.o vcn_v3_0.o vcn_v4_0.o vega10_ih.o \
	vega10_reg_init.o vega20_ih.o vega20_reg_init.o vi.o \
	amdgpu_dm.o amdgpu_dm_color.o amdgpu_dm_crtc.o \
	amdgpu_dm_helpers.o amdgpu_dm_irq.o amdgpu_dm_mst_types.o \
	amdgpu_dm_plane.o amdgpu_dm_pp_smu.o amdgpu_dm_psr.o \
	amdgpu_dm_services.o dc_fpu.o amdgpu_vector.o conversion.o \
	dc_common.o fixpt31_32.o bios_parser.o bios_parser2.o \
	bios_parser_common.o bios_parser_helper.o \
	bios_parser_interface.o command_table.o command_table2.o \
	command_table_helper.o command_table_helper2.o \
	command_table_helper_dce110.o command_table_helper2_dce112.o \
	command_table_helper_dce112.o command_table_helper_dce80.o \
	clk_mgr.o dce_clk_mgr.o dce110_clk_mgr.o dce112_clk_mgr.o \
	dce120_clk_mgr.o rv1_clk_mgr.o rv1_clk_mgr_vbios_smu.o \
	rv2_clk_mgr.o dcn20_clk_mgr.o dcn201_clk_mgr.o rn_clk_mgr.o \
	rn_clk_mgr_vbios_smu.o dcn30_clk_mgr.o dcn30_clk_mgr_smu_msg.o \
	dcn301_smu.o vg_clk_mgr.o dcn31_clk_mgr.o dcn31_smu.o \
	dcn314_clk_mgr.o dcn314_smu.o dcn315_clk_mgr.o dcn315_smu.o \
	dcn316_clk_mgr.o dcn316_smu.o dcn32_clk_mgr.o \
	dcn32_clk_mgr_smu_msg.o amdgpu_dc.o dc_debug.o \
	dc_hw_sequencer.o dc_link.o dc_link_ddc.o dc_link_dp.o \
	dc_link_dpcd.o dc_link_dpia.o dc_link_enc_cfg.o dc_resource.o \
	dc_sink.o dc_stat.o dc_stream.o dc_surface.o dc_vm_helper.o \
	dc_dmub_srv.o dc_edid_parser.o dc_helper.o dce_abm.o \
	dce_audio.o dce_aux.o dce_clock_source.o dce_dmcu.o \
	dce_hwseq.o dce_i2c.o dce_i2c_hw.o dce_i2c_sw.o dce_ipp.o \
	dce_link_encoder.o dce_mem_input.o dce_opp.o dce_panel_cntl.o \
	dce_scl_filters.o dce_scl_filters_old.o dce_stream_encoder.o \
	dce_transform.o dmub_abm.o dmub_hw_lock_mgr.o dmub_outbox.o \
	dmub_psr.o dce100_hw_sequencer.o dce100_resource.o \
	dce110_compressor.o dce110_hw_sequencer.o dce110_mem_input_v.o \
	dce110_opp_csc_v.o dce110_opp_regamma_v.o dce110_opp_v.o \
	dce110_resource.o dce110_timing_generator.o \
	dce110_timing_generator_v.o dce110_transform_v.o \
	dce112_compressor.o dce112_hw_sequencer.o dce112_resource.o \
	dce120_hw_sequencer.o dce120_resource.o \
	dce120_timing_generator.o dce80_hw_sequencer.o \
	dce80_resource.o dce80_timing_generator.o dcn10_cm_common.o \
	dcn10_dpp.o dcn10_dpp_cm.o dcn10_dpp_dscl.o dcn10_dwb.o \
	dcn10_hubbub.o dcn10_hubp.o dcn10_hw_sequencer.o \
	dcn10_hw_sequencer_debug.o dcn10_init.o dcn10_ipp.o \
	dcn10_link_encoder.o dcn10_mpc.o dcn10_opp.o dcn10_optc.o \
	dcn10_resource.o dcn10_stream_encoder.o dcn20_dccg.o \
	dcn20_dpp.o dcn20_dpp_cm.o dcn20_dsc.o dcn20_dwb.o \
	dcn20_dwb_scl.o dcn20_hubbub.o dcn20_hubp.o dcn20_hwseq.o \
	dcn20_init.o dcn20_link_encoder.o dcn20_mmhubbub.o \
	dcn20_mpc.o dcn20_opp.o dcn20_optc.o dcn20_resource.o \
	dcn20_stream_encoder.o dcn20_vmid.o dcn201_dccg.o \
	dcn201_dpp.o dcn201_hubbub.o dcn201_hubp.o dcn201_hwseq.o \
	dcn201_init.o dcn201_link_encoder.o dcn201_mpc.o dcn201_opp.o \
	dcn201_optc.o dcn201_resource.o dcn21_dccg.o dcn21_hubbub.o \
	dcn21_hubp.o dcn21_hwseq.o dcn21_init.o dcn21_link_encoder.o \
	dcn21_resource.o dcn30_afmt.o dcn30_cm_common.o dcn30_dccg.o \
	dcn30_dio_link_encoder.o dcn30_dio_stream_encoder.o \
	dcn30_dpp.o dcn30_dpp_cm.o dcn30_dwb.o dcn30_dwb_cm.o \
	dcn30_hubbub.o dcn30_hubp.o dcn30_hwseq.o dcn30_init.o \
	dcn30_mmhubbub.o dcn30_mpc.o dcn30_optc.o dcn30_resource.o \
	dcn30_vpg.o dcn301_dccg.o dcn301_dio_link_encoder.o \
	dcn301_hubbub.o dcn301_hwseq.o dcn301_init.o \
	dcn301_panel_cntl.o dcn301_resource.o dcn302_hwseq.o \
	dcn302_init.o dcn302_resource.o dcn303_hwseq.o dcn303_init.o \
	dcn303_resource.o dcn31_afmt.o dcn31_apg.o dcn31_dccg.o \
	dcn31_dio_link_encoder.o dcn31_hpo_dp_link_encoder.o \
	dcn31_hpo_dp_stream_encoder.o dcn31_hubbub.o dcn31_hubp.o \
	dcn31_hwseq.o dcn31_init.o dcn31_optc.o dcn31_panel_cntl.o \
	dcn31_resource.o dcn31_vpg.o dcn314_dccg.o \
	dcn314_dio_stream_encoder.o dcn314_hwseq.o dcn314_init.o \
	dcn314_optc.o dcn314_resource.o dcn315_resource.o \
	dcn316_resource.o dcn32_dccg.o dcn32_dio_link_encoder.o \
	dcn32_dio_stream_encoder.o dcn32_dpp.o \
	dcn32_hpo_dp_link_encoder.o dcn32_hubbub.o dcn32_hubp.o \
	dcn32_hwseq.o dcn32_init.o dcn32_mmhubbub.o dcn32_mpc.o \
	dcn32_optc.o dcn32_resource.o dcn32_resource_helpers.o \
	dcn321_dio_link_encoder.o dcn321_resource.o bw_fixed.o \
	custom_float.o dce_calcs.o dcn_calc_auto.o dcn_calc_math.o \
	dcn_calcs.o dcn10_fpu.o dcn20_fpu.o display_mode_vba_20.o \
	display_mode_vba_20v2.o display_rq_dlg_calc_20.o \
	display_rq_dlg_calc_20v2.o display_mode_vba_21.o \
	display_rq_dlg_calc_21.o dcn30_fpu.o display_mode_vba_30.o \
	display_rq_dlg_calc_30.o dcn301_fpu.o dcn302_fpu.o \
	dcn303_fpu.o dcn31_fpu.o display_mode_vba_31.o \
	display_rq_dlg_calc_31.o dcn314_fpu.o display_mode_vba_314.o \
	display_rq_dlg_calc_314.o dcn32_fpu.o display_mode_vba_32.o \
	display_mode_vba_util_32.o display_rq_dlg_calc_32.o \
	dcn321_fpu.o display_mode_lib.o display_mode_vba.o \
	display_rq_dlg_helpers.o dml1_display_rq_dlg_calc.o \
	rc_calc_fpu.o dc_dsc.o rc_calc.o rc_calc_dpi.o \
	hw_factory_dce110.o hw_translate_dce110.o hw_factory_dce120.o \
	hw_translate_dce120.o hw_factory_dce80.o hw_translate_dce80.o \
	hw_factory_dcn10.o hw_translate_dcn10.o hw_factory_dcn20.o \
	hw_translate_dcn20.o hw_factory_dcn21.o hw_translate_dcn21.o \
	hw_factory_dcn30.o hw_translate_dcn30.o hw_factory_dcn315.o \
	hw_translate_dcn315.o hw_factory_dcn32.o hw_translate_dcn32.o \
	gpio_base.o gpio_service.o hw_ddc.o hw_factory.o \
	hw_generic.o hw_gpio.o hw_hpd.o hw_translate.o hdcp_msg.o \
	irq_service_dce110.o irq_service_dce120.o irq_service_dce80.o \
	irq_service_dcn10.o irq_service_dcn20.o irq_service_dcn201.o \
	irq_service_dcn21.o irq_service_dcn30.o irq_service_dcn302.o \
	irq_service_dcn303.o irq_service_dcn31.o irq_service_dcn314.o \
	irq_service_dcn315.o irq_service_dcn32.o irq_service.o \
	link_dp_trace.o link_hwss_dio.o link_hwss_dpia.o \
	link_hwss_hpo_dp.o virtual_link_encoder.o virtual_link_hwss.o \
	virtual_stream_encoder.o dmub_dcn20.o dmub_dcn21.o \
	dmub_dcn30.o dmub_dcn301.o dmub_dcn302.o dmub_dcn303.o \
	dmub_dcn31.o dmub_dcn314.o dmub_dcn315.o dmub_dcn316.o \
	dmub_dcn32.o dmub_reg.o dmub_srv.o dmub_srv_stat.o \
	color_gamma.o color_table.o freesync.o info_packet.o \
	power_helpers.o vmid.o amdgpu_dpm.o amdgpu_dpm_internal.o \
	amdgpu_pm.o legacy_dpm.o amd_powerplay.o ci_baco.o \
	common_baco.o fiji_baco.o hardwaremanager.o hwmgr.o \
	polaris_baco.o pp_overdriver.o pp_psm.o ppatomctrl.o \
	ppatomfwctrl.o pppcielanes.o process_pptables_v1_0.o \
	processpptables.o smu10_hwmgr.o smu7_baco.o \
	smu7_clockpowergating.o smu7_hwmgr.o smu7_powertune.o \
	smu7_thermal.o smu8_hwmgr.o smu9_baco.o smu_helper.o \
	tonga_baco.o vega10_baco.o vega10_hwmgr.o vega10_powertune.o \
	vega10_processpptables.o vega10_thermal.o vega12_baco.o \
	vega12_hwmgr.o vega12_processpptables.o vega12_thermal.o \
	vega20_baco.o vega20_hwmgr.o vega20_powertune.o \
	vega20_processpptables.o vega20_thermal.o ci_smumgr.o \
	fiji_smumgr.o iceland_smumgr.o polaris10_smumgr.o \
	smu10_smumgr.o smu7_smumgr.o smu8_smumgr.o smu9_smumgr.o \
	smumgr.o tonga_smumgr.o vega10_smumgr.o vega12_smumgr.o \
	vega20_smumgr.o vegam_smumgr.o amdgpu_smu.o arcturus_ppt.o \
	cyan_skillfish_ppt.o navi10_ppt.o sienna_cichlid_ppt.o \
	smu_v11_0.o vangogh_ppt.o renoir_ppt.o smu_v12_0.o \
	aldebaran_ppt.o smu_v13_0.o smu_v13_0_0_ppt.o \
	smu_v13_0_4_ppt.o smu_v13_0_5_ppt.o smu_v13_0_7_ppt.o \
	yellow_carp_ppt.o smu_cmn.o pci_machdep.o pciide_machdep.o \
	vga_post.o pchb.o amas.o agp_machdep.o cardslot.o cardbus.o \
	cardbus_map.o cardbus_exrom.o rbus.o com_cardbus.o \
	if_xl_cardbus.o if_dc_cardbus.o if_fxp_cardbus.o \
	if_rl_cardbus.o if_re_cardbus.o if_ath_cardbus.o \
	if_athn_cardbus.o if_atw_cardbus.o if_rtw_cardbus.o \
	if_ral_cardbus.o if_acx_cardbus.o if_pgt_cardbus.o \
	ehci_cardbus.o ohci_cardbus.o uhci_cardbus.o \
	if_malo_cardbus.o if_bwi_cardbus.o rbus_machdep.o pcmcia.o \
	pcmcia_cis.o pcmcia_cis_quirks.o if_ep_pcmcia.o \
	if_ne_pcmcia.o aic_pcmcia.o com_pcmcia.o wdc_pcmcia.o \
	if_sm_pcmcia.o if_xe.o if_wi_pcmcia.o if_malo.o \
	if_an_pcmcia.o pcib.o amdpcib.o tcpcib.o aapic.o hme.o \
	if_hme_pci.o isa.o isadma.o fdc.o fd.o com_isa.o \
	pckbc_isa.o vga_isa.o wdc_isa.o mpu401.o mpu_isa.o pcppi.o \
	spkr.o lpt_isa.o wbsio.o sch311x.o lm78_isa.o it.o uguru.o \
	aps.o isa_machdep.o wsdisplay.o wsdisplay_compat_usl.o \
	wsevent.o wskbd.o wskbdutil.o wsmouse.o wstpad.o wsmux.o \
	wsemulconf.o wsemul_subr.o wsemul_vt100.o wsemul_vt100_subr.o \
	wsemul_vt100_chars.o wsemul_vt100_keys.o pckbd.o \
	wskbdmap_mfii.o pms.o wscons_machdep.o skgpio.o pctr.o \
	nvram.o hid.o hidkbd.o hidms.o hidmt.o hidcc.o usb.o \
	usbdi.o usbdi_util.o usb_mem.o usb_subr.o usb_quirks.o \
	uhub.o uaudio.o uvideo.o utvfu.o udl.o umidi.o \
	umidi_quirks.o ucom.o ugen.o uhidev.o uhid.o fido.o ujoy.o \
	ukbdmap.o ukbd.o ums.o umt.o uts.o ubcmtp.o ucycom.o \
	uslhcom.o ulpt.o umass.o umass_quirks.o umass_scsi.o \
	uthum.o ugold.o utrh.o uoak_subr.o uoakrh.o uoaklux.o \
	uoakv.o uonerng.o urng.o udcf.o umbg.o uvisor.o udsbr.o \
	utwitch.o if_aue.o if_axe.o if_axen.o if_smsc.o if_cue.o \
	if_kue.o if_cdce.o if_urndis.o if_mos.o if_mue.o if_udav.o \
	if_upl.o if_ugl.o if_url.o if_ure.o if_uaq.o umodem.o \
	uftdi.o uplcom.o umct.o uvscom.o ubsa.o ukspan.o uslcom.o \
	uark.o moscom.o umcs.o uscom.o ucrcom.o uxrcom.o uipaq.o \
	umsm.o uchcom.o uticom.o if_wi_usb.o if_atu.o if_ral.o \
	if_rum.o if_run.o if_mtw.o if_zyd.o if_upgt.o if_urtw.o \
	if_urtwn.o if_rsu.o if_otus.o if_umb.o if_uath.o \
	if_athn_usb.o uow.o uberry.o upd.o uwacom.o if_bwfm_usb.o \
	umstc.o uhidpp.o ucc.o i2c.o i2c_exec.o i2c_scan.o \
	i2c_bitbang.o lm75.o lm93.o lm87.o maxim6690.o ad741x.o \
	adm1021.o adm1024.o adm1025.o adm1030.o adm1031.o ds1631.o \
	adt7460.o lm78_i2c.o adm1026.o w83793g.o w83795g.o \
	asc7621.o asc7611.o spdmem_i2c.o sdtemp.o lis331dl.o \
	ihidev.o ikbd.o ims.o imt.o iatp.o ietp.o bmc150.o icc.o \
	gpio.o acpi.o acpiutil.o dsdt.o acpidebug.o acpitimer.o \
	acpiac.o acpibat.o acpibtn.o acpicmos.o acpicpu.o \
	acpihpet.o acpiec.o acpitz.o acpimadt.o acpimcfg.o \
	acpiprt.o acpidmar.o acpidock.o abl.o asmc.o acpiasus.o \
	acpithinkpad.o acpitoshiba.o acpisony.o acpivideo.o \
	acpivout.o acpipwrres.o atk0110.o aplgpio.o bytgpio.o \
	chvgpio.o glkgpio.o pchgpio.o tipmic.o ccpmic.o com_acpi.o \
	sdhc_acpi.o dwiic_acpi.o acpicbkbd.o acpials.o tpm.o \
	acpihve.o acpisbs.o acpisurface.o ipmi_acpi.o amdgpio.o \
	acpihid.o iosf_acpi.o acpi_machdep.o acpi_wakecode.o \
	acpi_x86.o acpi_apm.o acpipci.o efi.o efi_machdep.o vmm.o \
	vmm_machdep.o vmm_support.o sdmmc.o sdmmc_cis.o sdmmc_io.o \
	sdmmc_mem.o sdmmc_scsi.o if_bwfm_sdio.o onewire.o \
	onewire_subr.o owid.o owsbm.o owtemp.o owctr.o

CFILES=	$S/dev/ic/smc93cx6.c $S/dev/ic/pcdisplay_subr.c \
	$S/dev/ic/pcdisplay_chars.c $S/dev/pci/drm/drm_drv.c \
	$S/dev/ic/vga.c $S/dev/ic/vga_subr.c $S/dev/videomode/edid.c \
	$S/dev/videomode/vesagtf.c $S/dev/videomode/videomode.c \
	$S/dev/mii/mii_bitbang.c $S/dev/ic/wdc.c $S/dev/ic/aic7xxx.c \
	$S/dev/ic/aic7xxx_openbsd.c $S/dev/ic/aic7xxx_seeprom.c \
	$S/dev/ic/aic79xx.c $S/dev/ic/aic79xx_openbsd.c \
	$S/dev/ic/aic6360.c $S/dev/ic/adw.c $S/dev/ic/gdt_common.c \
	$S/dev/ic/twe.c $S/dev/ic/ciss.c $S/dev/ic/ami.c $S/dev/ic/mfi.c \
	$S/dev/ic/qlw.c $S/dev/ic/qla.c $S/dev/ic/ahci.c $S/dev/ic/nvme.c \
	$S/dev/ic/mpi.c $S/dev/ic/sili.c $S/dev/ic/ncr53c9x.c \
	$S/dev/ic/siop_common.c $S/dev/ic/siop.c $S/dev/ic/elink3.c \
	$S/dev/ic/if_wi.c $S/dev/ic/if_wi_hostap.c $S/dev/ic/an.c \
	$S/dev/ic/xl.c $S/dev/ic/fxp.c $S/dev/ic/rtl81x9.c $S/dev/ic/re.c \
	$S/dev/ic/dc.c $S/dev/ic/smc91cxx.c $S/dev/ic/smc83c170.c \
	$S/dev/ic/ne2000.c $S/dev/ic/dl10019.c $S/dev/ic/ax88190.c \
	$S/dev/ic/gem.c $S/dev/ic/ti.c $S/dev/ic/com.c $S/dev/ic/pckbc.c \
	$S/dev/ic/ac97.c $S/dev/ic/cy.c $S/dev/ic/lpt.c $S/dev/ic/iha.c \
	$S/dev/ic/lm78.c $S/dev/ic/ar5xxx.c $S/dev/ic/ar5210.c \
	$S/dev/ic/ar5211.c $S/dev/ic/ar5212.c $S/dev/ic/ath.c \
	$S/dev/ic/athn.c $S/dev/ic/ar5008.c $S/dev/ic/ar5416.c \
	$S/dev/ic/ar9280.c $S/dev/ic/ar9285.c $S/dev/ic/ar9287.c \
	$S/dev/ic/ar9003.c $S/dev/ic/ar9380.c $S/dev/ic/bwfm.c \
	$S/dev/ic/atw.c $S/dev/ic/rtw.c $S/dev/ic/rtwn.c \
	$S/dev/ic/rt2560.c $S/dev/ic/rt2661.c $S/dev/ic/rt2860.c \
	$S/dev/ic/acx.c $S/dev/ic/acx111.c $S/dev/ic/acx100.c \
	$S/dev/ic/pgt.c $S/dev/ic/aic6915.c $S/dev/ic/malo.c \
	$S/dev/ic/bwi.c $S/dev/ic/iosf.c $S/dev/usb/uhci.c \
	$S/dev/usb/ohci.c $S/dev/usb/ehci.c $S/dev/usb/xhci.c \
	$S/dev/ic/ccp.c $S/dev/sdmmc/sdhc.c $S/dev/ic/rtsx.c \
	$S/dev/radio.c $S/dev/ipmi.c $S/dev/vscsi.c $S/scsi/mpath.c \
	$S/dev/softraid.c $S/dev/softraid_concat.c \
	$S/dev/softraid_crypto.c $S/dev/softraid_raid0.c \
	$S/dev/softraid_raid1.c $S/dev/softraid_raid5.c \
	$S/dev/softraid_raid6.c $S/dev/softraid_raid1c.c $S/dev/spdmem.c \
	$S/dev/ic/dwiic.c $S/dev/ic/dwqe.c $S/dev/ksyms.c $S/dev/kstat.c \
	$S/miscfs/fuse/fuse_device.c $S/miscfs/fuse/fuse_file.c \
	$S/miscfs/fuse/fuse_lookup.c $S/miscfs/fuse/fuse_vfsops.c \
	$S/miscfs/fuse/fuse_vnops.c $S/miscfs/fuse/fusebuf.c $S/net/pf.c \
	$S/net/pf_norm.c $S/net/pf_ruleset.c $S/net/pf_ioctl.c \
	$S/net/pf_table.c $S/net/pf_osfp.c $S/net/pf_if.c $S/net/pf_lb.c \
	$S/net/pf_syncookies.c $S/net/hfsc.c $S/net/fq_codel.c \
	$S/net/if_pflog.c $S/net/if_pfsync.c $S/net/if_pflow.c \
	$S/dev/bio.c $S/dev/hotplug.c $S/net/if_pppoe.c \
	$S/dev/dt/dt_dev.c $S/dev/dt/dt_prov_profile.c \
	$S/dev/dt/dt_prov_syscall.c $S/dev/dt/dt_prov_static.c \
	$S/dev/dt/dt_prov_kprobe.c $S/ddb/db_access.c $S/ddb/db_break.c \
	$S/ddb/db_command.c $S/ddb/db_ctf.c $S/ddb/db_dwarf.c \
	$S/ddb/db_elf.c $S/ddb/db_examine.c $S/ddb/db_expr.c \
	$S/ddb/db_hangman.c $S/ddb/db_input.c $S/ddb/db_lex.c \
	$S/ddb/db_output.c $S/ddb/db_rint.c $S/ddb/db_run.c \
	$S/ddb/db_sym.c $S/ddb/db_trap.c $S/ddb/db_variables.c \
	$S/ddb/db_watch.c $S/ddb/db_usrreq.c $S/dev/audio.c $S/dev/cons.c \
	$S/dev/diskmap.c $S/dev/firmload.c $S/dev/ic/dp8390.c \
	$S/dev/ic/rtl80x9.c $S/dev/midi.c $S/dev/mulaw.c $S/dev/vnd.c \
	$S/dev/rnd.c $S/dev/video.c $S/isofs/cd9660/cd9660_bmap.c \
	$S/isofs/cd9660/cd9660_lookup.c $S/isofs/cd9660/cd9660_node.c \
	$S/isofs/cd9660/cd9660_rrip.c $S/isofs/cd9660/cd9660_util.c \
	$S/isofs/cd9660/cd9660_vfsops.c $S/isofs/cd9660/cd9660_vnops.c \
	$S/isofs/udf/udf_subr.c $S/isofs/udf/udf_vfsops.c \
	$S/isofs/udf/udf_vnops.c $S/kern/clock_subr.c $S/kern/exec_conf.c \
	$S/kern/exec_elf.c $S/kern/exec_script.c $S/kern/exec_subr.c \
	$S/kern/init_main.c $S/kern/init_sysent.c $S/kern/kern_acct.c \
	$S/kern/kern_bufq.c $S/kern/kern_clock.c $S/kern/kern_clockintr.c \
	$S/kern/kern_descrip.c $S/kern/kern_event.c $S/kern/kern_exec.c \
	$S/kern/kern_exit.c $S/kern/kern_fork.c $S/kern/kern_kthread.c \
	$S/kern/kern_ktrace.c $S/kern/kern_lock.c $S/kern/kern_malloc.c \
	$S/kern/kern_rwlock.c $S/kern/kern_physio.c $S/kern/kern_proc.c \
	$S/kern/kern_prot.c $S/kern/kern_resource.c $S/kern/kern_pledge.c \
	$S/kern/kern_unveil.c $S/kern/kern_sched.c $S/kern/kern_intrmap.c \
	$S/kern/kern_sensors.c $S/kern/kern_sig.c $S/kern/kern_smr.c \
	$S/kern/kern_subr.c $S/kern/kern_sysctl.c $S/kern/kern_synch.c \
	$S/kern/kern_tc.c $S/kern/kern_time.c $S/kern/kern_timeout.c \
	$S/kern/kern_uuid.c $S/kern/kern_watchdog.c $S/kern/kern_task.c \
	$S/kern/kern_srp.c $S/kern/kern_xxx.c $S/kern/sched_bsd.c \
	$S/kern/subr_autoconf.c $S/kern/subr_blist.c $S/kern/subr_disk.c \
	$S/kern/subr_evcount.c $S/kern/subr_extent.c \
	$S/kern/subr_suspend.c $S/kern/subr_hibernate.c \
	$S/kern/subr_log.c $S/kern/subr_percpu.c $S/kern/subr_poison.c \
	$S/kern/subr_pool.c $S/kern/subr_tree.c $S/kern/dma_alloc.c \
	$S/kern/subr_prf.c $S/kern/subr_prof.c $S/kern/subr_userconf.c \
	$S/kern/subr_xxx.c $S/kern/sys_futex.c $S/kern/sys_generic.c \
	$S/kern/sys_pipe.c $S/kern/sys_process.c $S/kern/sys_socket.c \
	$S/kern/sysv_ipc.c $S/kern/sysv_msg.c $S/kern/sysv_sem.c \
	$S/kern/sysv_shm.c $S/kern/tty.c $S/kern/tty_conf.c \
	$S/kern/tty_pty.c $S/kern/tty_nmea.c $S/kern/tty_msts.c \
	$S/kern/tty_endrun.c $S/kern/tty_subr.c $S/kern/tty_tty.c \
	$S/kern/uipc_domain.c $S/kern/uipc_mbuf.c $S/kern/uipc_mbuf2.c \
	$S/kern/uipc_proto.c $S/kern/uipc_socket.c $S/kern/uipc_socket2.c \
	$S/kern/uipc_syscalls.c $S/kern/uipc_usrreq.c $S/kern/vfs_bio.c \
	$S/kern/vfs_biomem.c $S/kern/vfs_cache.c $S/kern/vfs_default.c \
	$S/kern/vfs_init.c $S/kern/vfs_lockf.c $S/kern/vfs_lookup.c \
	$S/kern/vfs_subr.c $S/kern/vfs_sync.c $S/kern/vfs_syscalls.c \
	$S/kern/vfs_vops.c $S/kern/vfs_vnops.c $S/kern/vfs_getcwd.c \
	$S/kern/spec_vnops.c $S/miscfs/deadfs/dead_vnops.c \
	$S/miscfs/fifofs/fifo_vnops.c $S/msdosfs/msdosfs_conv.c \
	$S/msdosfs/msdosfs_denode.c $S/msdosfs/msdosfs_fat.c \
	$S/msdosfs/msdosfs_lookup.c $S/msdosfs/msdosfs_vfsops.c \
	$S/msdosfs/msdosfs_vnops.c $S/ntfs/ntfs_compr.c \
	$S/ntfs/ntfs_conv.c $S/ntfs/ntfs_ihash.c $S/ntfs/ntfs_subr.c \
	$S/ntfs/ntfs_vfsops.c $S/ntfs/ntfs_vnops.c \
	$S/hammer2/hammer2_admin.c $S/hammer2/hammer2_bulkfree.c \
	$S/hammer2/hammer2_chain.c $S/hammer2/hammer2_cluster.c \
	$S/hammer2/hammer2_flush.c $S/hammer2/hammer2_freemap.c \
	$S/hammer2/hammer2_inode.c $S/hammer2/hammer2_io.c \
	$S/hammer2/hammer2_ioctl.c $S/hammer2/hammer2_lz4.c \
	$S/hammer2/hammer2_ondisk.c $S/hammer2/hammer2_strategy.c \
	$S/hammer2/hammer2_subr.c $S/hammer2/hammer2_vfsops.c \
	$S/hammer2/hammer2_vnops.c $S/hammer2/hammer2_xops.c \
	$S/hammer2/xxhash/xxhash.c $S/net/art.c $S/net/bpf.c \
	$S/net/bpf_filter.c $S/net/if.c $S/net/ifq.c \
	$S/net/if_ethersubr.c $S/net/if_etherip.c $S/net/if_spppsubr.c \
	$S/net/if_loop.c $S/net/if_media.c $S/net/if_ppp.c \
	$S/net/ppp_tty.c $S/net/bsd-comp.c $S/net/ppp-deflate.c \
	$S/net/if_tun.c $S/net/if_bridge.c $S/net/bridgectl.c \
	$S/net/bridgestp.c $S/net/if_etherbridge.c $S/net/if_veb.c \
	$S/net/if_vlan.c $S/net/pipex.c $S/net/radix.c $S/net/rtable.c \
	$S/net/route.c $S/net/rtsock.c $S/net/slcompress.c \
	$S/net/if_enc.c $S/net/if_gre.c $S/net/if_trunk.c \
	$S/net/trunklacp.c $S/net/if_aggr.c $S/net/if_tpmr.c \
	$S/net/if_mpe.c $S/net/if_mpw.c $S/net/if_mpip.c $S/net/if_bpe.c \
	$S/net/if_vether.c $S/net/if_pair.c $S/net/if_pppx.c \
	$S/net/if_vxlan.c $S/net/if_wg.c $S/net/wg_noise.c \
	$S/net/wg_cookie.c $S/net/toeplitz.c $S/net80211/ieee80211.c \
	$S/net80211/ieee80211_amrr.c $S/net80211/ieee80211_crypto.c \
	$S/net80211/ieee80211_crypto_bip.c \
	$S/net80211/ieee80211_crypto_ccmp.c \
	$S/net80211/ieee80211_crypto_tkip.c \
	$S/net80211/ieee80211_crypto_wep.c $S/net80211/ieee80211_input.c \
	$S/net80211/ieee80211_ioctl.c $S/net80211/ieee80211_node.c \
	$S/net80211/ieee80211_output.c $S/net80211/ieee80211_pae_input.c \
	$S/net80211/ieee80211_pae_output.c $S/net80211/ieee80211_proto.c \
	$S/net80211/ieee80211_ra.c $S/net80211/ieee80211_ra_vht.c \
	$S/net80211/ieee80211_rssadapt.c \
	$S/net80211/ieee80211_regdomain.c $S/netinet/if_ether.c \
	$S/netinet/igmp.c $S/netinet/in.c $S/netinet/in_pcb.c \
	$S/netinet/in_proto.c $S/netinet/inet_nat64.c \
	$S/netinet/inet_ntop.c $S/netinet/ip_divert.c \
	$S/netinet/ip_icmp.c $S/netinet/ip_id.c $S/netinet/ip_input.c \
	$S/netinet/ip_mroute.c $S/netinet/ip_output.c $S/netinet/raw_ip.c \
	$S/netinet/tcp_debug.c $S/netinet/tcp_input.c \
	$S/netinet/tcp_output.c $S/netinet/tcp_subr.c \
	$S/netinet/tcp_timer.c $S/netinet/tcp_usrreq.c \
	$S/netinet/udp_usrreq.c $S/netinet/ip_gre.c $S/netinet/ip_ipsp.c \
	$S/netinet/ip_spd.c $S/netinet/ip_ipip.c $S/netinet/ipsec_input.c \
	$S/netinet/ipsec_output.c $S/netinet/ip_esp.c $S/netinet/ip_ah.c \
	$S/netinet/ip_carp.c $S/netinet/ip_ipcomp.c $S/crypto/aes.c \
	$S/crypto/rijndael.c $S/crypto/md5.c $S/crypto/rmd160.c \
	$S/crypto/sha1.c $S/crypto/sha2.c $S/crypto/blf.c \
	$S/crypto/cast.c $S/crypto/ecb_enc.c $S/crypto/set_key.c \
	$S/crypto/ecb3_enc.c $S/crypto/crypto.c $S/crypto/criov.c \
	$S/crypto/cryptosoft.c $S/crypto/xform.c $S/crypto/xform_ipcomp.c \
	$S/crypto/arc4.c $S/crypto/michael.c $S/crypto/cmac.c \
	$S/crypto/hmac.c $S/crypto/gmac.c $S/crypto/key_wrap.c \
	$S/crypto/idgen.c $S/crypto/chachapoly.c $S/crypto/poly1305.c \
	$S/crypto/siphash.c $S/crypto/blake2s.c $S/crypto/curve25519.c \
	$S/netmpls/mpls_input.c $S/netmpls/mpls_output.c \
	$S/netmpls/mpls_proto.c $S/netmpls/mpls_raw.c \
	$S/netmpls/mpls_shim.c $S/nfs/krpc_subr.c $S/nfs/nfs_bio.c \
	$S/nfs/nfs_boot.c $S/nfs/nfs_debug.c $S/nfs/nfs_node.c \
	$S/nfs/nfs_kq.c $S/nfs/nfs_serv.c $S/nfs/nfs_socket.c \
	$S/nfs/nfs_srvcache.c $S/nfs/nfs_subs.c $S/nfs/nfs_syscalls.c \
	$S/nfs/nfs_vfsops.c $S/nfs/nfs_vnops.c $S/ufs/ffs/ffs_alloc.c \
	$S/ufs/ffs/ffs_balloc.c $S/ufs/ffs/ffs_inode.c \
	$S/ufs/ffs/ffs_subr.c $S/ufs/ffs/ffs_softdep_stub.c \
	$S/ufs/ffs/ffs_tables.c $S/ufs/ffs/ffs_vfsops.c \
	$S/ufs/ffs/ffs_vnops.c $S/ufs/ffs/ffs_softdep.c \
	$S/ufs/mfs/mfs_vfsops.c $S/ufs/mfs/mfs_vnops.c \
	$S/ufs/ufs/ufs_bmap.c $S/ufs/ufs/ufs_dirhash.c \
	$S/ufs/ufs/ufs_ihash.c $S/ufs/ufs/ufs_inode.c \
	$S/ufs/ufs/ufs_lookup.c $S/ufs/ufs/ufs_quota.c \
	$S/ufs/ufs/ufs_quota_stub.c $S/ufs/ufs/ufs_vfsops.c \
	$S/ufs/ufs/ufs_vnops.c $S/ufs/ext2fs/ext2fs_alloc.c \
	$S/ufs/ext2fs/ext2fs_balloc.c $S/ufs/ext2fs/ext2fs_bmap.c \
	$S/ufs/ext2fs/ext2fs_bswap.c $S/ufs/ext2fs/ext2fs_extents.c \
	$S/ufs/ext2fs/ext2fs_inode.c $S/ufs/ext2fs/ext2fs_lookup.c \
	$S/ufs/ext2fs/ext2fs_readwrite.c $S/ufs/ext2fs/ext2fs_subr.c \
	$S/ufs/ext2fs/ext2fs_vfsops.c $S/ufs/ext2fs/ext2fs_vnops.c \
	$S/uvm/uvm_addr.c $S/uvm/uvm_amap.c $S/uvm/uvm_anon.c \
	$S/uvm/uvm_aobj.c $S/uvm/uvm_device.c $S/uvm/uvm_fault.c \
	$S/uvm/uvm_glue.c $S/uvm/uvm_init.c $S/uvm/uvm_io.c \
	$S/uvm/uvm_km.c $S/uvm/uvm_map.c $S/uvm/uvm_meter.c \
	$S/uvm/uvm_mmap.c $S/uvm/uvm_object.c $S/uvm/uvm_page.c \
	$S/uvm/uvm_pager.c $S/uvm/uvm_pdaemon.c $S/uvm/uvm_pmemrange.c \
	$S/uvm/uvm_swap.c $S/uvm/uvm_swap_encrypt.c $S/uvm/uvm_unix.c \
	$S/uvm/uvm_vnode.c $S/net/if_gif.c $S/net/if_sec.c \
	$S/netinet/ip_ecn.c $S/netinet6/in6_pcb.c $S/netinet6/in6.c \
	$S/netinet6/ip6_divert.c $S/netinet6/in6_ifattach.c \
	$S/netinet6/in6_cksum.c $S/netinet6/in6_src.c \
	$S/netinet6/in6_proto.c $S/netinet6/dest6.c $S/netinet6/frag6.c \
	$S/netinet6/icmp6.c $S/netinet6/ip6_id.c $S/netinet6/ip6_input.c \
	$S/netinet6/ip6_forward.c $S/netinet6/ip6_mroute.c \
	$S/netinet6/ip6_output.c $S/netinet6/route6.c $S/netinet6/mld6.c \
	$S/netinet6/nd6.c $S/netinet6/nd6_nbr.c $S/netinet6/nd6_rtr.c \
	$S/netinet6/raw_ip6.c $S/netinet6/udp6_output.c $S/net/pfkeyv2.c \
	$S/net/pfkeyv2_parsemessage.c $S/net/pfkeyv2_convert.c \
	$S/dev/x86emu/x86emu.c $S/dev/x86emu/x86emu_util.c \
	$S/lib/libkern/getsn.c $S/lib/libkern/random.c \
	$S/lib/libkern/explicit_bzero.c $S/lib/libkern/timingsafe_bcmp.c \
	$S/lib/libkern/icrc32.c $S/lib/libkern/imax.c \
	$S/lib/libkern/imin.c $S/lib/libkern/lmax.c $S/lib/libkern/lmin.c \
	$S/lib/libkern/max.c $S/lib/libkern/min.c $S/lib/libkern/ulmax.c \
	$S/lib/libkern/ulmin.c $S/lib/libkern/fls.c $S/lib/libkern/flsl.c \
	$S/lib/libkern/strlcat.c $S/lib/libkern/strlcpy.c \
	$S/lib/libkern/strncmp.c $S/lib/libkern/strncpy.c \
	$S/lib/libkern/strnlen.c $S/lib/libkern/strncasecmp.c \
	$S/lib/libz/adler32.c $S/lib/libz/crc32.c $S/lib/libz/infback.c \
	$S/lib/libz/inffast.c $S/lib/libz/inflate.c \
	$S/lib/libz/inftrees.c $S/lib/libz/deflate.c $S/lib/libz/zutil.c \
	$S/lib/libz/zopenbsd.c $S/lib/libz/trees.c $S/lib/libz/compress.c \
	$S/arch/amd64/amd64/autoconf.c $S/arch/amd64/amd64/conf.c \
	$S/arch/amd64/amd64/disksubr.c $S/arch/amd64/amd64/gdt.c \
	$S/arch/amd64/amd64/machdep.c \
	$S/arch/amd64/amd64/hibernate_machdep.c \
	$S/arch/amd64/amd64/identcpu.c $S/arch/amd64/amd64/tsc.c \
	$S/arch/amd64/amd64/via.c $S/arch/amd64/amd64/aesni.c \
	$S/arch/amd64/amd64/amd64errata.c $S/arch/amd64/amd64/ucode.c \
	$S/arch/amd64/amd64/mem.c $S/arch/amd64/amd64/amd64_mem.c \
	$S/arch/amd64/amd64/mtrr.c $S/arch/amd64/amd64/pmap.c \
	$S/arch/amd64/amd64/process_machdep.c \
	$S/arch/amd64/amd64/sys_machdep.c $S/arch/amd64/amd64/trap.c \
	$S/arch/amd64/amd64/vm_machdep.c $S/arch/amd64/amd64/fpu.c \
	$S/arch/amd64/amd64/softintr.c $S/arch/amd64/amd64/i8259.c \
	$S/arch/amd64/amd64/cacheinfo.c $S/arch/amd64/amd64/intr.c \
	$S/arch/amd64/amd64/bus_space.c $S/arch/amd64/amd64/bus_dma.c \
	$S/arch/amd64/amd64/ipifuncs.c $S/arch/amd64/amd64/ipi.c \
	$S/arch/amd64/amd64/mp_setperf.c $S/arch/amd64/amd64/apic.c \
	$S/arch/amd64/amd64/consinit.c $S/dev/cninit.c \
	$S/arch/amd64/amd64/dkcsum.c $S/arch/amd64/amd64/db_disasm.c \
	$S/arch/amd64/amd64/db_interface.c $S/arch/amd64/amd64/db_memrw.c \
	$S/arch/amd64/amd64/db_trace.c $S/netinet/in_cksum.c \
	$S/netinet/in4_cksum.c $S/arch/amd64/isa/clock.c \
	$S/arch/amd64/amd64/powernow-k8.c $S/arch/amd64/amd64/est.c \
	$S/arch/amd64/amd64/k1x-pstate.c $S/dev/rasops/rasops.c \
	$S/dev/rasops/rasops8.c $S/dev/rasops/rasops15.c \
	$S/dev/rasops/rasops24.c $S/dev/rasops/rasops32.c \
	$S/dev/wsfont/wsfont.c $S/dev/mii/mii.c $S/dev/mii/mii_physubr.c \
	$S/dev/mii/ukphy_subr.c $S/dev/mii/nsphy.c $S/dev/mii/nsphyter.c \
	$S/dev/mii/gentbi.c $S/dev/mii/qsphy.c $S/dev/mii/inphy.c \
	$S/dev/mii/iophy.c $S/dev/mii/eephy.c $S/dev/mii/exphy.c \
	$S/dev/mii/rlphy.c $S/dev/mii/lxtphy.c $S/dev/mii/luphy.c \
	$S/dev/mii/mtdphy.c $S/dev/mii/icsphy.c $S/dev/mii/sqphy.c \
	$S/dev/mii/tqphy.c $S/dev/mii/ukphy.c $S/dev/mii/dcphy.c \
	$S/dev/mii/bmtphy.c $S/dev/mii/brgphy.c $S/dev/mii/xmphy.c \
	$S/dev/mii/amphy.c $S/dev/mii/acphy.c $S/dev/mii/nsgphy.c \
	$S/dev/mii/urlphy.c $S/dev/mii/rgephy.c $S/dev/mii/ciphy.c \
	$S/dev/mii/ipgphy.c $S/dev/mii/etphy.c $S/dev/mii/jmphy.c \
	$S/dev/mii/atphy.c $S/scsi/scsi_base.c $S/scsi/scsi_ioctl.c \
	$S/scsi/scsiconf.c $S/scsi/cd.c $S/scsi/ch.c $S/scsi/sd.c \
	$S/scsi/st.c $S/scsi/uk.c $S/scsi/safte.c $S/scsi/ses.c \
	$S/scsi/mpath_sym.c $S/scsi/mpath_rdac.c $S/scsi/mpath_emc.c \
	$S/scsi/mpath_hds.c $S/dev/atapiscsi/atapiscsi.c $S/dev/ata/wd.c \
	$S/dev/ata/ata_wdc.c $S/dev/ata/ata.c $S/dev/ata/atascsi.c \
	$S/arch/amd64/amd64/mainbus.c $S/arch/amd64/amd64/codepatch.c \
	$S/arch/amd64/amd64/bios.c $S/arch/amd64/amd64/mpbios.c \
	$S/arch/amd64/amd64/mpbios_intr_fixup.c $S/arch/amd64/amd64/cpu.c \
	$S/arch/amd64/amd64/lapic.c $S/arch/amd64/amd64/ioapic.c \
	$S/arch/amd64/amd64/efifb.c $S/dev/pv/pvbus.c $S/dev/pv/pvclock.c \
	$S/dev/pv/vmt.c $S/dev/pv/xen.c $S/dev/pv/xenstore.c \
	$S/dev/pv/if_xnf.c $S/dev/pv/xbf.c $S/dev/pv/hyperv.c \
	$S/dev/pv/hypervic.c $S/dev/pv/if_hvn.c $S/dev/pv/hvs.c \
	$S/dev/pv/virtio.c $S/dev/pv/if_vio.c $S/dev/pv/vioblk.c \
	$S/dev/pv/viomb.c $S/dev/pv/viornd.c $S/dev/pv/vioscsi.c \
	$S/dev/pv/vmmci.c $S/dev/pci/pci.c $S/dev/pci/pci_map.c \
	$S/dev/pci/pci_quirks.c $S/dev/pci/pci_subr.c \
	$S/dev/pci/vga_pci.c $S/dev/pci/vga_pci_common.c \
	$S/dev/pci/cy82c693.c $S/dev/pci/ahc_pci.c $S/dev/pci/ahd_pci.c \
	$S/dev/pci/adw_pci.c $S/dev/ic/adwlib.c \
	$S/dev/microcode/adw/adwmcode.c $S/dev/pci/twe_pci.c \
	$S/dev/pci/arc.c $S/dev/pci/jmb.c $S/dev/pci/ahci_pci.c \
	$S/dev/pci/nvme_pci.c $S/dev/pci/ami_pci.c $S/dev/pci/mfi_pci.c \
	$S/dev/pci/mfii.c $S/dev/pci/ips.c $S/dev/pci/eap.c \
	$S/dev/pci/auacer.c $S/dev/pci/auich.c $S/dev/pci/azalia.c \
	$S/dev/pci/azalia_codec.c $S/dev/pci/envy.c $S/dev/pci/emuxki.c \
	$S/dev/pci/auixp.c $S/dev/pci/cs4280.c $S/dev/pci/yds.c \
	$S/dev/pci/auvia.c $S/dev/pci/gdt_pci.c $S/dev/pci/ciss_pci.c \
	$S/dev/pci/qlw_pci.c $S/dev/pci/qla_pci.c $S/dev/pci/qle.c \
	$S/dev/pci/mpi_pci.c $S/dev/pci/mpii.c $S/dev/pci/sili_pci.c \
	$S/dev/pci/if_aq_pci.c $S/dev/pci/if_de.c $S/dev/pci/if_ep_pci.c \
	$S/dev/pci/if_pcn.c $S/dev/pci/siop_pci_common.c \
	$S/dev/pci/siop_pci.c $S/dev/pci/pciide.c $S/dev/pci/ppb.c \
	$S/dev/pci/cy_pci.c $S/dev/pci/if_rl_pci.c $S/dev/pci/if_re_pci.c \
	$S/dev/pci/if_vr.c $S/dev/pci/if_txp.c \
	$S/dev/pci/bktr/bktr_audio.c $S/dev/pci/bktr/bktr_card.c \
	$S/dev/pci/bktr/bktr_core.c $S/dev/pci/bktr/bktr_os.c \
	$S/dev/pci/bktr/bktr_tuner.c $S/dev/pci/if_xl_pci.c \
	$S/dev/pci/if_fxp_pci.c $S/dev/pci/if_em.c $S/dev/pci/if_em_hw.c \
	$S/dev/pci/if_em_soc.c $S/dev/pci/if_ixgb.c $S/dev/pci/ixgb_ee.c \
	$S/dev/pci/ixgb_hw.c $S/dev/pci/if_ix.c $S/dev/pci/ixgbe.c \
	$S/dev/pci/ixgbe_82598.c $S/dev/pci/ixgbe_82599.c \
	$S/dev/pci/ixgbe_x540.c $S/dev/pci/ixgbe_x550.c \
	$S/dev/pci/ixgbe_phy.c $S/dev/pci/if_ixl.c \
	$S/dev/pci/if_dwqe_pci.c $S/dev/pci/if_xge.c $S/dev/pci/if_tht.c \
	$S/dev/pci/if_myx.c $S/dev/pci/if_oce.c $S/dev/pci/if_dc_pci.c \
	$S/dev/pci/if_epic_pci.c $S/dev/pci/if_ti_pci.c \
	$S/dev/pci/if_ne_pci.c $S/dev/pci/if_gem_pci.c \
	$S/dev/pci/if_cas.c $S/dev/pci/if_sf_pci.c $S/dev/pci/if_sis.c \
	$S/dev/pci/if_se.c $S/dev/pci/mbg.c $S/dev/pci/uhci_pci.c \
	$S/dev/pci/ohci_pci.c $S/dev/pci/ehci_pci.c $S/dev/pci/xhci_pci.c \
	$S/dev/pci/pccbb.c $S/dev/pci/if_sk.c $S/dev/pci/if_msk.c \
	$S/dev/pci/puc.c $S/dev/pci/pucdata.c $S/dev/puc/com_puc.c \
	$S/dev/puc/lpt_puc.c $S/dev/pci/if_wi_pci.c \
	$S/dev/pci/if_an_pci.c $S/dev/pci/if_iwi.c $S/dev/pci/if_wpi.c \
	$S/dev/pci/if_iwn.c $S/dev/pci/if_iwm.c $S/dev/pci/if_iwx.c \
	$S/dev/pci/cmpci.c $S/dev/pci/iha_pci.c $S/dev/pci/pcscp.c \
	$S/dev/pci/if_bge.c $S/dev/pci/if_bnx.c $S/dev/pci/if_vge.c \
	$S/dev/pci/if_stge.c $S/dev/pci/if_nfe.c $S/dev/pci/if_et.c \
	$S/dev/pci/if_jme.c $S/dev/pci/if_age.c $S/dev/pci/if_alc.c \
	$S/dev/pci/if_ale.c $S/dev/pci/amdpm.c $S/dev/pci/if_bce.c \
	$S/dev/pci/if_ath_pci.c $S/dev/pci/if_athn_pci.c \
	$S/dev/pci/if_atw_pci.c $S/dev/pci/if_rtw_pci.c \
	$S/dev/pci/if_rtwn.c $S/dev/pci/if_ral_pci.c \
	$S/dev/pci/if_acx_pci.c $S/dev/pci/if_pgt_pci.c \
	$S/dev/pci/if_malo_pci.c $S/dev/pci/if_bwi_pci.c \
	$S/dev/pci/piixpm.c $S/dev/pci/if_vic.c $S/dev/pci/if_vmx.c \
	$S/dev/pci/vmwpvs.c $S/dev/pci/if_lii.c $S/dev/pci/ichiic.c \
	$S/dev/pci/viapm.c $S/dev/pci/amdiic.c $S/dev/pci/nviic.c \
	$S/dev/pci/sdhc_pci.c $S/dev/pci/kate.c $S/dev/pci/km.c \
	$S/dev/pci/ksmn.c $S/dev/pci/iosf_pci.c $S/dev/pci/itherm.c \
	$S/dev/pci/pchtemp.c $S/dev/pci/rtsx_pci.c $S/dev/pci/xspd.c \
	$S/dev/pci/virtio_pci.c $S/dev/pci/dwiic_pci.c \
	$S/dev/pci/if_bwfm_pci.c $S/dev/pci/ccp_pci.c \
	$S/dev/pci/if_bnxt.c $S/dev/pci/if_mcx.c $S/dev/pci/if_iavf.c \
	$S/dev/pci/if_rge.c $S/dev/pci/if_igc.c $S/dev/pci/igc_api.c \
	$S/dev/pci/igc_base.c $S/dev/pci/igc_i225.c $S/dev/pci/igc_mac.c \
	$S/dev/pci/igc_nvm.c $S/dev/pci/igc_phy.c $S/dev/pci/if_ngbe.c \
	$S/dev/pci/com_pci.c $S/dev/pci/agp.c $S/dev/pci/agp_i810.c \
	$S/dev/pci/drm/dma-resv.c $S/dev/pci/drm/drm_agpsupport.c \
	$S/dev/pci/drm/drm_aperture.c $S/dev/pci/drm/drm_atomic.c \
	$S/dev/pci/drm/drm_atomic_helper.c \
	$S/dev/pci/drm/drm_atomic_state_helper.c \
	$S/dev/pci/drm/drm_atomic_uapi.c $S/dev/pci/drm/drm_auth.c \
	$S/dev/pci/drm/drm_blend.c $S/dev/pci/drm/drm_bridge.c \
	$S/dev/pci/drm/drm_buddy.c $S/dev/pci/drm/drm_cache.c \
	$S/dev/pci/drm/drm_client.c $S/dev/pci/drm/drm_client_modeset.c \
	$S/dev/pci/drm/drm_color_mgmt.c $S/dev/pci/drm/drm_connector.c \
	$S/dev/pci/drm/drm_crtc.c $S/dev/pci/drm/drm_crtc_helper.c \
	$S/dev/pci/drm/drm_damage_helper.c $S/dev/pci/drm/drm_displayid.c \
	$S/dev/pci/drm/drm_dumb_buffers.c $S/dev/pci/drm/drm_edid.c \
	$S/dev/pci/drm/drm_encoder.c $S/dev/pci/drm/drm_encoder_slave.c \
	$S/dev/pci/drm/drm_fb_helper.c $S/dev/pci/drm/drm_file.c \
	$S/dev/pci/drm/drm_flip_work.c $S/dev/pci/drm/drm_format_helper.c \
	$S/dev/pci/drm/drm_fourcc.c $S/dev/pci/drm/drm_framebuffer.c \
	$S/dev/pci/drm/drm_gem.c $S/dev/pci/drm/drm_gem_atomic_helper.c \
	$S/dev/pci/drm/drm_gem_framebuffer_helper.c \
	$S/dev/pci/drm/drm_hashtab.c $S/dev/pci/drm/drm_ioctl.c \
	$S/dev/pci/drm/drm_kms_helper_common.c $S/dev/pci/drm/drm_linux.c \
	$S/dev/pci/drm/drm_managed.c $S/dev/pci/drm/drm_memory.c \
	$S/dev/pci/drm/drm_mipi_dsi.c $S/dev/pci/drm/drm_mm.c \
	$S/dev/pci/drm/drm_mode_config.c $S/dev/pci/drm/drm_mode_object.c \
	$S/dev/pci/drm/drm_modes.c $S/dev/pci/drm/drm_modeset_helper.c \
	$S/dev/pci/drm/drm_modeset_lock.c $S/dev/pci/drm/drm_mtrr.c \
	$S/dev/pci/drm/drm_panel.c \
	$S/dev/pci/drm/drm_panel_orientation_quirks.c \
	$S/dev/pci/drm/drm_pci.c $S/dev/pci/drm/drm_plane.c \
	$S/dev/pci/drm/drm_plane_helper.c $S/dev/pci/drm/drm_prime.c \
	$S/dev/pci/drm/drm_print.c $S/dev/pci/drm/drm_probe_helper.c \
	$S/dev/pci/drm/drm_property.c $S/dev/pci/drm/drm_rect.c \
	$S/dev/pci/drm/drm_self_refresh_helper.c \
	$S/dev/pci/drm/drm_syncobj.c $S/dev/pci/drm/drm_trace_points.c \
	$S/dev/pci/drm/drm_vblank.c $S/dev/pci/drm/drm_vblank_work.c \
	$S/dev/pci/drm/drm_vma_manager.c $S/dev/pci/drm/hdmi.c \
	$S/dev/pci/drm/linux_list_sort.c $S/dev/pci/drm/linux_radix.c \
	$S/dev/pci/drm/linux_sort.c \
	$S/dev/pci/drm/display/drm_dp_dual_mode_helper.c \
	$S/dev/pci/drm/display/drm_dp_helper.c \
	$S/dev/pci/drm/display/drm_dp_mst_topology.c \
	$S/dev/pci/drm/display/drm_dsc_helper.c \
	$S/dev/pci/drm/display/drm_hdcp_helper.c \
	$S/dev/pci/drm/display/drm_hdmi_helper.c \
	$S/dev/pci/drm/display/drm_scdc_helper.c \
	$S/dev/pci/drm/drm_gem_ttm_helper.c \
	$S/dev/pci/drm/ttm/ttm_agp_backend.c $S/dev/pci/drm/ttm/ttm_bo.c \
	$S/dev/pci/drm/ttm/ttm_bo_util.c $S/dev/pci/drm/ttm/ttm_bo_vm.c \
	$S/dev/pci/drm/ttm/ttm_device.c \
	$S/dev/pci/drm/ttm/ttm_execbuf_util.c \
	$S/dev/pci/drm/ttm/ttm_module.c $S/dev/pci/drm/ttm/ttm_pool.c \
	$S/dev/pci/drm/ttm/ttm_range_manager.c \
	$S/dev/pci/drm/ttm/ttm_resource.c \
	$S/dev/pci/drm/ttm/ttm_sys_manager.c $S/dev/pci/drm/ttm/ttm_tt.c \
	$S/dev/pci/drm/scheduler/sched_entity.c \
	$S/dev/pci/drm/scheduler/sched_fence.c \
	$S/dev/pci/drm/scheduler/sched_main.c \
	$S/dev/pci/drm/i915/display/dvo_ch7017.c \
	$S/dev/pci/drm/i915/display/dvo_ch7xxx.c \
	$S/dev/pci/drm/i915/display/dvo_ivch.c \
	$S/dev/pci/drm/i915/display/dvo_ns2501.c \
	$S/dev/pci/drm/i915/display/dvo_sil164.c \
	$S/dev/pci/drm/i915/display/dvo_tfp410.c \
	$S/dev/pci/drm/i915/display/g4x_dp.c \
	$S/dev/pci/drm/i915/display/g4x_hdmi.c \
	$S/dev/pci/drm/i915/display/hsw_ips.c \
	$S/dev/pci/drm/i915/display/i9xx_plane.c \
	$S/dev/pci/drm/i915/display/icl_dsi.c \
	$S/dev/pci/drm/i915/display/intel_atomic.c \
	$S/dev/pci/drm/i915/display/intel_atomic_plane.c \
	$S/dev/pci/drm/i915/display/intel_audio.c \
	$S/dev/pci/drm/i915/display/intel_backlight.c \
	$S/dev/pci/drm/i915/display/intel_bios.c \
	$S/dev/pci/drm/i915/display/intel_bw.c \
	$S/dev/pci/drm/i915/display/intel_cdclk.c \
	$S/dev/pci/drm/i915/display/intel_color.c \
	$S/dev/pci/drm/i915/display/intel_combo_phy.c \
	$S/dev/pci/drm/i915/display/intel_connector.c \
	$S/dev/pci/drm/i915/display/intel_crt.c \
	$S/dev/pci/drm/i915/display/intel_crtc.c \
	$S/dev/pci/drm/i915/display/intel_crtc_state_dump.c \
	$S/dev/pci/drm/i915/display/intel_cursor.c \
	$S/dev/pci/drm/i915/display/intel_ddi.c \
	$S/dev/pci/drm/i915/display/intel_ddi_buf_trans.c \
	$S/dev/pci/drm/i915/display/intel_display.c \
	$S/dev/pci/drm/i915/display/intel_display_power.c \
	$S/dev/pci/drm/i915/display/intel_display_power_map.c \
	$S/dev/pci/drm/i915/display/intel_display_power_well.c \
	$S/dev/pci/drm/i915/display/intel_dkl_phy.c \
	$S/dev/pci/drm/i915/display/intel_dmc.c \
	$S/dev/pci/drm/i915/display/intel_dp.c \
	$S/dev/pci/drm/i915/display/intel_dp_aux.c \
	$S/dev/pci/drm/i915/display/intel_dp_aux_backlight.c \
	$S/dev/pci/drm/i915/display/intel_dp_hdcp.c \
	$S/dev/pci/drm/i915/display/intel_dp_link_training.c \
	$S/dev/pci/drm/i915/display/intel_dp_mst.c \
	$S/dev/pci/drm/i915/display/intel_dpio_phy.c \
	$S/dev/pci/drm/i915/display/intel_dpll.c \
	$S/dev/pci/drm/i915/display/intel_dpll_mgr.c \
	$S/dev/pci/drm/i915/display/intel_dpt.c \
	$S/dev/pci/drm/i915/display/intel_drrs.c \
	$S/dev/pci/drm/i915/display/intel_dsb.c \
	$S/dev/pci/drm/i915/display/intel_dsi.c \
	$S/dev/pci/drm/i915/display/intel_dsi_dcs_backlight.c \
	$S/dev/pci/drm/i915/display/intel_dsi_vbt.c \
	$S/dev/pci/drm/i915/display/intel_dvo.c \
	$S/dev/pci/drm/i915/display/intel_fb.c \
	$S/dev/pci/drm/i915/display/intel_fb_pin.c \
	$S/dev/pci/drm/i915/display/intel_fbc.c \
	$S/dev/pci/drm/i915/display/intel_fbdev.c \
	$S/dev/pci/drm/i915/display/intel_fdi.c \
	$S/dev/pci/drm/i915/display/intel_fifo_underrun.c \
	$S/dev/pci/drm/i915/display/intel_frontbuffer.c \
	$S/dev/pci/drm/i915/display/intel_global_state.c \
	$S/dev/pci/drm/i915/display/intel_gmbus.c \
	$S/dev/pci/drm/i915/display/intel_hdcp.c \
	$S/dev/pci/drm/i915/display/intel_hdmi.c \
	$S/dev/pci/drm/i915/display/intel_hotplug.c \
	$S/dev/pci/drm/i915/display/intel_lpe_audio.c \
	$S/dev/pci/drm/i915/display/intel_lspcon.c \
	$S/dev/pci/drm/i915/display/intel_lvds.c \
	$S/dev/pci/drm/i915/display/intel_modeset_setup.c \
	$S/dev/pci/drm/i915/display/intel_modeset_verify.c \
	$S/dev/pci/drm/i915/display/intel_opregion.c \
	$S/dev/pci/drm/i915/display/intel_overlay.c \
	$S/dev/pci/drm/i915/display/intel_panel.c \
	$S/dev/pci/drm/i915/display/intel_pch_display.c \
	$S/dev/pci/drm/i915/display/intel_pch_refclk.c \
	$S/dev/pci/drm/i915/display/intel_plane_initial.c \
	$S/dev/pci/drm/i915/display/intel_pps.c \
	$S/dev/pci/drm/i915/display/intel_psr.c \
	$S/dev/pci/drm/i915/display/intel_qp_tables.c \
	$S/dev/pci/drm/i915/display/intel_quirks.c \
	$S/dev/pci/drm/i915/display/intel_sdvo.c \
	$S/dev/pci/drm/i915/display/intel_snps_phy.c \
	$S/dev/pci/drm/i915/display/intel_sprite.c \
	$S/dev/pci/drm/i915/display/intel_tc.c \
	$S/dev/pci/drm/i915/display/intel_tv.c \
	$S/dev/pci/drm/i915/display/intel_vdsc.c \
	$S/dev/pci/drm/i915/display/intel_vga.c \
	$S/dev/pci/drm/i915/display/intel_vrr.c \
	$S/dev/pci/drm/i915/display/skl_scaler.c \
	$S/dev/pci/drm/i915/display/skl_universal_plane.c \
	$S/dev/pci/drm/i915/display/skl_watermark.c \
	$S/dev/pci/drm/i915/display/vlv_dsi.c \
	$S/dev/pci/drm/i915/display/vlv_dsi_pll.c \
	$S/dev/pci/drm/i915/gem/i915_gem_busy.c \
	$S/dev/pci/drm/i915/gem/i915_gem_clflush.c \
	$S/dev/pci/drm/i915/gem/i915_gem_context.c \
	$S/dev/pci/drm/i915/gem/i915_gem_create.c \
	$S/dev/pci/drm/i915/gem/i915_gem_dmabuf.c \
	$S/dev/pci/drm/i915/gem/i915_gem_domain.c \
	$S/dev/pci/drm/i915/gem/i915_gem_execbuffer.c \
	$S/dev/pci/drm/i915/gem/i915_gem_internal.c \
	$S/dev/pci/drm/i915/gem/i915_gem_lmem.c \
	$S/dev/pci/drm/i915/gem/i915_gem_mman.c \
	$S/dev/pci/drm/i915/gem/i915_gem_object.c \
	$S/dev/pci/drm/i915/gem/i915_gem_pages.c \
	$S/dev/pci/drm/i915/gem/i915_gem_phys.c \
	$S/dev/pci/drm/i915/gem/i915_gem_pm.c \
	$S/dev/pci/drm/i915/gem/i915_gem_region.c \
	$S/dev/pci/drm/i915/gem/i915_gem_shmem.c \
	$S/dev/pci/drm/i915/gem/i915_gem_shrinker.c \
	$S/dev/pci/drm/i915/gem/i915_gem_stolen.c \
	$S/dev/pci/drm/i915/gem/i915_gem_throttle.c \
	$S/dev/pci/drm/i915/gem/i915_gem_tiling.c \
	$S/dev/pci/drm/i915/gem/i915_gem_ttm.c \
	$S/dev/pci/drm/i915/gem/i915_gem_ttm_move.c \
	$S/dev/pci/drm/i915/gem/i915_gem_ttm_pm.c \
	$S/dev/pci/drm/i915/gem/i915_gem_userptr.c \
	$S/dev/pci/drm/i915/gem/i915_gem_wait.c \
	$S/dev/pci/drm/i915/gem/i915_gemfs.c \
	$S/dev/pci/drm/i915/gt/agp_intel_gtt.c \
	$S/dev/pci/drm/i915/gt/gen2_engine_cs.c \
	$S/dev/pci/drm/i915/gt/gen6_engine_cs.c \
	$S/dev/pci/drm/i915/gt/gen6_ppgtt.c \
	$S/dev/pci/drm/i915/gt/gen6_renderstate.c \
	$S/dev/pci/drm/i915/gt/gen7_renderclear.c \
	$S/dev/pci/drm/i915/gt/gen7_renderstate.c \
	$S/dev/pci/drm/i915/gt/gen8_engine_cs.c \
	$S/dev/pci/drm/i915/gt/gen8_ppgtt.c \
	$S/dev/pci/drm/i915/gt/gen8_renderstate.c \
	$S/dev/pci/drm/i915/gt/gen9_renderstate.c \
	$S/dev/pci/drm/i915/gt/intel_breadcrumbs.c \
	$S/dev/pci/drm/i915/gt/intel_context.c \
	$S/dev/pci/drm/i915/gt/intel_context_sseu.c \
	$S/dev/pci/drm/i915/gt/intel_engine_cs.c \
	$S/dev/pci/drm/i915/gt/intel_engine_heartbeat.c \
	$S/dev/pci/drm/i915/gt/intel_engine_pm.c \
	$S/dev/pci/drm/i915/gt/intel_engine_user.c \
	$S/dev/pci/drm/i915/gt/intel_execlists_submission.c \
	$S/dev/pci/drm/i915/gt/intel_ggtt.c \
	$S/dev/pci/drm/i915/gt/intel_ggtt_fencing.c \
	$S/dev/pci/drm/i915/gt/intel_ggtt_gmch.c \
	$S/dev/pci/drm/i915/gt/intel_gsc.c \
	$S/dev/pci/drm/i915/gt/intel_gt.c \
	$S/dev/pci/drm/i915/gt/intel_gt_buffer_pool.c \
	$S/dev/pci/drm/i915/gt/intel_gt_clock_utils.c \
	$S/dev/pci/drm/i915/gt/intel_gt_debugfs.c \
	$S/dev/pci/drm/i915/gt/intel_gt_engines_debugfs.c \
	$S/dev/pci/drm/i915/gt/intel_gt_irq.c \
	$S/dev/pci/drm/i915/gt/intel_gt_mcr.c \
	$S/dev/pci/drm/i915/gt/intel_gt_pm.c \
	$S/dev/pci/drm/i915/gt/intel_gt_pm_debugfs.c \
	$S/dev/pci/drm/i915/gt/intel_gt_pm_irq.c \
	$S/dev/pci/drm/i915/gt/intel_gt_requests.c \
	$S/dev/pci/drm/i915/gt/intel_gt_sysfs.c \
	$S/dev/pci/drm/i915/gt/intel_gt_sysfs_pm.c \
	$S/dev/pci/drm/i915/gt/intel_gtt.c \
	$S/dev/pci/drm/i915/gt/intel_llc.c \
	$S/dev/pci/drm/i915/gt/intel_lrc.c \
	$S/dev/pci/drm/i915/gt/intel_migrate.c \
	$S/dev/pci/drm/i915/gt/intel_mocs.c \
	$S/dev/pci/drm/i915/gt/intel_ppgtt.c \
	$S/dev/pci/drm/i915/gt/intel_rc6.c \
	$S/dev/pci/drm/i915/gt/intel_region_lmem.c \
	$S/dev/pci/drm/i915/gt/intel_renderstate.c \
	$S/dev/pci/drm/i915/gt/intel_reset.c \
	$S/dev/pci/drm/i915/gt/intel_ring.c \
	$S/dev/pci/drm/i915/gt/intel_ring_submission.c \
	$S/dev/pci/drm/i915/gt/intel_rps.c \
	$S/dev/pci/drm/i915/gt/intel_sa_media.c \
	$S/dev/pci/drm/i915/gt/intel_sseu.c \
	$S/dev/pci/drm/i915/gt/intel_sseu_debugfs.c \
	$S/dev/pci/drm/i915/gt/intel_timeline.c \
	$S/dev/pci/drm/i915/gt/intel_workarounds.c \
	$S/dev/pci/drm/i915/gt/shmem_utils.c \
	$S/dev/pci/drm/i915/gt/sysfs_engines.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_ads.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_capture.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_ct.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_debugfs.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_fw.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_hwconfig.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_log.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_log_debugfs.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_rc.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_slpc.c \
	$S/dev/pci/drm/i915/gt/uc/intel_guc_submission.c \
	$S/dev/pci/drm/i915/gt/uc/intel_huc.c \
	$S/dev/pci/drm/i915/gt/uc/intel_huc_debugfs.c \
	$S/dev/pci/drm/i915/gt/uc/intel_huc_fw.c \
	$S/dev/pci/drm/i915/gt/uc/intel_uc.c \
	$S/dev/pci/drm/i915/gt/uc/intel_uc_debugfs.c \
	$S/dev/pci/drm/i915/gt/uc/intel_uc_fw.c \
	$S/dev/pci/drm/i915/i915_active.c \
	$S/dev/pci/drm/i915/i915_cmd_parser.c \
	$S/dev/pci/drm/i915/i915_config.c $S/dev/pci/drm/i915/i915_deps.c \
	$S/dev/pci/drm/i915/i915_driver.c \
	$S/dev/pci/drm/i915/i915_drm_client.c \
	$S/dev/pci/drm/i915/i915_gem.c \
	$S/dev/pci/drm/i915/i915_gem_evict.c \
	$S/dev/pci/drm/i915/i915_gem_gtt.c \
	$S/dev/pci/drm/i915/i915_gem_ww.c \
	$S/dev/pci/drm/i915/i915_getparam.c \
	$S/dev/pci/drm/i915/i915_gpu_error.c \
	$S/dev/pci/drm/i915/i915_ioctl.c $S/dev/pci/drm/i915/i915_irq.c \
	$S/dev/pci/drm/i915/i915_memcpy.c \
	$S/dev/pci/drm/i915/i915_mitigations.c \
	$S/dev/pci/drm/i915/i915_mm.c $S/dev/pci/drm/i915/i915_module.c \
	$S/dev/pci/drm/i915/i915_params.c $S/dev/pci/drm/i915/i915_pci.c \
	$S/dev/pci/drm/i915/i915_perf.c $S/dev/pci/drm/i915/i915_query.c \
	$S/dev/pci/drm/i915/i915_request.c \
	$S/dev/pci/drm/i915/i915_scatterlist.c \
	$S/dev/pci/drm/i915/i915_scheduler.c \
	$S/dev/pci/drm/i915/i915_suspend.c \
	$S/dev/pci/drm/i915/i915_sw_fence.c \
	$S/dev/pci/drm/i915/i915_sw_fence_work.c \
	$S/dev/pci/drm/i915/i915_switcheroo.c \
	$S/dev/pci/drm/i915/i915_syncmap.c \
	$S/dev/pci/drm/i915/i915_sysfs.c \
	$S/dev/pci/drm/i915/i915_ttm_buddy_manager.c \
	$S/dev/pci/drm/i915/i915_user_extensions.c \
	$S/dev/pci/drm/i915/i915_utils.c $S/dev/pci/drm/i915/i915_vgpu.c \
	$S/dev/pci/drm/i915/i915_vma.c \
	$S/dev/pci/drm/i915/i915_vma_resource.c \
	$S/dev/pci/drm/i915/intel_device_info.c \
	$S/dev/pci/drm/i915/intel_dram.c \
	$S/dev/pci/drm/i915/intel_memory_region.c \
	$S/dev/pci/drm/i915/intel_pch.c $S/dev/pci/drm/i915/intel_pcode.c \
	$S/dev/pci/drm/i915/intel_pm.c \
	$S/dev/pci/drm/i915/intel_region_ttm.c \
	$S/dev/pci/drm/i915/intel_runtime_pm.c \
	$S/dev/pci/drm/i915/intel_sbi.c $S/dev/pci/drm/i915/intel_step.c \
	$S/dev/pci/drm/i915/intel_stolen.c \
	$S/dev/pci/drm/i915/intel_uncore.c \
	$S/dev/pci/drm/i915/intel_wakeref.c \
	$S/dev/pci/drm/i915/intel_wopcm.c \
	$S/dev/pci/drm/i915/vlv_sideband.c \
	$S/dev/pci/drm/i915/vlv_suspend.c $S/dev/pci/drm/radeon/atom.c \
	$S/dev/pci/drm/radeon/atombios_crtc.c \
	$S/dev/pci/drm/radeon/atombios_dp.c \
	$S/dev/pci/drm/radeon/atombios_encoders.c \
	$S/dev/pci/drm/radeon/atombios_i2c.c \
	$S/dev/pci/drm/radeon/btc_dpm.c $S/dev/pci/drm/radeon/ci_dpm.c \
	$S/dev/pci/drm/radeon/ci_smc.c $S/dev/pci/drm/radeon/cik.c \
	$S/dev/pci/drm/radeon/cik_sdma.c \
	$S/dev/pci/drm/radeon/cypress_dpm.c \
	$S/dev/pci/drm/radeon/dce3_1_afmt.c \
	$S/dev/pci/drm/radeon/dce6_afmt.c \
	$S/dev/pci/drm/radeon/evergreen.c \
	$S/dev/pci/drm/radeon/evergreen_cs.c \
	$S/dev/pci/drm/radeon/evergreen_dma.c \
	$S/dev/pci/drm/radeon/evergreen_hdmi.c \
	$S/dev/pci/drm/radeon/kv_dpm.c $S/dev/pci/drm/radeon/kv_smc.c \
	$S/dev/pci/drm/radeon/ni.c $S/dev/pci/drm/radeon/ni_dma.c \
	$S/dev/pci/drm/radeon/ni_dpm.c $S/dev/pci/drm/radeon/r100.c \
	$S/dev/pci/drm/radeon/r200.c $S/dev/pci/drm/radeon/r300.c \
	$S/dev/pci/drm/radeon/r420.c $S/dev/pci/drm/radeon/r520.c \
	$S/dev/pci/drm/radeon/r600.c $S/dev/pci/drm/radeon/r600_cs.c \
	$S/dev/pci/drm/radeon/r600_dma.c $S/dev/pci/drm/radeon/r600_dpm.c \
	$S/dev/pci/drm/radeon/r600_hdmi.c \
	$S/dev/pci/drm/radeon/radeon_acpi.c \
	$S/dev/pci/drm/radeon/radeon_agp.c \
	$S/dev/pci/drm/radeon/radeon_asic.c \
	$S/dev/pci/drm/radeon/radeon_atombios.c \
	$S/dev/pci/drm/radeon/radeon_audio.c \
	$S/dev/pci/drm/radeon/radeon_benchmark.c \
	$S/dev/pci/drm/radeon/radeon_bios.c \
	$S/dev/pci/drm/radeon/radeon_clocks.c \
	$S/dev/pci/drm/radeon/radeon_combios.c \
	$S/dev/pci/drm/radeon/radeon_connectors.c \
	$S/dev/pci/drm/radeon/radeon_cs.c \
	$S/dev/pci/drm/radeon/radeon_cursor.c \
	$S/dev/pci/drm/radeon/radeon_device.c \
	$S/dev/pci/drm/radeon/radeon_display.c \
	$S/dev/pci/drm/radeon/radeon_dp_auxch.c \
	$S/dev/pci/drm/radeon/radeon_drv.c \
	$S/dev/pci/drm/radeon/radeon_encoders.c \
	$S/dev/pci/drm/radeon/radeon_fb.c \
	$S/dev/pci/drm/radeon/radeon_fence.c \
	$S/dev/pci/drm/radeon/radeon_gart.c \
	$S/dev/pci/drm/radeon/radeon_gem.c \
	$S/dev/pci/drm/radeon/radeon_i2c.c \
	$S/dev/pci/drm/radeon/radeon_ib.c \
	$S/dev/pci/drm/radeon/radeon_irq_kms.c \
	$S/dev/pci/drm/radeon/radeon_kms.c \
	$S/dev/pci/drm/radeon/radeon_legacy_crtc.c \
	$S/dev/pci/drm/radeon/radeon_legacy_encoders.c \
	$S/dev/pci/drm/radeon/radeon_legacy_tv.c \
	$S/dev/pci/drm/radeon/radeon_object.c \
	$S/dev/pci/drm/radeon/radeon_pm.c \
	$S/dev/pci/drm/radeon/radeon_prime.c \
	$S/dev/pci/drm/radeon/radeon_ring.c \
	$S/dev/pci/drm/radeon/radeon_sa.c \
	$S/dev/pci/drm/radeon/radeon_semaphore.c \
	$S/dev/pci/drm/radeon/radeon_sync.c \
	$S/dev/pci/drm/radeon/radeon_test.c \
	$S/dev/pci/drm/radeon/radeon_ttm.c \
	$S/dev/pci/drm/radeon/radeon_ucode.c \
	$S/dev/pci/drm/radeon/radeon_uvd.c \
	$S/dev/pci/drm/radeon/radeon_vce.c \
	$S/dev/pci/drm/radeon/radeon_vm.c $S/dev/pci/drm/radeon/rs400.c \
	$S/dev/pci/drm/radeon/rs600.c $S/dev/pci/drm/radeon/rs690.c \
	$S/dev/pci/drm/radeon/rs780_dpm.c $S/dev/pci/drm/radeon/rv515.c \
	$S/dev/pci/drm/radeon/rv6xx_dpm.c \
	$S/dev/pci/drm/radeon/rv730_dpm.c \
	$S/dev/pci/drm/radeon/rv740_dpm.c $S/dev/pci/drm/radeon/rv770.c \
	$S/dev/pci/drm/radeon/rv770_dma.c \
	$S/dev/pci/drm/radeon/rv770_dpm.c \
	$S/dev/pci/drm/radeon/rv770_smc.c $S/dev/pci/drm/radeon/si.c \
	$S/dev/pci/drm/radeon/si_dma.c $S/dev/pci/drm/radeon/si_dpm.c \
	$S/dev/pci/drm/radeon/si_smc.c $S/dev/pci/drm/radeon/sumo_dpm.c \
	$S/dev/pci/drm/radeon/sumo_smc.c \
	$S/dev/pci/drm/radeon/trinity_dpm.c \
	$S/dev/pci/drm/radeon/trinity_smc.c \
	$S/dev/pci/drm/radeon/uvd_v1_0.c $S/dev/pci/drm/radeon/uvd_v2_2.c \
	$S/dev/pci/drm/radeon/uvd_v3_1.c $S/dev/pci/drm/radeon/uvd_v4_2.c \
	$S/dev/pci/drm/radeon/vce_v1_0.c $S/dev/pci/drm/radeon/vce_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/aldebaran.c \
	$S/dev/pci/drm/amd/amdgpu/aldebaran_reg_init.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_acpi.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_afmt.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_amdkfd.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atom.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atombios.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_crtc.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_dp.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_encoders.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_i2c.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_atomfirmware.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_benchmark.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_bios.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_bo_list.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_cgs.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_connectors.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_cs.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_csa.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ctx.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_debugfs.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_device.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_discovery.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_display.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_dma_buf.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_drv.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_eeprom.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_encoders.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_fdinfo.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_fence.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_fru_eeprom.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_fw_attestation.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_gart.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_gem.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_gfx.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_gmc.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_gtt_mgr.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_i2c.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ib.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ids.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ih.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_irq.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_job.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_jpeg.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_kms.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_lsdma.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_mca.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_mes.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_nbio.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_object.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_pll.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_preempt_mgr.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_psp.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_psp_ta.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_rap.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ras.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ras_eeprom.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_reset.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ring.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_rlc.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_sa.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_sched.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_sdma.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_securedisplay.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_sync.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_trace_points.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ttm.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_ucode.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_umc.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_uvd.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vce.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vcn.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vf_error.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_virt.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vkms.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vm.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vm_cpu.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vm_pt.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vm_sdma.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_vram_mgr.c \
	$S/dev/pci/drm/amd/amdgpu/amdgpu_xgmi.c \
	$S/dev/pci/drm/amd/amdgpu/arct_reg_init.c \
	$S/dev/pci/drm/amd/amdgpu/athub_v1_0.c \
	$S/dev/pci/drm/amd/amdgpu/athub_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/athub_v2_1.c \
	$S/dev/pci/drm/amd/amdgpu/athub_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/cz_ih.c \
	$S/dev/pci/drm/amd/amdgpu/dce_v10_0.c \
	$S/dev/pci/drm/amd/amdgpu/dce_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/df_v1_7.c \
	$S/dev/pci/drm/amd/amdgpu/df_v3_6.c \
	$S/dev/pci/drm/amd/amdgpu/dimgrey_cavefish_reg_init.c \
	$S/dev/pci/drm/amd/amdgpu/emu_soc.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v10_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v8_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v9_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v9_4.c \
	$S/dev/pci/drm/amd/amdgpu/gfx_v9_4_2.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v1_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v1_1.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v2_1.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/gfxhub_v3_0_3.c \
	$S/dev/pci/drm/amd/amdgpu/gmc_v10_0.c \
	$S/dev/pci/drm/amd/amdgpu/gmc_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/gmc_v7_0.c \
	$S/dev/pci/drm/amd/amdgpu/gmc_v8_0.c \
	$S/dev/pci/drm/amd/amdgpu/gmc_v9_0.c \
	$S/dev/pci/drm/amd/amdgpu/hdp_v4_0.c \
	$S/dev/pci/drm/amd/amdgpu/hdp_v5_0.c \
	$S/dev/pci/drm/amd/amdgpu/hdp_v5_2.c \
	$S/dev/pci/drm/amd/amdgpu/hdp_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/iceland_ih.c \
	$S/dev/pci/drm/amd/amdgpu/ih_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/imu_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/imu_v11_0_3.c \
	$S/dev/pci/drm/amd/amdgpu/jpeg_v1_0.c \
	$S/dev/pci/drm/amd/amdgpu/jpeg_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/jpeg_v2_5.c \
	$S/dev/pci/drm/amd/amdgpu/jpeg_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/jpeg_v4_0.c \
	$S/dev/pci/drm/amd/amdgpu/lsdma_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/mca_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/mes_v10_1.c \
	$S/dev/pci/drm/amd/amdgpu/mes_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v1_0.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v1_7.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v2_3.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v3_0_1.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v3_0_2.c \
	$S/dev/pci/drm/amd/amdgpu/mmhub_v9_4.c \
	$S/dev/pci/drm/amd/amdgpu/mxgpu_ai.c \
	$S/dev/pci/drm/amd/amdgpu/mxgpu_nv.c \
	$S/dev/pci/drm/amd/amdgpu/mxgpu_vi.c \
	$S/dev/pci/drm/amd/amdgpu/navi10_ih.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v2_3.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v4_3.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v6_1.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v7_0.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v7_2.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v7_4.c \
	$S/dev/pci/drm/amd/amdgpu/nbio_v7_7.c \
	$S/dev/pci/drm/amd/amdgpu/nv.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v10_0.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v11_0_8.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v12_0.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v13_0.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v13_0_4.c \
	$S/dev/pci/drm/amd/amdgpu/psp_v3_1.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v2_4.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v4_0.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v4_4.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v5_0.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v5_2.c \
	$S/dev/pci/drm/amd/amdgpu/sdma_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/sienna_cichlid.c \
	$S/dev/pci/drm/amd/amdgpu/smu_v11_0_i2c.c \
	$S/dev/pci/drm/amd/amdgpu/smuio_v11_0.c \
	$S/dev/pci/drm/amd/amdgpu/smuio_v11_0_6.c \
	$S/dev/pci/drm/amd/amdgpu/smuio_v13_0.c \
	$S/dev/pci/drm/amd/amdgpu/smuio_v13_0_6.c \
	$S/dev/pci/drm/amd/amdgpu/smuio_v9_0.c \
	$S/dev/pci/drm/amd/amdgpu/soc15.c \
	$S/dev/pci/drm/amd/amdgpu/soc21.c \
	$S/dev/pci/drm/amd/amdgpu/tonga_ih.c \
	$S/dev/pci/drm/amd/amdgpu/umc_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/umc_v6_1.c \
	$S/dev/pci/drm/amd/amdgpu/umc_v6_7.c \
	$S/dev/pci/drm/amd/amdgpu/umc_v8_10.c \
	$S/dev/pci/drm/amd/amdgpu/umc_v8_7.c \
	$S/dev/pci/drm/amd/amdgpu/uvd_v5_0.c \
	$S/dev/pci/drm/amd/amdgpu/uvd_v6_0.c \
	$S/dev/pci/drm/amd/amdgpu/uvd_v7_0.c \
	$S/dev/pci/drm/amd/amdgpu/vce_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/vce_v4_0.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_sw_ring.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_v1_0.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_v2_0.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_v2_5.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_v3_0.c \
	$S/dev/pci/drm/amd/amdgpu/vcn_v4_0.c \
	$S/dev/pci/drm/amd/amdgpu/vega10_ih.c \
	$S/dev/pci/drm/amd/amdgpu/vega10_reg_init.c \
	$S/dev/pci/drm/amd/amdgpu/vega20_ih.c \
	$S/dev/pci/drm/amd/amdgpu/vega20_reg_init.c \
	$S/dev/pci/drm/amd/amdgpu/vi.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_color.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_crtc.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_helpers.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_irq.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_mst_types.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_plane.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_pp_smu.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_psr.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_services.c \
	$S/dev/pci/drm/amd/display/amdgpu_dm/dc_fpu.c \
	$S/dev/pci/drm/amd/display/dc/basics/amdgpu_vector.c \
	$S/dev/pci/drm/amd/display/dc/basics/conversion.c \
	$S/dev/pci/drm/amd/display/dc/basics/dc_common.c \
	$S/dev/pci/drm/amd/display/dc/basics/fixpt31_32.c \
	$S/dev/pci/drm/amd/display/dc/bios/bios_parser.c \
	$S/dev/pci/drm/amd/display/dc/bios/bios_parser2.c \
	$S/dev/pci/drm/amd/display/dc/bios/bios_parser_common.c \
	$S/dev/pci/drm/amd/display/dc/bios/bios_parser_helper.c \
	$S/dev/pci/drm/amd/display/dc/bios/bios_parser_interface.c \
	$S/dev/pci/drm/amd/display/dc/bios/command_table.c \
	$S/dev/pci/drm/amd/display/dc/bios/command_table2.c \
	$S/dev/pci/drm/amd/display/dc/bios/command_table_helper.c \
	$S/dev/pci/drm/amd/display/dc/bios/command_table_helper2.c \
	$S/dev/pci/drm/amd/display/dc/bios/dce110/command_table_helper_dce110.c \
	$S/dev/pci/drm/amd/display/dc/bios/dce112/command_table_helper2_dce112.c \
	$S/dev/pci/drm/amd/display/dc/bios/dce112/command_table_helper_dce112.c \
	$S/dev/pci/drm/amd/display/dc/bios/dce80/command_table_helper_dce80.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dce100/dce_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dce110/dce110_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dce112/dce112_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dce120/dce120_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv1_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv1_clk_mgr_vbios_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv2_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn20/dcn20_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn201/dcn201_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn21/rn_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn21/rn_clk_mgr_vbios_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn30/dcn30_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn30/dcn30_clk_mgr_smu_msg.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn301/dcn301_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn301/vg_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn31/dcn31_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn31/dcn31_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn314/dcn314_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn314/dcn314_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn315/dcn315_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn315/dcn315_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn316/dcn316_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn316/dcn316_smu.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn32/dcn32_clk_mgr.c \
	$S/dev/pci/drm/amd/display/dc/clk_mgr/dcn32/dcn32_clk_mgr_smu_msg.c \
	$S/dev/pci/drm/amd/display/dc/core/amdgpu_dc.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_debug.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link_ddc.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link_dp.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link_dpcd.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link_dpia.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_link_enc_cfg.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_resource.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_sink.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_stat.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_stream.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_surface.c \
	$S/dev/pci/drm/amd/display/dc/core/dc_vm_helper.c \
	$S/dev/pci/drm/amd/display/dc/dc_dmub_srv.c \
	$S/dev/pci/drm/amd/display/dc/dc_edid_parser.c \
	$S/dev/pci/drm/amd/display/dc/dc_helper.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_abm.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_audio.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_aux.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_clock_source.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_dmcu.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_i2c.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_i2c_hw.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_i2c_sw.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_ipp.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_mem_input.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_opp.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_panel_cntl.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_scl_filters.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_scl_filters_old.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dce/dce_transform.c \
	$S/dev/pci/drm/amd/display/dc/dce/dmub_abm.c \
	$S/dev/pci/drm/amd/display/dc/dce/dmub_hw_lock_mgr.c \
	$S/dev/pci/drm/amd/display/dc/dce/dmub_outbox.c \
	$S/dev/pci/drm/amd/display/dc/dce/dmub_psr.c \
	$S/dev/pci/drm/amd/display/dc/dce100/dce100_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dce100/dce100_resource.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_compressor.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_mem_input_v.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_csc_v.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_regamma_v.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_v.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_resource.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_timing_generator.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_timing_generator_v.c \
	$S/dev/pci/drm/amd/display/dc/dce110/dce110_transform_v.c \
	$S/dev/pci/drm/amd/display/dc/dce112/dce112_compressor.c \
	$S/dev/pci/drm/amd/display/dc/dce112/dce112_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dce112/dce112_resource.c \
	$S/dev/pci/drm/amd/display/dc/dce120/dce120_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dce120/dce120_resource.c \
	$S/dev/pci/drm/amd/display/dc/dce120/dce120_timing_generator.c \
	$S/dev/pci/drm/amd/display/dc/dce80/dce80_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dce80/dce80_resource.c \
	$S/dev/pci/drm/amd/display/dc/dce80/dce80_timing_generator.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_cm_common.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp_cm.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp_dscl.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dwb.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hw_sequencer.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hw_sequencer_debug.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_ipp.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_mpc.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_opp.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn10/dcn10_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dpp.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dpp_cm.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dsc.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dwb.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dwb_scl.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_mmhubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_mpc.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_opp.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn20/dcn20_vmid.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_dpp.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_mpc.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_opp.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn201/dcn201_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn21/dcn21_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_afmt.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_cm_common.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dio_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dio_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dpp.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dpp_cm.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dwb.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dwb_cm.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_mmhubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_mpc.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn30/dcn30_vpg.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_dio_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_panel_cntl.c \
	$S/dev/pci/drm/amd/display/dc/dcn301/dcn301_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn302/dcn302_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn302/dcn302_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn302/dcn302_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn303/dcn303_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn303/dcn303_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn303/dcn303_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_afmt.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_apg.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_dio_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hpo_dp_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hpo_dp_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_panel_cntl.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn31/dcn31_vpg.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_dio_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn314/dcn314_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn315/dcn315_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn316/dcn316_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dccg.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dio_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dio_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dpp.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hpo_dp_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hubp.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hwseq.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_init.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_mmhubbub.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_mpc.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_optc.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_resource.c \
	$S/dev/pci/drm/amd/display/dc/dcn32/dcn32_resource_helpers.c \
	$S/dev/pci/drm/amd/display/dc/dcn321/dcn321_dio_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/dcn321/dcn321_resource.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/bw_fixed.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/custom_float.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/dce_calcs.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_auto.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_math.c \
	$S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calcs.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn10/dcn10_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn20/dcn20_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20v2.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20v2.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn21/display_mode_vba_21.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn21/display_rq_dlg_calc_21.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn30/dcn30_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn30/display_mode_vba_30.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn30/display_rq_dlg_calc_30.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn301/dcn301_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn302/dcn302_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn303/dcn303_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn31/dcn31_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn31/display_mode_vba_31.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn31/display_rq_dlg_calc_31.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn314/dcn314_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn314/display_mode_vba_314.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn314/display_rq_dlg_calc_314.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn32/dcn32_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_32.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_util_32.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn32/display_rq_dlg_calc_32.c \
	$S/dev/pci/drm/amd/display/dc/dml/dcn321/dcn321_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dml/display_mode_lib.c \
	$S/dev/pci/drm/amd/display/dc/dml/display_mode_vba.c \
	$S/dev/pci/drm/amd/display/dc/dml/display_rq_dlg_helpers.c \
	$S/dev/pci/drm/amd/display/dc/dml/dml1_display_rq_dlg_calc.c \
	$S/dev/pci/drm/amd/display/dc/dml/dsc/rc_calc_fpu.c \
	$S/dev/pci/drm/amd/display/dc/dsc/dc_dsc.c \
	$S/dev/pci/drm/amd/display/dc/dsc/rc_calc.c \
	$S/dev/pci/drm/amd/display/dc/dsc/rc_calc_dpi.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce110/hw_factory_dce110.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce110/hw_translate_dce110.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce120/hw_factory_dce120.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce120/hw_translate_dce120.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce80/hw_factory_dce80.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dce80/hw_translate_dce80.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn10/hw_factory_dcn10.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn10/hw_translate_dcn10.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn20/hw_factory_dcn20.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn20/hw_translate_dcn20.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn21/hw_factory_dcn21.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn21/hw_translate_dcn21.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn30/hw_factory_dcn30.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn30/hw_translate_dcn30.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn315/hw_factory_dcn315.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn315/hw_translate_dcn315.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn32/hw_factory_dcn32.c \
	$S/dev/pci/drm/amd/display/dc/gpio/dcn32/hw_translate_dcn32.c \
	$S/dev/pci/drm/amd/display/dc/gpio/gpio_base.c \
	$S/dev/pci/drm/amd/display/dc/gpio/gpio_service.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_ddc.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_factory.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_generic.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_gpio.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_hpd.c \
	$S/dev/pci/drm/amd/display/dc/gpio/hw_translate.c \
	$S/dev/pci/drm/amd/display/dc/hdcp/hdcp_msg.c \
	$S/dev/pci/drm/amd/display/dc/irq/dce110/irq_service_dce110.c \
	$S/dev/pci/drm/amd/display/dc/irq/dce120/irq_service_dce120.c \
	$S/dev/pci/drm/amd/display/dc/irq/dce80/irq_service_dce80.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn10/irq_service_dcn10.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn20/irq_service_dcn20.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn201/irq_service_dcn201.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn21/irq_service_dcn21.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn30/irq_service_dcn30.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn302/irq_service_dcn302.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn303/irq_service_dcn303.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn31/irq_service_dcn31.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn314/irq_service_dcn314.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn315/irq_service_dcn315.c \
	$S/dev/pci/drm/amd/display/dc/irq/dcn32/irq_service_dcn32.c \
	$S/dev/pci/drm/amd/display/dc/irq/irq_service.c \
	$S/dev/pci/drm/amd/display/dc/link/link_dp_trace.c \
	$S/dev/pci/drm/amd/display/dc/link/link_hwss_dio.c \
	$S/dev/pci/drm/amd/display/dc/link/link_hwss_dpia.c \
	$S/dev/pci/drm/amd/display/dc/link/link_hwss_hpo_dp.c \
	$S/dev/pci/drm/amd/display/dc/virtual/virtual_link_encoder.c \
	$S/dev/pci/drm/amd/display/dc/virtual/virtual_link_hwss.c \
	$S/dev/pci/drm/amd/display/dc/virtual/virtual_stream_encoder.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn20.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn21.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn30.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn301.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn302.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn303.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn31.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn314.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn315.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn316.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_dcn32.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_reg.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_srv.c \
	$S/dev/pci/drm/amd/display/dmub/src/dmub_srv_stat.c \
	$S/dev/pci/drm/amd/display/modules/color/color_gamma.c \
	$S/dev/pci/drm/amd/display/modules/color/color_table.c \
	$S/dev/pci/drm/amd/display/modules/freesync/freesync.c \
	$S/dev/pci/drm/amd/display/modules/info_packet/info_packet.c \
	$S/dev/pci/drm/amd/display/modules/power/power_helpers.c \
	$S/dev/pci/drm/amd/display/modules/vmid/vmid.c \
	$S/dev/pci/drm/amd/pm/amdgpu_dpm.c \
	$S/dev/pci/drm/amd/pm/amdgpu_dpm_internal.c \
	$S/dev/pci/drm/amd/pm/amdgpu_pm.c \
	$S/dev/pci/drm/amd/pm/legacy-dpm/legacy_dpm.c \
	$S/dev/pci/drm/amd/pm/powerplay/amd_powerplay.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/ci_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/common_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/fiji_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/hardwaremanager.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/polaris_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/pp_overdriver.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/pp_psm.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/ppatomctrl.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/ppatomfwctrl.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/pppcielanes.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/process_pptables_v1_0.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/processpptables.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu10_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_clockpowergating.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_powertune.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_thermal.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu8_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu9_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu_helper.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/tonga_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_powertune.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_processpptables.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_thermal.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_processpptables.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_thermal.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_baco.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_hwmgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_powertune.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_processpptables.c \
	$S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_thermal.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/ci_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/fiji_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/iceland_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/polaris10_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/smu10_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/smu7_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/smu8_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/smu9_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/tonga_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/vega10_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/vega12_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/vega20_smumgr.c \
	$S/dev/pci/drm/amd/pm/powerplay/smumgr/vegam_smumgr.c \
	$S/dev/pci/drm/amd/pm/swsmu/amdgpu_smu.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/arcturus_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/cyan_skillfish_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/navi10_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/sienna_cichlid_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/smu_v11_0.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu11/vangogh_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu12/renoir_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu12/smu_v12_0.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/aldebaran_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_0_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_4_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_5_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_7_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu13/yellow_carp_ppt.c \
	$S/dev/pci/drm/amd/pm/swsmu/smu_cmn.c \
	$S/arch/amd64/pci/pci_machdep.c \
	$S/arch/amd64/pci/pciide_machdep.c $S/arch/amd64/pci/vga_post.c \
	$S/arch/amd64/pci/pchb.c $S/dev/pci/amas.c \
	$S/arch/amd64/pci/agp_machdep.c $S/dev/cardbus/cardslot.c \
	$S/dev/cardbus/cardbus.c $S/dev/cardbus/cardbus_map.c \
	$S/dev/cardbus/cardbus_exrom.c $S/dev/cardbus/rbus.c \
	$S/dev/cardbus/com_cardbus.c $S/dev/cardbus/if_xl_cardbus.c \
	$S/dev/cardbus/if_dc_cardbus.c $S/dev/cardbus/if_fxp_cardbus.c \
	$S/dev/cardbus/if_rl_cardbus.c $S/dev/cardbus/if_re_cardbus.c \
	$S/dev/cardbus/if_ath_cardbus.c $S/dev/cardbus/if_athn_cardbus.c \
	$S/dev/cardbus/if_atw_cardbus.c $S/dev/cardbus/if_rtw_cardbus.c \
	$S/dev/cardbus/if_ral_cardbus.c $S/dev/cardbus/if_acx_cardbus.c \
	$S/dev/cardbus/if_pgt_cardbus.c $S/dev/cardbus/ehci_cardbus.c \
	$S/dev/cardbus/ohci_cardbus.c $S/dev/cardbus/uhci_cardbus.c \
	$S/dev/cardbus/if_malo_cardbus.c $S/dev/cardbus/if_bwi_cardbus.c \
	$S/arch/amd64/amd64/rbus_machdep.c $S/dev/pcmcia/pcmcia.c \
	$S/dev/pcmcia/pcmcia_cis.c $S/dev/pcmcia/pcmcia_cis_quirks.c \
	$S/dev/pcmcia/if_ep_pcmcia.c $S/dev/pcmcia/if_ne_pcmcia.c \
	$S/dev/pcmcia/aic_pcmcia.c $S/dev/pcmcia/com_pcmcia.c \
	$S/dev/pcmcia/wdc_pcmcia.c $S/dev/pcmcia/if_sm_pcmcia.c \
	$S/dev/pcmcia/if_xe.c $S/dev/pcmcia/if_wi_pcmcia.c \
	$S/dev/pcmcia/if_malo.c $S/dev/pcmcia/if_an_pcmcia.c \
	$S/arch/amd64/pci/pcib.c $S/dev/pci/amdpcib.c $S/dev/pci/tcpcib.c \
	$S/arch/amd64/pci/aapic.c $S/dev/ic/hme.c $S/dev/pci/if_hme_pci.c \
	$S/dev/isa/isa.c $S/dev/isa/isadma.c $S/dev/isa/fdc.c \
	$S/dev/isa/fd.c $S/dev/isa/com_isa.c $S/dev/isa/pckbc_isa.c \
	$S/dev/isa/vga_isa.c $S/dev/isa/wdc_isa.c $S/dev/isa/mpu401.c \
	$S/dev/isa/mpu_isa.c $S/dev/isa/pcppi.c $S/dev/isa/spkr.c \
	$S/dev/isa/lpt_isa.c $S/dev/isa/wbsio.c $S/dev/isa/sch311x.c \
	$S/dev/isa/lm78_isa.c $S/dev/isa/it.c $S/dev/isa/uguru.c \
	$S/dev/isa/aps.c $S/arch/amd64/isa/isa_machdep.c \
	$S/dev/wscons/wsdisplay.c $S/dev/wscons/wsdisplay_compat_usl.c \
	$S/dev/wscons/wsevent.c $S/dev/wscons/wskbd.c \
	$S/dev/wscons/wskbdutil.c $S/dev/wscons/wsmouse.c \
	$S/dev/wscons/wstpad.c $S/dev/wscons/wsmux.c \
	$S/dev/wscons/wsemulconf.c $S/dev/wscons/wsemul_subr.c \
	$S/dev/wscons/wsemul_vt100.c $S/dev/wscons/wsemul_vt100_subr.c \
	$S/dev/wscons/wsemul_vt100_chars.c \
	$S/dev/wscons/wsemul_vt100_keys.c $S/dev/pckbc/pckbd.c \
	$S/dev/pckbc/wskbdmap_mfii.c $S/dev/pckbc/pms.c \
	$S/arch/amd64/amd64/wscons_machdep.c $S/dev/isa/skgpio.c \
	$S/arch/amd64/amd64/pctr.c $S/arch/amd64/amd64/nvram.c \
	$S/dev/hid/hid.c $S/dev/hid/hidkbd.c $S/dev/hid/hidms.c \
	$S/dev/hid/hidmt.c $S/dev/hid/hidcc.c $S/dev/usb/usb.c \
	$S/dev/usb/usbdi.c $S/dev/usb/usbdi_util.c $S/dev/usb/usb_mem.c \
	$S/dev/usb/usb_subr.c $S/dev/usb/usb_quirks.c $S/dev/usb/uhub.c \
	$S/dev/usb/uaudio.c $S/dev/usb/uvideo.c $S/dev/usb/utvfu.c \
	$S/dev/usb/udl.c $S/dev/usb/umidi.c $S/dev/usb/umidi_quirks.c \
	$S/dev/usb/ucom.c $S/dev/usb/ugen.c $S/dev/usb/uhidev.c \
	$S/dev/usb/uhid.c $S/dev/usb/fido.c $S/dev/usb/ujoy.c \
	$S/dev/usb/ukbdmap.c $S/dev/usb/ukbd.c $S/dev/usb/ums.c \
	$S/dev/usb/umt.c $S/dev/usb/uts.c $S/dev/usb/ubcmtp.c \
	$S/dev/usb/ucycom.c $S/dev/usb/uslhcom.c $S/dev/usb/ulpt.c \
	$S/dev/usb/umass.c $S/dev/usb/umass_quirks.c \
	$S/dev/usb/umass_scsi.c $S/dev/usb/uthum.c $S/dev/usb/ugold.c \
	$S/dev/usb/utrh.c $S/dev/usb/uoak_subr.c $S/dev/usb/uoakrh.c \
	$S/dev/usb/uoaklux.c $S/dev/usb/uoakv.c $S/dev/usb/uonerng.c \
	$S/dev/usb/urng.c $S/dev/usb/udcf.c $S/dev/usb/umbg.c \
	$S/dev/usb/uvisor.c $S/dev/usb/udsbr.c $S/dev/usb/utwitch.c \
	$S/dev/usb/if_aue.c $S/dev/usb/if_axe.c $S/dev/usb/if_axen.c \
	$S/dev/usb/if_smsc.c $S/dev/usb/if_cue.c $S/dev/usb/if_kue.c \
	$S/dev/usb/if_cdce.c $S/dev/usb/if_urndis.c $S/dev/usb/if_mos.c \
	$S/dev/usb/if_mue.c $S/dev/usb/if_udav.c $S/dev/usb/if_upl.c \
	$S/dev/usb/if_ugl.c $S/dev/usb/if_url.c $S/dev/usb/if_ure.c \
	$S/dev/usb/if_uaq.c $S/dev/usb/umodem.c $S/dev/usb/uftdi.c \
	$S/dev/usb/uplcom.c $S/dev/usb/umct.c $S/dev/usb/uvscom.c \
	$S/dev/usb/ubsa.c $S/dev/usb/ukspan.c $S/dev/usb/uslcom.c \
	$S/dev/usb/uark.c $S/dev/usb/moscom.c $S/dev/usb/umcs.c \
	$S/dev/usb/uscom.c $S/dev/usb/ucrcom.c $S/dev/usb/uxrcom.c \
	$S/dev/usb/uipaq.c $S/dev/usb/umsm.c $S/dev/usb/uchcom.c \
	$S/dev/usb/uticom.c $S/dev/usb/if_wi_usb.c $S/dev/usb/if_atu.c \
	$S/dev/usb/if_ral.c $S/dev/usb/if_rum.c $S/dev/usb/if_run.c \
	$S/dev/usb/if_mtw.c $S/dev/usb/if_zyd.c $S/dev/usb/if_upgt.c \
	$S/dev/usb/if_urtw.c $S/dev/usb/if_urtwn.c $S/dev/usb/if_rsu.c \
	$S/dev/usb/if_otus.c $S/dev/usb/if_umb.c $S/dev/usb/if_uath.c \
	$S/dev/usb/if_athn_usb.c $S/dev/usb/uow.c $S/dev/usb/uberry.c \
	$S/dev/usb/upd.c $S/dev/usb/uwacom.c $S/dev/usb/if_bwfm_usb.c \
	$S/dev/usb/umstc.c $S/dev/usb/uhidpp.c $S/dev/usb/ucc.c \
	$S/dev/i2c/i2c.c $S/dev/i2c/i2c_exec.c $S/dev/i2c/i2c_scan.c \
	$S/dev/i2c/i2c_bitbang.c $S/dev/i2c/lm75.c $S/dev/i2c/lm93.c \
	$S/dev/i2c/lm87.c $S/dev/i2c/maxim6690.c $S/dev/i2c/ad741x.c \
	$S/dev/i2c/adm1021.c $S/dev/i2c/adm1024.c $S/dev/i2c/adm1025.c \
	$S/dev/i2c/adm1030.c $S/dev/i2c/adm1031.c $S/dev/i2c/ds1631.c \
	$S/dev/i2c/adt7460.c $S/dev/i2c/lm78_i2c.c $S/dev/i2c/adm1026.c \
	$S/dev/i2c/w83793g.c $S/dev/i2c/w83795g.c $S/dev/i2c/asc7621.c \
	$S/dev/i2c/asc7611.c $S/dev/i2c/spdmem_i2c.c $S/dev/i2c/sdtemp.c \
	$S/dev/i2c/lis331dl.c $S/dev/i2c/ihidev.c $S/dev/i2c/ikbd.c \
	$S/dev/i2c/ims.c $S/dev/i2c/imt.c $S/dev/i2c/iatp.c \
	$S/dev/i2c/ietp.c $S/dev/i2c/bmc150.c $S/dev/i2c/icc.c \
	$S/dev/gpio/gpio.c $S/dev/acpi/acpi.c $S/dev/acpi/acpiutil.c \
	$S/dev/acpi/dsdt.c $S/dev/acpi/acpidebug.c \
	$S/dev/acpi/acpitimer.c $S/dev/acpi/acpiac.c \
	$S/dev/acpi/acpibat.c $S/dev/acpi/acpibtn.c \
	$S/dev/acpi/acpicmos.c $S/dev/acpi/acpicpu.c \
	$S/dev/acpi/acpihpet.c $S/dev/acpi/acpiec.c $S/dev/acpi/acpitz.c \
	$S/dev/acpi/acpimadt.c $S/dev/acpi/acpimcfg.c \
	$S/dev/acpi/acpiprt.c $S/dev/acpi/acpidmar.c \
	$S/dev/acpi/acpidock.c $S/dev/acpi/abl.c $S/dev/acpi/asmc.c \
	$S/dev/acpi/acpiasus.c $S/dev/acpi/acpithinkpad.c \
	$S/dev/acpi/acpitoshiba.c $S/dev/acpi/acpisony.c \
	$S/dev/acpi/acpivideo.c $S/dev/acpi/acpivout.c \
	$S/dev/acpi/acpipwrres.c $S/dev/acpi/atk0110.c \
	$S/dev/acpi/aplgpio.c $S/dev/acpi/bytgpio.c $S/dev/acpi/chvgpio.c \
	$S/dev/acpi/glkgpio.c $S/dev/acpi/pchgpio.c $S/dev/acpi/tipmic.c \
	$S/dev/acpi/ccpmic.c $S/dev/acpi/com_acpi.c \
	$S/dev/acpi/sdhc_acpi.c $S/dev/acpi/dwiic_acpi.c \
	$S/dev/acpi/acpicbkbd.c $S/dev/acpi/acpials.c $S/dev/acpi/tpm.c \
	$S/dev/acpi/acpihve.c $S/dev/acpi/acpisbs.c \
	$S/dev/acpi/acpisurface.c $S/dev/acpi/ipmi_acpi.c \
	$S/dev/acpi/amdgpio.c $S/dev/acpi/acpihid.c \
	$S/dev/acpi/iosf_acpi.c $S/arch/amd64/amd64/acpi_machdep.c \
	$S/dev/acpi/acpi_x86.c $S/dev/acpi/acpi_apm.c \
	$S/arch/amd64/pci/acpipci.c $S/dev/efi/efi.c \
	$S/arch/amd64/amd64/efi_machdep.c $S/dev/vmm/vmm.c \
	$S/arch/amd64/amd64/vmm_machdep.c $S/dev/sdmmc/sdmmc.c \
	$S/dev/sdmmc/sdmmc_cis.c $S/dev/sdmmc/sdmmc_io.c \
	$S/dev/sdmmc/sdmmc_mem.c $S/dev/sdmmc/sdmmc_scsi.c \
	$S/dev/sdmmc/if_bwfm_sdio.c $S/dev/onewire/onewire.c \
	$S/dev/onewire/onewire_subr.c $S/dev/onewire/owid.c \
	$S/dev/onewire/owsbm.c $S/dev/onewire/owtemp.c \
	$S/dev/onewire/owctr.c

SFILES=	$S/lib/libkern/arch/amd64/strchr.S \
	$S/lib/libkern/arch/amd64/strrchr.S \
	$S/lib/libkern/arch/amd64/memchr.S \
	$S/lib/libkern/arch/amd64/memcmp.S \
	$S/lib/libkern/arch/amd64/bcmp.S \
	$S/lib/libkern/arch/amd64/bzero.S \
	$S/lib/libkern/arch/amd64/bcopy.S \
	$S/lib/libkern/arch/amd64/memcpy.S \
	$S/lib/libkern/arch/amd64/memmove.S \
	$S/lib/libkern/arch/amd64/ffs.S \
	$S/lib/libkern/arch/amd64/memset.S \
	$S/lib/libkern/arch/amd64/strcmp.S \
	$S/lib/libkern/arch/amd64/strlen.S \
	$S/lib/libkern/arch/amd64/scanc.S \
	$S/lib/libkern/arch/amd64/skpc.S \
	$S/lib/libkern/arch/amd64/htonl.S \
	$S/lib/libkern/arch/amd64/htons.S $S/arch/amd64/amd64/locore.S \
	$S/arch/amd64/amd64/aes_intel.S $S/arch/amd64/amd64/vector.S \
	$S/arch/amd64/amd64/copy.S $S/arch/amd64/amd64/spl.S \
	$S/arch/amd64/amd64/mds.S $S/arch/amd64/amd64/mptramp.S \
	$S/arch/amd64/amd64/acpi_wakecode.S \
	$S/arch/amd64/amd64/vmm_support.S

# load lines for config "xxx" will be emitted as:
# xxx: ${SYSTEM_DEP} swapxxx.o
#	${SYSTEM_LD_HEAD}
#	${SYSTEM_LD} swapxxx.o
#	${SYSTEM_LD_TAIL}
SYSTEM_HEAD=	locore0.o gap.o
SYSTEM_OBJ=	${SYSTEM_HEAD} ${OBJS} param.o ioconf.o
SYSTEM_DEP=	Makefile ${SYSTEM_OBJ} ld.script
SYSTEM_LD_HEAD=	@rm -f $@
SYSTEM_LD=	@echo ${LD} ${LINKFLAGS} -o $@ '$${SYSTEM_HEAD} vers.o $${OBJS}'; \
		umask 007; \
		echo ${OBJS} param.o ioconf.o vers.o | tr " " "\n" | ${SORTR} > lorder; \
		${LD} ${LINKFLAGS} -o $@ ${SYSTEM_HEAD} `cat lorder`
SYSTEM_LD_TAIL=	@${SIZE} $@

.if ${DEBUG} == "-g"
STRIPFLAGS=	-S
SYSTEM_LD_TAIL+=; umask 007; \
		echo mv $@ $@.gdb; rm -f $@.gdb; mv $@ $@.gdb; \
		echo ${STRIP} ${STRIPFLAGS} -o $@ $@.gdb; \
		${STRIP} ${STRIPFLAGS} -o $@ $@.gdb
.else
LINKFLAGS+=	-S
.endif

.if ${SYSTEM_OBJ:Mkcov.o} && ${COMPILER_VERSION:Mclang}
PROF=		-fsanitize-coverage=trace-pc,trace-cmp
.endif

.if ${IDENT:M-DKUBSAN} && ${COMPILER_VERSION:Mclang}
CFLAGS+=	-fsanitize=undefined
CFLAGS+=	-fno-wrapv
.endif

all: bsd

bsd: ${SYSTEM_DEP} swapgeneric.o vers.o
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swapgeneric.o
	${SYSTEM_LD_TAIL}

swapgeneric.o: $S/conf/swapgeneric.c
	${NORMAL_C}

newbsd:
	${MAKE_GAP}
	${SYSTEM_LD_HEAD}
	${SYSTEM_LD} swapgeneric.o
	${SYSTEM_LD_TAIL}
	rm -f bsd.gdb
	mv -f newbsd bsd

update-link:
	mkdir -p -m 700 /usr/share/relink/kernel
	rm -rf /usr/share/relink/kernel/GENERIC.MP /usr/share/relink/kernel.tgz
	mkdir /usr/share/relink/kernel/GENERIC.MP
	tar -chf - Makefile makegap.sh ld.script *.o | \
	    tar -C /usr/share/relink/kernel/GENERIC.MP -xf -


# cc's -MD puts the source and output paths in the dependency file;
# since those are temp files here we need to fix it up.  It also
# puts the file in /tmp, so we use -MF to put it in the current
# directory as assym.P and then generate assym.d from it with a
# good target name
assym.h: $S/kern/genassym.sh Makefile \
	 ${_archdir}/${_arch}/genassym.cf ${_machdir}/${_mach}/genassym.cf
	cat ${_archdir}/${_arch}/genassym.cf ${_machdir}/${_mach}/genassym.cf | \
	    sh $S/kern/genassym.sh ${CC} ${NO_INTEGR_AS} ${CFLAGS} ${CPPFLAGS} -MF assym.P > assym.h.tmp
	sed '1s/.*/assym.h: \\/' assym.P > assym.d
	sort -u assym.h.tmp > assym.h

param.c: $S/conf/param.c
	rm -f param.c
	cp $S/conf/param.c .

param.o: param.c Makefile
	${NORMAL_C}

mcount.o: $S/lib/libkern/mcount.c Makefile
	${NORMAL_C_NOP}

ioconf.o: ioconf.c
	${NORMAL_C}

locore.o: assym.h
	${NORMAL_S}
	@[[ -n `objdump -D $@ | grep -A1 doreti_iret | grep -v ^-- | sort | \
	 uniq -d` ]] || \
	 { rm -f $@; echo "ERROR: overlaid iretq instructions don't line up"; \
	   echo "#GP-on-iretq fault handling would be broken"; exit 1; }

ld.script: ${_machdir}/conf/ld.script
	cp ${_machdir}/conf/ld.script $@

gapdummy.o:
	echo '__asm(".section .rodata,\"a\"");' > gapdummy.c
	${CC} -c ${CFLAGS} ${CPPFLAGS} -fcf-protection=none gapdummy.c -o $@

makegap.sh:
	cp $S/conf/makegap.sh $@

MAKE_GAP = LD="${LD}" sh makegap.sh 0xcccccccc gapdummy.o

gap.o:	Makefile makegap.sh gapdummy.o vers.o
	${MAKE_GAP}

vers.o: ${SYSTEM_DEP:Ngap.o}
	sh $S/conf/newvers.sh
	${CC} ${CFLAGS} ${CPPFLAGS} ${PROF} -c vers.c

.if ${SYSTEM_OBJ:Mkcov.o} && ${COMPILER_VERSION:Mclang}
kcov.o: $S/dev/kcov.c
	${NORMAL_C} -fno-sanitize-coverage=trace-pc,trace-cmp
.endif

HARDFLOAT_CFLAGS= -msse -msse2

display_mode_vba.o: $S/dev/pci/drm/amd/display/dc/dml/display_mode_vba.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn10_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn10/dcn10_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn20_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/dcn20_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_20.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_20.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_20v2.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20v2.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_20v2.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20v2.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_21.o: $S/dev/pci/drm/amd/display/dc/dml/dcn21/display_mode_vba_21.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_21.o: $S/dev/pci/drm/amd/display/dc/dml/dcn21/display_rq_dlg_calc_21.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_30.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/display_mode_vba_30.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_30.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/display_rq_dlg_calc_30.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_31.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/display_mode_vba_31.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_31.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/display_rq_dlg_calc_31.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_314.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/display_mode_vba_314.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_314.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/display_rq_dlg_calc_314.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn314_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/dcn314_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn30_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/dcn30_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn32_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/dcn32_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_32.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_calc_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_rq_dlg_calc_32.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_mode_vba_util_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_util_32.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn321_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn321/dcn321_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn31_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/dcn31_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn301_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn301/dcn301_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn302_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn302/dcn302_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn303_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn303/dcn303_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
rc_calc_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dsc/rc_calc_fpu.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn_calcs.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calcs.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn_calc_auto.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_auto.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dcn_calc_math.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_math.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
dml1_display_rq_dlg_calc.o: $S/dev/pci/drm/amd/display/dc/dml/dml1_display_rq_dlg_calc.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}
display_rq_dlg_helpers.o: $S/dev/pci/drm/amd/display/dc/dml/display_rq_dlg_helpers.c
	${NORMAL_C} ${HARDFLOAT_CFLAGS}

clean:
	rm -f *bsd *bsd.gdb *.[dio] [a-z]*.s assym.* \
	    gap.link gapdummy.c ld.script lorder makegap.sh param.c

cleandir: clean
	rm -f Makefile *.h ioconf.c options machine ${_mach} vers.c

depend obj:

locore0.o: ${_machdir}/${_mach}/locore0.S assym.h
mutex.o vector.o copy.o spl.o mds.o: assym.h
mptramp.o acpi_wakecode.o vmm_support.o: assym.h

hardlink-obsd:
	[[ ! -f /bsd ]] || cmp -s bsd /bsd || ln -f /bsd /obsd

newinstall:
	install -F -m 700 bsd /bsd && sha256 -h /var/db/kernel.SHA256 /bsd

install: update-link hardlink-obsd newinstall

# pull in the dependency information
.ifnmake clean
. for o in ${SYSTEM_OBJ:Ngap.o} assym.h
.  if exists(${o:R}.d)
.   include "${o:R}.d"
.  elif exists($o)
    .PHONY: $o
.  endif
. endfor
.endif

.SUFFIXES:
.SUFFIXES: .s .S .c .o

.PHONY: depend all install clean tags newbsd update-link

.c.o:
	${NORMAL_C}

.s.o:
	${NORMAL_S}

.S.o:
	${NORMAL_S}

smc93cx6.o: $S/dev/ic/smc93cx6.c
pcdisplay_subr.o: $S/dev/ic/pcdisplay_subr.c
pcdisplay_chars.o: $S/dev/ic/pcdisplay_chars.c
drm_drv.o: $S/dev/pci/drm/drm_drv.c
vga.o: $S/dev/ic/vga.c
vga_subr.o: $S/dev/ic/vga_subr.c
edid.o: $S/dev/videomode/edid.c
vesagtf.o: $S/dev/videomode/vesagtf.c
videomode.o: $S/dev/videomode/videomode.c
mii_bitbang.o: $S/dev/mii/mii_bitbang.c
wdc.o: $S/dev/ic/wdc.c
aic7xxx.o: $S/dev/ic/aic7xxx.c
aic7xxx_openbsd.o: $S/dev/ic/aic7xxx_openbsd.c
aic7xxx_seeprom.o: $S/dev/ic/aic7xxx_seeprom.c
aic79xx.o: $S/dev/ic/aic79xx.c
aic79xx_openbsd.o: $S/dev/ic/aic79xx_openbsd.c
aic6360.o: $S/dev/ic/aic6360.c
adw.o: $S/dev/ic/adw.c
gdt_common.o: $S/dev/ic/gdt_common.c
twe.o: $S/dev/ic/twe.c
ciss.o: $S/dev/ic/ciss.c
ami.o: $S/dev/ic/ami.c
mfi.o: $S/dev/ic/mfi.c
qlw.o: $S/dev/ic/qlw.c
qla.o: $S/dev/ic/qla.c
ahci.o: $S/dev/ic/ahci.c
nvme.o: $S/dev/ic/nvme.c
mpi.o: $S/dev/ic/mpi.c
sili.o: $S/dev/ic/sili.c
ncr53c9x.o: $S/dev/ic/ncr53c9x.c
siop_common.o: $S/dev/ic/siop_common.c
siop.o: $S/dev/ic/siop.c
elink3.o: $S/dev/ic/elink3.c
if_wi.o: $S/dev/ic/if_wi.c
if_wi_hostap.o: $S/dev/ic/if_wi_hostap.c
an.o: $S/dev/ic/an.c
xl.o: $S/dev/ic/xl.c
fxp.o: $S/dev/ic/fxp.c
rtl81x9.o: $S/dev/ic/rtl81x9.c
re.o: $S/dev/ic/re.c
dc.o: $S/dev/ic/dc.c
smc91cxx.o: $S/dev/ic/smc91cxx.c
smc83c170.o: $S/dev/ic/smc83c170.c
ne2000.o: $S/dev/ic/ne2000.c
dl10019.o: $S/dev/ic/dl10019.c
ax88190.o: $S/dev/ic/ax88190.c
gem.o: $S/dev/ic/gem.c
ti.o: $S/dev/ic/ti.c
com.o: $S/dev/ic/com.c
pckbc.o: $S/dev/ic/pckbc.c
ac97.o: $S/dev/ic/ac97.c
cy.o: $S/dev/ic/cy.c
lpt.o: $S/dev/ic/lpt.c
iha.o: $S/dev/ic/iha.c
lm78.o: $S/dev/ic/lm78.c
ar5xxx.o: $S/dev/ic/ar5xxx.c
ar5210.o: $S/dev/ic/ar5210.c
ar5211.o: $S/dev/ic/ar5211.c
ar5212.o: $S/dev/ic/ar5212.c
ath.o: $S/dev/ic/ath.c
athn.o: $S/dev/ic/athn.c
ar5008.o: $S/dev/ic/ar5008.c
ar5416.o: $S/dev/ic/ar5416.c
ar9280.o: $S/dev/ic/ar9280.c
ar9285.o: $S/dev/ic/ar9285.c
ar9287.o: $S/dev/ic/ar9287.c
ar9003.o: $S/dev/ic/ar9003.c
ar9380.o: $S/dev/ic/ar9380.c
bwfm.o: $S/dev/ic/bwfm.c
atw.o: $S/dev/ic/atw.c
rtw.o: $S/dev/ic/rtw.c
rtwn.o: $S/dev/ic/rtwn.c
rt2560.o: $S/dev/ic/rt2560.c
rt2661.o: $S/dev/ic/rt2661.c
rt2860.o: $S/dev/ic/rt2860.c
acx.o: $S/dev/ic/acx.c
acx111.o: $S/dev/ic/acx111.c
acx100.o: $S/dev/ic/acx100.c
pgt.o: $S/dev/ic/pgt.c
aic6915.o: $S/dev/ic/aic6915.c
malo.o: $S/dev/ic/malo.c
bwi.o: $S/dev/ic/bwi.c
iosf.o: $S/dev/ic/iosf.c
uhci.o: $S/dev/usb/uhci.c
ohci.o: $S/dev/usb/ohci.c
ehci.o: $S/dev/usb/ehci.c
xhci.o: $S/dev/usb/xhci.c
ccp.o: $S/dev/ic/ccp.c
sdhc.o: $S/dev/sdmmc/sdhc.c
rtsx.o: $S/dev/ic/rtsx.c
radio.o: $S/dev/radio.c
ipmi.o: $S/dev/ipmi.c
vscsi.o: $S/dev/vscsi.c
mpath.o: $S/scsi/mpath.c
softraid.o: $S/dev/softraid.c
softraid_concat.o: $S/dev/softraid_concat.c
softraid_crypto.o: $S/dev/softraid_crypto.c
softraid_raid0.o: $S/dev/softraid_raid0.c
softraid_raid1.o: $S/dev/softraid_raid1.c
softraid_raid5.o: $S/dev/softraid_raid5.c
softraid_raid6.o: $S/dev/softraid_raid6.c
softraid_raid1c.o: $S/dev/softraid_raid1c.c
spdmem.o: $S/dev/spdmem.c
dwiic.o: $S/dev/ic/dwiic.c
dwqe.o: $S/dev/ic/dwqe.c
ksyms.o: $S/dev/ksyms.c
kstat.o: $S/dev/kstat.c
fuse_device.o: $S/miscfs/fuse/fuse_device.c
fuse_file.o: $S/miscfs/fuse/fuse_file.c
fuse_lookup.o: $S/miscfs/fuse/fuse_lookup.c
fuse_vfsops.o: $S/miscfs/fuse/fuse_vfsops.c
fuse_vnops.o: $S/miscfs/fuse/fuse_vnops.c
fusebuf.o: $S/miscfs/fuse/fusebuf.c
pf.o: $S/net/pf.c
pf_norm.o: $S/net/pf_norm.c
pf_ruleset.o: $S/net/pf_ruleset.c
pf_ioctl.o: $S/net/pf_ioctl.c
pf_table.o: $S/net/pf_table.c
pf_osfp.o: $S/net/pf_osfp.c
pf_if.o: $S/net/pf_if.c
pf_lb.o: $S/net/pf_lb.c
pf_syncookies.o: $S/net/pf_syncookies.c
hfsc.o: $S/net/hfsc.c
fq_codel.o: $S/net/fq_codel.c
if_pflog.o: $S/net/if_pflog.c
if_pfsync.o: $S/net/if_pfsync.c
if_pflow.o: $S/net/if_pflow.c
bio.o: $S/dev/bio.c
hotplug.o: $S/dev/hotplug.c
if_pppoe.o: $S/net/if_pppoe.c
dt_dev.o: $S/dev/dt/dt_dev.c
dt_prov_profile.o: $S/dev/dt/dt_prov_profile.c
dt_prov_syscall.o: $S/dev/dt/dt_prov_syscall.c
dt_prov_static.o: $S/dev/dt/dt_prov_static.c
dt_prov_kprobe.o: $S/dev/dt/dt_prov_kprobe.c
db_access.o: $S/ddb/db_access.c
db_break.o: $S/ddb/db_break.c
db_command.o: $S/ddb/db_command.c
db_ctf.o: $S/ddb/db_ctf.c
db_dwarf.o: $S/ddb/db_dwarf.c
db_elf.o: $S/ddb/db_elf.c
db_examine.o: $S/ddb/db_examine.c
db_expr.o: $S/ddb/db_expr.c
db_hangman.o: $S/ddb/db_hangman.c
db_input.o: $S/ddb/db_input.c
db_lex.o: $S/ddb/db_lex.c
db_output.o: $S/ddb/db_output.c
db_rint.o: $S/ddb/db_rint.c
db_run.o: $S/ddb/db_run.c
db_sym.o: $S/ddb/db_sym.c
db_trap.o: $S/ddb/db_trap.c
db_variables.o: $S/ddb/db_variables.c
db_watch.o: $S/ddb/db_watch.c
db_usrreq.o: $S/ddb/db_usrreq.c
audio.o: $S/dev/audio.c
cons.o: $S/dev/cons.c
diskmap.o: $S/dev/diskmap.c
firmload.o: $S/dev/firmload.c
dp8390.o: $S/dev/ic/dp8390.c
rtl80x9.o: $S/dev/ic/rtl80x9.c
midi.o: $S/dev/midi.c
mulaw.o: $S/dev/mulaw.c
vnd.o: $S/dev/vnd.c
rnd.o: $S/dev/rnd.c
video.o: $S/dev/video.c
cd9660_bmap.o: $S/isofs/cd9660/cd9660_bmap.c
cd9660_lookup.o: $S/isofs/cd9660/cd9660_lookup.c
cd9660_node.o: $S/isofs/cd9660/cd9660_node.c
cd9660_rrip.o: $S/isofs/cd9660/cd9660_rrip.c
cd9660_util.o: $S/isofs/cd9660/cd9660_util.c
cd9660_vfsops.o: $S/isofs/cd9660/cd9660_vfsops.c
cd9660_vnops.o: $S/isofs/cd9660/cd9660_vnops.c
udf_subr.o: $S/isofs/udf/udf_subr.c
udf_vfsops.o: $S/isofs/udf/udf_vfsops.c
udf_vnops.o: $S/isofs/udf/udf_vnops.c
clock_subr.o: $S/kern/clock_subr.c
exec_conf.o: $S/kern/exec_conf.c
exec_elf.o: $S/kern/exec_elf.c
exec_script.o: $S/kern/exec_script.c
exec_subr.o: $S/kern/exec_subr.c
init_main.o: $S/kern/init_main.c
init_sysent.o: $S/kern/init_sysent.c
kern_acct.o: $S/kern/kern_acct.c
kern_bufq.o: $S/kern/kern_bufq.c
kern_clock.o: $S/kern/kern_clock.c
kern_clockintr.o: $S/kern/kern_clockintr.c
kern_descrip.o: $S/kern/kern_descrip.c
kern_event.o: $S/kern/kern_event.c
kern_exec.o: $S/kern/kern_exec.c
kern_exit.o: $S/kern/kern_exit.c
kern_fork.o: $S/kern/kern_fork.c
kern_kthread.o: $S/kern/kern_kthread.c
kern_ktrace.o: $S/kern/kern_ktrace.c
kern_lock.o: $S/kern/kern_lock.c
kern_malloc.o: $S/kern/kern_malloc.c
kern_rwlock.o: $S/kern/kern_rwlock.c
kern_physio.o: $S/kern/kern_physio.c
kern_proc.o: $S/kern/kern_proc.c
kern_prot.o: $S/kern/kern_prot.c
kern_resource.o: $S/kern/kern_resource.c
kern_pledge.o: $S/kern/kern_pledge.c
kern_unveil.o: $S/kern/kern_unveil.c
kern_sched.o: $S/kern/kern_sched.c
kern_intrmap.o: $S/kern/kern_intrmap.c
kern_sensors.o: $S/kern/kern_sensors.c
kern_sig.o: $S/kern/kern_sig.c
kern_smr.o: $S/kern/kern_smr.c
kern_subr.o: $S/kern/kern_subr.c
kern_sysctl.o: $S/kern/kern_sysctl.c
kern_synch.o: $S/kern/kern_synch.c
kern_tc.o: $S/kern/kern_tc.c
kern_time.o: $S/kern/kern_time.c
kern_timeout.o: $S/kern/kern_timeout.c
kern_uuid.o: $S/kern/kern_uuid.c
kern_watchdog.o: $S/kern/kern_watchdog.c
kern_task.o: $S/kern/kern_task.c
kern_srp.o: $S/kern/kern_srp.c
kern_xxx.o: $S/kern/kern_xxx.c
sched_bsd.o: $S/kern/sched_bsd.c
subr_autoconf.o: $S/kern/subr_autoconf.c
subr_blist.o: $S/kern/subr_blist.c
subr_disk.o: $S/kern/subr_disk.c
subr_evcount.o: $S/kern/subr_evcount.c
subr_extent.o: $S/kern/subr_extent.c
subr_suspend.o: $S/kern/subr_suspend.c
subr_hibernate.o: $S/kern/subr_hibernate.c
subr_log.o: $S/kern/subr_log.c
subr_percpu.o: $S/kern/subr_percpu.c
subr_poison.o: $S/kern/subr_poison.c
subr_pool.o: $S/kern/subr_pool.c
subr_tree.o: $S/kern/subr_tree.c
dma_alloc.o: $S/kern/dma_alloc.c
subr_prf.o: $S/kern/subr_prf.c
subr_prof.o: $S/kern/subr_prof.c
subr_userconf.o: $S/kern/subr_userconf.c
subr_xxx.o: $S/kern/subr_xxx.c
sys_futex.o: $S/kern/sys_futex.c
sys_generic.o: $S/kern/sys_generic.c
sys_pipe.o: $S/kern/sys_pipe.c
sys_process.o: $S/kern/sys_process.c
sys_socket.o: $S/kern/sys_socket.c
sysv_ipc.o: $S/kern/sysv_ipc.c
sysv_msg.o: $S/kern/sysv_msg.c
sysv_sem.o: $S/kern/sysv_sem.c
sysv_shm.o: $S/kern/sysv_shm.c
tty.o: $S/kern/tty.c
tty_conf.o: $S/kern/tty_conf.c
tty_pty.o: $S/kern/tty_pty.c
tty_nmea.o: $S/kern/tty_nmea.c
tty_msts.o: $S/kern/tty_msts.c
tty_endrun.o: $S/kern/tty_endrun.c
tty_subr.o: $S/kern/tty_subr.c
tty_tty.o: $S/kern/tty_tty.c
uipc_domain.o: $S/kern/uipc_domain.c
uipc_mbuf.o: $S/kern/uipc_mbuf.c
uipc_mbuf2.o: $S/kern/uipc_mbuf2.c
uipc_proto.o: $S/kern/uipc_proto.c
uipc_socket.o: $S/kern/uipc_socket.c
uipc_socket2.o: $S/kern/uipc_socket2.c
uipc_syscalls.o: $S/kern/uipc_syscalls.c
uipc_usrreq.o: $S/kern/uipc_usrreq.c
vfs_bio.o: $S/kern/vfs_bio.c
vfs_biomem.o: $S/kern/vfs_biomem.c
vfs_cache.o: $S/kern/vfs_cache.c
vfs_default.o: $S/kern/vfs_default.c
vfs_init.o: $S/kern/vfs_init.c
vfs_lockf.o: $S/kern/vfs_lockf.c
vfs_lookup.o: $S/kern/vfs_lookup.c
vfs_subr.o: $S/kern/vfs_subr.c
vfs_sync.o: $S/kern/vfs_sync.c
vfs_syscalls.o: $S/kern/vfs_syscalls.c
vfs_vops.o: $S/kern/vfs_vops.c
vfs_vnops.o: $S/kern/vfs_vnops.c
vfs_getcwd.o: $S/kern/vfs_getcwd.c
spec_vnops.o: $S/kern/spec_vnops.c
dead_vnops.o: $S/miscfs/deadfs/dead_vnops.c
fifo_vnops.o: $S/miscfs/fifofs/fifo_vnops.c
msdosfs_conv.o: $S/msdosfs/msdosfs_conv.c
msdosfs_denode.o: $S/msdosfs/msdosfs_denode.c
msdosfs_fat.o: $S/msdosfs/msdosfs_fat.c
msdosfs_lookup.o: $S/msdosfs/msdosfs_lookup.c
msdosfs_vfsops.o: $S/msdosfs/msdosfs_vfsops.c
msdosfs_vnops.o: $S/msdosfs/msdosfs_vnops.c
ntfs_compr.o: $S/ntfs/ntfs_compr.c
ntfs_conv.o: $S/ntfs/ntfs_conv.c
ntfs_ihash.o: $S/ntfs/ntfs_ihash.c
ntfs_subr.o: $S/ntfs/ntfs_subr.c
ntfs_vfsops.o: $S/ntfs/ntfs_vfsops.c
ntfs_vnops.o: $S/ntfs/ntfs_vnops.c
hammer2_admin.o: $S/hammer2/hammer2_admin.c
hammer2_bulkfree.o: $S/hammer2/hammer2_bulkfree.c
hammer2_chain.o: $S/hammer2/hammer2_chain.c
hammer2_cluster.o: $S/hammer2/hammer2_cluster.c
hammer2_flush.o: $S/hammer2/hammer2_flush.c
hammer2_freemap.o: $S/hammer2/hammer2_freemap.c
hammer2_inode.o: $S/hammer2/hammer2_inode.c
hammer2_io.o: $S/hammer2/hammer2_io.c
hammer2_ioctl.o: $S/hammer2/hammer2_ioctl.c
hammer2_lz4.o: $S/hammer2/hammer2_lz4.c
hammer2_ondisk.o: $S/hammer2/hammer2_ondisk.c
hammer2_strategy.o: $S/hammer2/hammer2_strategy.c
hammer2_subr.o: $S/hammer2/hammer2_subr.c
hammer2_vfsops.o: $S/hammer2/hammer2_vfsops.c
hammer2_vnops.o: $S/hammer2/hammer2_vnops.c
hammer2_xops.o: $S/hammer2/hammer2_xops.c
xxhash.o: $S/hammer2/xxhash/xxhash.c
art.o: $S/net/art.c
bpf.o: $S/net/bpf.c
bpf_filter.o: $S/net/bpf_filter.c
if.o: $S/net/if.c
ifq.o: $S/net/ifq.c
if_ethersubr.o: $S/net/if_ethersubr.c
if_etherip.o: $S/net/if_etherip.c
if_spppsubr.o: $S/net/if_spppsubr.c
if_loop.o: $S/net/if_loop.c
if_media.o: $S/net/if_media.c
if_ppp.o: $S/net/if_ppp.c
ppp_tty.o: $S/net/ppp_tty.c
bsd-comp.o: $S/net/bsd-comp.c
ppp-deflate.o: $S/net/ppp-deflate.c
if_tun.o: $S/net/if_tun.c
if_bridge.o: $S/net/if_bridge.c
bridgectl.o: $S/net/bridgectl.c
bridgestp.o: $S/net/bridgestp.c
if_etherbridge.o: $S/net/if_etherbridge.c
if_veb.o: $S/net/if_veb.c
if_vlan.o: $S/net/if_vlan.c
pipex.o: $S/net/pipex.c
radix.o: $S/net/radix.c
rtable.o: $S/net/rtable.c
route.o: $S/net/route.c
rtsock.o: $S/net/rtsock.c
slcompress.o: $S/net/slcompress.c
if_enc.o: $S/net/if_enc.c
if_gre.o: $S/net/if_gre.c
if_trunk.o: $S/net/if_trunk.c
trunklacp.o: $S/net/trunklacp.c
if_aggr.o: $S/net/if_aggr.c
if_tpmr.o: $S/net/if_tpmr.c
if_mpe.o: $S/net/if_mpe.c
if_mpw.o: $S/net/if_mpw.c
if_mpip.o: $S/net/if_mpip.c
if_bpe.o: $S/net/if_bpe.c
if_vether.o: $S/net/if_vether.c
if_pair.o: $S/net/if_pair.c
if_pppx.o: $S/net/if_pppx.c
if_vxlan.o: $S/net/if_vxlan.c
if_wg.o: $S/net/if_wg.c
wg_noise.o: $S/net/wg_noise.c
wg_cookie.o: $S/net/wg_cookie.c
toeplitz.o: $S/net/toeplitz.c
ieee80211.o: $S/net80211/ieee80211.c
ieee80211_amrr.o: $S/net80211/ieee80211_amrr.c
ieee80211_crypto.o: $S/net80211/ieee80211_crypto.c
ieee80211_crypto_bip.o: $S/net80211/ieee80211_crypto_bip.c
ieee80211_crypto_ccmp.o: $S/net80211/ieee80211_crypto_ccmp.c
ieee80211_crypto_tkip.o: $S/net80211/ieee80211_crypto_tkip.c
ieee80211_crypto_wep.o: $S/net80211/ieee80211_crypto_wep.c
ieee80211_input.o: $S/net80211/ieee80211_input.c
ieee80211_ioctl.o: $S/net80211/ieee80211_ioctl.c
ieee80211_node.o: $S/net80211/ieee80211_node.c
ieee80211_output.o: $S/net80211/ieee80211_output.c
ieee80211_pae_input.o: $S/net80211/ieee80211_pae_input.c
ieee80211_pae_output.o: $S/net80211/ieee80211_pae_output.c
ieee80211_proto.o: $S/net80211/ieee80211_proto.c
ieee80211_ra.o: $S/net80211/ieee80211_ra.c
ieee80211_ra_vht.o: $S/net80211/ieee80211_ra_vht.c
ieee80211_rssadapt.o: $S/net80211/ieee80211_rssadapt.c
ieee80211_regdomain.o: $S/net80211/ieee80211_regdomain.c
if_ether.o: $S/netinet/if_ether.c
igmp.o: $S/netinet/igmp.c
in.o: $S/netinet/in.c
in_pcb.o: $S/netinet/in_pcb.c
in_proto.o: $S/netinet/in_proto.c
inet_nat64.o: $S/netinet/inet_nat64.c
inet_ntop.o: $S/netinet/inet_ntop.c
ip_divert.o: $S/netinet/ip_divert.c
ip_icmp.o: $S/netinet/ip_icmp.c
ip_id.o: $S/netinet/ip_id.c
ip_input.o: $S/netinet/ip_input.c
ip_mroute.o: $S/netinet/ip_mroute.c
ip_output.o: $S/netinet/ip_output.c
raw_ip.o: $S/netinet/raw_ip.c
tcp_debug.o: $S/netinet/tcp_debug.c
tcp_input.o: $S/netinet/tcp_input.c
tcp_output.o: $S/netinet/tcp_output.c
tcp_subr.o: $S/netinet/tcp_subr.c
tcp_timer.o: $S/netinet/tcp_timer.c
tcp_usrreq.o: $S/netinet/tcp_usrreq.c
udp_usrreq.o: $S/netinet/udp_usrreq.c
ip_gre.o: $S/netinet/ip_gre.c
ip_ipsp.o: $S/netinet/ip_ipsp.c
ip_spd.o: $S/netinet/ip_spd.c
ip_ipip.o: $S/netinet/ip_ipip.c
ipsec_input.o: $S/netinet/ipsec_input.c
ipsec_output.o: $S/netinet/ipsec_output.c
ip_esp.o: $S/netinet/ip_esp.c
ip_ah.o: $S/netinet/ip_ah.c
ip_carp.o: $S/netinet/ip_carp.c
ip_ipcomp.o: $S/netinet/ip_ipcomp.c
aes.o: $S/crypto/aes.c
rijndael.o: $S/crypto/rijndael.c
md5.o: $S/crypto/md5.c
rmd160.o: $S/crypto/rmd160.c
sha1.o: $S/crypto/sha1.c
sha2.o: $S/crypto/sha2.c
blf.o: $S/crypto/blf.c
cast.o: $S/crypto/cast.c
ecb_enc.o: $S/crypto/ecb_enc.c
set_key.o: $S/crypto/set_key.c
ecb3_enc.o: $S/crypto/ecb3_enc.c
crypto.o: $S/crypto/crypto.c
criov.o: $S/crypto/criov.c
cryptosoft.o: $S/crypto/cryptosoft.c
xform.o: $S/crypto/xform.c
xform_ipcomp.o: $S/crypto/xform_ipcomp.c
arc4.o: $S/crypto/arc4.c
michael.o: $S/crypto/michael.c
cmac.o: $S/crypto/cmac.c
hmac.o: $S/crypto/hmac.c
gmac.o: $S/crypto/gmac.c
key_wrap.o: $S/crypto/key_wrap.c
idgen.o: $S/crypto/idgen.c
chachapoly.o: $S/crypto/chachapoly.c
poly1305.o: $S/crypto/poly1305.c
siphash.o: $S/crypto/siphash.c
blake2s.o: $S/crypto/blake2s.c
curve25519.o: $S/crypto/curve25519.c
mpls_input.o: $S/netmpls/mpls_input.c
mpls_output.o: $S/netmpls/mpls_output.c
mpls_proto.o: $S/netmpls/mpls_proto.c
mpls_raw.o: $S/netmpls/mpls_raw.c
mpls_shim.o: $S/netmpls/mpls_shim.c
krpc_subr.o: $S/nfs/krpc_subr.c
nfs_bio.o: $S/nfs/nfs_bio.c
nfs_boot.o: $S/nfs/nfs_boot.c
nfs_debug.o: $S/nfs/nfs_debug.c
nfs_node.o: $S/nfs/nfs_node.c
nfs_kq.o: $S/nfs/nfs_kq.c
nfs_serv.o: $S/nfs/nfs_serv.c
nfs_socket.o: $S/nfs/nfs_socket.c
nfs_srvcache.o: $S/nfs/nfs_srvcache.c
nfs_subs.o: $S/nfs/nfs_subs.c
nfs_syscalls.o: $S/nfs/nfs_syscalls.c
nfs_vfsops.o: $S/nfs/nfs_vfsops.c
nfs_vnops.o: $S/nfs/nfs_vnops.c
ffs_alloc.o: $S/ufs/ffs/ffs_alloc.c
ffs_balloc.o: $S/ufs/ffs/ffs_balloc.c
ffs_inode.o: $S/ufs/ffs/ffs_inode.c
ffs_subr.o: $S/ufs/ffs/ffs_subr.c
ffs_softdep_stub.o: $S/ufs/ffs/ffs_softdep_stub.c
ffs_tables.o: $S/ufs/ffs/ffs_tables.c
ffs_vfsops.o: $S/ufs/ffs/ffs_vfsops.c
ffs_vnops.o: $S/ufs/ffs/ffs_vnops.c
ffs_softdep.o: $S/ufs/ffs/ffs_softdep.c
mfs_vfsops.o: $S/ufs/mfs/mfs_vfsops.c
mfs_vnops.o: $S/ufs/mfs/mfs_vnops.c
ufs_bmap.o: $S/ufs/ufs/ufs_bmap.c
ufs_dirhash.o: $S/ufs/ufs/ufs_dirhash.c
ufs_ihash.o: $S/ufs/ufs/ufs_ihash.c
ufs_inode.o: $S/ufs/ufs/ufs_inode.c
ufs_lookup.o: $S/ufs/ufs/ufs_lookup.c
ufs_quota.o: $S/ufs/ufs/ufs_quota.c
ufs_quota_stub.o: $S/ufs/ufs/ufs_quota_stub.c
ufs_vfsops.o: $S/ufs/ufs/ufs_vfsops.c
ufs_vnops.o: $S/ufs/ufs/ufs_vnops.c
ext2fs_alloc.o: $S/ufs/ext2fs/ext2fs_alloc.c
ext2fs_balloc.o: $S/ufs/ext2fs/ext2fs_balloc.c
ext2fs_bmap.o: $S/ufs/ext2fs/ext2fs_bmap.c
ext2fs_bswap.o: $S/ufs/ext2fs/ext2fs_bswap.c
ext2fs_extents.o: $S/ufs/ext2fs/ext2fs_extents.c
ext2fs_inode.o: $S/ufs/ext2fs/ext2fs_inode.c
ext2fs_lookup.o: $S/ufs/ext2fs/ext2fs_lookup.c
ext2fs_readwrite.o: $S/ufs/ext2fs/ext2fs_readwrite.c
ext2fs_subr.o: $S/ufs/ext2fs/ext2fs_subr.c
ext2fs_vfsops.o: $S/ufs/ext2fs/ext2fs_vfsops.c
ext2fs_vnops.o: $S/ufs/ext2fs/ext2fs_vnops.c
uvm_addr.o: $S/uvm/uvm_addr.c
uvm_amap.o: $S/uvm/uvm_amap.c
uvm_anon.o: $S/uvm/uvm_anon.c
uvm_aobj.o: $S/uvm/uvm_aobj.c
uvm_device.o: $S/uvm/uvm_device.c
uvm_fault.o: $S/uvm/uvm_fault.c
uvm_glue.o: $S/uvm/uvm_glue.c
uvm_init.o: $S/uvm/uvm_init.c
uvm_io.o: $S/uvm/uvm_io.c
uvm_km.o: $S/uvm/uvm_km.c
uvm_map.o: $S/uvm/uvm_map.c
uvm_meter.o: $S/uvm/uvm_meter.c
uvm_mmap.o: $S/uvm/uvm_mmap.c
uvm_object.o: $S/uvm/uvm_object.c
uvm_page.o: $S/uvm/uvm_page.c
uvm_pager.o: $S/uvm/uvm_pager.c
uvm_pdaemon.o: $S/uvm/uvm_pdaemon.c
uvm_pmemrange.o: $S/uvm/uvm_pmemrange.c
uvm_swap.o: $S/uvm/uvm_swap.c
uvm_swap_encrypt.o: $S/uvm/uvm_swap_encrypt.c
uvm_unix.o: $S/uvm/uvm_unix.c
uvm_vnode.o: $S/uvm/uvm_vnode.c
if_gif.o: $S/net/if_gif.c
if_sec.o: $S/net/if_sec.c
ip_ecn.o: $S/netinet/ip_ecn.c
in6_pcb.o: $S/netinet6/in6_pcb.c
in6.o: $S/netinet6/in6.c
ip6_divert.o: $S/netinet6/ip6_divert.c
in6_ifattach.o: $S/netinet6/in6_ifattach.c
in6_cksum.o: $S/netinet6/in6_cksum.c
in6_src.o: $S/netinet6/in6_src.c
in6_proto.o: $S/netinet6/in6_proto.c
dest6.o: $S/netinet6/dest6.c
frag6.o: $S/netinet6/frag6.c
icmp6.o: $S/netinet6/icmp6.c
ip6_id.o: $S/netinet6/ip6_id.c
ip6_input.o: $S/netinet6/ip6_input.c
ip6_forward.o: $S/netinet6/ip6_forward.c
ip6_mroute.o: $S/netinet6/ip6_mroute.c
ip6_output.o: $S/netinet6/ip6_output.c
route6.o: $S/netinet6/route6.c
mld6.o: $S/netinet6/mld6.c
nd6.o: $S/netinet6/nd6.c
nd6_nbr.o: $S/netinet6/nd6_nbr.c
nd6_rtr.o: $S/netinet6/nd6_rtr.c
raw_ip6.o: $S/netinet6/raw_ip6.c
udp6_output.o: $S/netinet6/udp6_output.c
pfkeyv2.o: $S/net/pfkeyv2.c
pfkeyv2_parsemessage.o: $S/net/pfkeyv2_parsemessage.c
pfkeyv2_convert.o: $S/net/pfkeyv2_convert.c
x86emu.o: $S/dev/x86emu/x86emu.c
x86emu_util.o: $S/dev/x86emu/x86emu_util.c
getsn.o: $S/lib/libkern/getsn.c
random.o: $S/lib/libkern/random.c
explicit_bzero.o: $S/lib/libkern/explicit_bzero.c
timingsafe_bcmp.o: $S/lib/libkern/timingsafe_bcmp.c
icrc32.o: $S/lib/libkern/icrc32.c
strchr.o: $S/lib/libkern/arch/amd64/strchr.S
strrchr.o: $S/lib/libkern/arch/amd64/strrchr.S
imax.o: $S/lib/libkern/imax.c
imin.o: $S/lib/libkern/imin.c
lmax.o: $S/lib/libkern/lmax.c
lmin.o: $S/lib/libkern/lmin.c
max.o: $S/lib/libkern/max.c
min.o: $S/lib/libkern/min.c
ulmax.o: $S/lib/libkern/ulmax.c
ulmin.o: $S/lib/libkern/ulmin.c
memchr.o: $S/lib/libkern/arch/amd64/memchr.S
memcmp.o: $S/lib/libkern/arch/amd64/memcmp.S
bcmp.o: $S/lib/libkern/arch/amd64/bcmp.S
bzero.o: $S/lib/libkern/arch/amd64/bzero.S
bcopy.o: $S/lib/libkern/arch/amd64/bcopy.S
memcpy.o: $S/lib/libkern/arch/amd64/memcpy.S
memmove.o: $S/lib/libkern/arch/amd64/memmove.S
ffs.o: $S/lib/libkern/arch/amd64/ffs.S
fls.o: $S/lib/libkern/fls.c
flsl.o: $S/lib/libkern/flsl.c
memset.o: $S/lib/libkern/arch/amd64/memset.S
strcmp.o: $S/lib/libkern/arch/amd64/strcmp.S
strlcat.o: $S/lib/libkern/strlcat.c
strlcpy.o: $S/lib/libkern/strlcpy.c
strlen.o: $S/lib/libkern/arch/amd64/strlen.S
strncmp.o: $S/lib/libkern/strncmp.c
strncpy.o: $S/lib/libkern/strncpy.c
strnlen.o: $S/lib/libkern/strnlen.c
scanc.o: $S/lib/libkern/arch/amd64/scanc.S
skpc.o: $S/lib/libkern/arch/amd64/skpc.S
htonl.o: $S/lib/libkern/arch/amd64/htonl.S
htons.o: $S/lib/libkern/arch/amd64/htons.S
strncasecmp.o: $S/lib/libkern/strncasecmp.c
adler32.o: $S/lib/libz/adler32.c
crc32.o: $S/lib/libz/crc32.c
infback.o: $S/lib/libz/infback.c
inffast.o: $S/lib/libz/inffast.c
inflate.o: $S/lib/libz/inflate.c
inftrees.o: $S/lib/libz/inftrees.c
deflate.o: $S/lib/libz/deflate.c
zutil.o: $S/lib/libz/zutil.c
zopenbsd.o: $S/lib/libz/zopenbsd.c
trees.o: $S/lib/libz/trees.c
compress.o: $S/lib/libz/compress.c
autoconf.o: $S/arch/amd64/amd64/autoconf.c
conf.o: $S/arch/amd64/amd64/conf.c
disksubr.o: $S/arch/amd64/amd64/disksubr.c
gdt.o: $S/arch/amd64/amd64/gdt.c
machdep.o: $S/arch/amd64/amd64/machdep.c
hibernate_machdep.o: $S/arch/amd64/amd64/hibernate_machdep.c
identcpu.o: $S/arch/amd64/amd64/identcpu.c
tsc.o: $S/arch/amd64/amd64/tsc.c
via.o: $S/arch/amd64/amd64/via.c
locore.o: $S/arch/amd64/amd64/locore.S
aes_intel.o: $S/arch/amd64/amd64/aes_intel.S
aesni.o: $S/arch/amd64/amd64/aesni.c
amd64errata.o: $S/arch/amd64/amd64/amd64errata.c
ucode.o: $S/arch/amd64/amd64/ucode.c
mem.o: $S/arch/amd64/amd64/mem.c
amd64_mem.o: $S/arch/amd64/amd64/amd64_mem.c
mtrr.o: $S/arch/amd64/amd64/mtrr.c
pmap.o: $S/arch/amd64/amd64/pmap.c
process_machdep.o: $S/arch/amd64/amd64/process_machdep.c
sys_machdep.o: $S/arch/amd64/amd64/sys_machdep.c
trap.o: $S/arch/amd64/amd64/trap.c
vm_machdep.o: $S/arch/amd64/amd64/vm_machdep.c
fpu.o: $S/arch/amd64/amd64/fpu.c
softintr.o: $S/arch/amd64/amd64/softintr.c
i8259.o: $S/arch/amd64/amd64/i8259.c
cacheinfo.o: $S/arch/amd64/amd64/cacheinfo.c
vector.o: $S/arch/amd64/amd64/vector.S
copy.o: $S/arch/amd64/amd64/copy.S
spl.o: $S/arch/amd64/amd64/spl.S
mds.o: $S/arch/amd64/amd64/mds.S
intr.o: $S/arch/amd64/amd64/intr.c
bus_space.o: $S/arch/amd64/amd64/bus_space.c
bus_dma.o: $S/arch/amd64/amd64/bus_dma.c
mptramp.o: $S/arch/amd64/amd64/mptramp.S
ipifuncs.o: $S/arch/amd64/amd64/ipifuncs.c
ipi.o: $S/arch/amd64/amd64/ipi.c
mp_setperf.o: $S/arch/amd64/amd64/mp_setperf.c
apic.o: $S/arch/amd64/amd64/apic.c
consinit.o: $S/arch/amd64/amd64/consinit.c
cninit.o: $S/dev/cninit.c
dkcsum.o: $S/arch/amd64/amd64/dkcsum.c
db_disasm.o: $S/arch/amd64/amd64/db_disasm.c
db_interface.o: $S/arch/amd64/amd64/db_interface.c
db_memrw.o: $S/arch/amd64/amd64/db_memrw.c
db_trace.o: $S/arch/amd64/amd64/db_trace.c
in_cksum.o: $S/netinet/in_cksum.c
in4_cksum.o: $S/netinet/in4_cksum.c
clock.o: $S/arch/amd64/isa/clock.c
powernow-k8.o: $S/arch/amd64/amd64/powernow-k8.c
est.o: $S/arch/amd64/amd64/est.c
k1x-pstate.o: $S/arch/amd64/amd64/k1x-pstate.c
rasops.o: $S/dev/rasops/rasops.c
rasops8.o: $S/dev/rasops/rasops8.c
rasops15.o: $S/dev/rasops/rasops15.c
rasops24.o: $S/dev/rasops/rasops24.c
rasops32.o: $S/dev/rasops/rasops32.c
wsfont.o: $S/dev/wsfont/wsfont.c
mii.o: $S/dev/mii/mii.c
mii_physubr.o: $S/dev/mii/mii_physubr.c
ukphy_subr.o: $S/dev/mii/ukphy_subr.c
nsphy.o: $S/dev/mii/nsphy.c
nsphyter.o: $S/dev/mii/nsphyter.c
gentbi.o: $S/dev/mii/gentbi.c
qsphy.o: $S/dev/mii/qsphy.c
inphy.o: $S/dev/mii/inphy.c
iophy.o: $S/dev/mii/iophy.c
eephy.o: $S/dev/mii/eephy.c
exphy.o: $S/dev/mii/exphy.c
rlphy.o: $S/dev/mii/rlphy.c
lxtphy.o: $S/dev/mii/lxtphy.c
luphy.o: $S/dev/mii/luphy.c
mtdphy.o: $S/dev/mii/mtdphy.c
icsphy.o: $S/dev/mii/icsphy.c
sqphy.o: $S/dev/mii/sqphy.c
tqphy.o: $S/dev/mii/tqphy.c
ukphy.o: $S/dev/mii/ukphy.c
dcphy.o: $S/dev/mii/dcphy.c
bmtphy.o: $S/dev/mii/bmtphy.c
brgphy.o: $S/dev/mii/brgphy.c
xmphy.o: $S/dev/mii/xmphy.c
amphy.o: $S/dev/mii/amphy.c
acphy.o: $S/dev/mii/acphy.c
nsgphy.o: $S/dev/mii/nsgphy.c
urlphy.o: $S/dev/mii/urlphy.c
rgephy.o: $S/dev/mii/rgephy.c
ciphy.o: $S/dev/mii/ciphy.c
ipgphy.o: $S/dev/mii/ipgphy.c
etphy.o: $S/dev/mii/etphy.c
jmphy.o: $S/dev/mii/jmphy.c
atphy.o: $S/dev/mii/atphy.c
scsi_base.o: $S/scsi/scsi_base.c
scsi_ioctl.o: $S/scsi/scsi_ioctl.c
scsiconf.o: $S/scsi/scsiconf.c
cd.o: $S/scsi/cd.c
ch.o: $S/scsi/ch.c
sd.o: $S/scsi/sd.c
st.o: $S/scsi/st.c
uk.o: $S/scsi/uk.c
safte.o: $S/scsi/safte.c
ses.o: $S/scsi/ses.c
mpath_sym.o: $S/scsi/mpath_sym.c
mpath_rdac.o: $S/scsi/mpath_rdac.c
mpath_emc.o: $S/scsi/mpath_emc.c
mpath_hds.o: $S/scsi/mpath_hds.c
atapiscsi.o: $S/dev/atapiscsi/atapiscsi.c
wd.o: $S/dev/ata/wd.c
ata_wdc.o: $S/dev/ata/ata_wdc.c
ata.o: $S/dev/ata/ata.c
atascsi.o: $S/dev/ata/atascsi.c
mainbus.o: $S/arch/amd64/amd64/mainbus.c
codepatch.o: $S/arch/amd64/amd64/codepatch.c
bios.o: $S/arch/amd64/amd64/bios.c
mpbios.o: $S/arch/amd64/amd64/mpbios.c
mpbios_intr_fixup.o: $S/arch/amd64/amd64/mpbios_intr_fixup.c
cpu.o: $S/arch/amd64/amd64/cpu.c
lapic.o: $S/arch/amd64/amd64/lapic.c
ioapic.o: $S/arch/amd64/amd64/ioapic.c
efifb.o: $S/arch/amd64/amd64/efifb.c
pvbus.o: $S/dev/pv/pvbus.c
pvclock.o: $S/dev/pv/pvclock.c
vmt.o: $S/dev/pv/vmt.c
xen.o: $S/dev/pv/xen.c
xenstore.o: $S/dev/pv/xenstore.c
if_xnf.o: $S/dev/pv/if_xnf.c
xbf.o: $S/dev/pv/xbf.c
hyperv.o: $S/dev/pv/hyperv.c
hypervic.o: $S/dev/pv/hypervic.c
if_hvn.o: $S/dev/pv/if_hvn.c
hvs.o: $S/dev/pv/hvs.c
virtio.o: $S/dev/pv/virtio.c
if_vio.o: $S/dev/pv/if_vio.c
vioblk.o: $S/dev/pv/vioblk.c
viomb.o: $S/dev/pv/viomb.c
viornd.o: $S/dev/pv/viornd.c
vioscsi.o: $S/dev/pv/vioscsi.c
vmmci.o: $S/dev/pv/vmmci.c
pci.o: $S/dev/pci/pci.c
pci_map.o: $S/dev/pci/pci_map.c
pci_quirks.o: $S/dev/pci/pci_quirks.c
pci_subr.o: $S/dev/pci/pci_subr.c
vga_pci.o: $S/dev/pci/vga_pci.c
vga_pci_common.o: $S/dev/pci/vga_pci_common.c
cy82c693.o: $S/dev/pci/cy82c693.c
ahc_pci.o: $S/dev/pci/ahc_pci.c
ahd_pci.o: $S/dev/pci/ahd_pci.c
adw_pci.o: $S/dev/pci/adw_pci.c
adwlib.o: $S/dev/ic/adwlib.c
adwmcode.o: $S/dev/microcode/adw/adwmcode.c
twe_pci.o: $S/dev/pci/twe_pci.c
arc.o: $S/dev/pci/arc.c
jmb.o: $S/dev/pci/jmb.c
ahci_pci.o: $S/dev/pci/ahci_pci.c
nvme_pci.o: $S/dev/pci/nvme_pci.c
ami_pci.o: $S/dev/pci/ami_pci.c
mfi_pci.o: $S/dev/pci/mfi_pci.c
mfii.o: $S/dev/pci/mfii.c
ips.o: $S/dev/pci/ips.c
eap.o: $S/dev/pci/eap.c
auacer.o: $S/dev/pci/auacer.c
auich.o: $S/dev/pci/auich.c
azalia.o: $S/dev/pci/azalia.c
azalia_codec.o: $S/dev/pci/azalia_codec.c
envy.o: $S/dev/pci/envy.c
emuxki.o: $S/dev/pci/emuxki.c
auixp.o: $S/dev/pci/auixp.c
cs4280.o: $S/dev/pci/cs4280.c
yds.o: $S/dev/pci/yds.c
auvia.o: $S/dev/pci/auvia.c
gdt_pci.o: $S/dev/pci/gdt_pci.c
ciss_pci.o: $S/dev/pci/ciss_pci.c
qlw_pci.o: $S/dev/pci/qlw_pci.c
qla_pci.o: $S/dev/pci/qla_pci.c
qle.o: $S/dev/pci/qle.c
mpi_pci.o: $S/dev/pci/mpi_pci.c
mpii.o: $S/dev/pci/mpii.c
sili_pci.o: $S/dev/pci/sili_pci.c
if_aq_pci.o: $S/dev/pci/if_aq_pci.c
if_de.o: $S/dev/pci/if_de.c
if_ep_pci.o: $S/dev/pci/if_ep_pci.c
if_pcn.o: $S/dev/pci/if_pcn.c
siop_pci_common.o: $S/dev/pci/siop_pci_common.c
siop_pci.o: $S/dev/pci/siop_pci.c
pciide.o: $S/dev/pci/pciide.c
ppb.o: $S/dev/pci/ppb.c
cy_pci.o: $S/dev/pci/cy_pci.c
if_rl_pci.o: $S/dev/pci/if_rl_pci.c
if_re_pci.o: $S/dev/pci/if_re_pci.c
if_vr.o: $S/dev/pci/if_vr.c
if_txp.o: $S/dev/pci/if_txp.c
bktr_audio.o: $S/dev/pci/bktr/bktr_audio.c
bktr_card.o: $S/dev/pci/bktr/bktr_card.c
bktr_core.o: $S/dev/pci/bktr/bktr_core.c
bktr_os.o: $S/dev/pci/bktr/bktr_os.c
bktr_tuner.o: $S/dev/pci/bktr/bktr_tuner.c
if_xl_pci.o: $S/dev/pci/if_xl_pci.c
if_fxp_pci.o: $S/dev/pci/if_fxp_pci.c
if_em.o: $S/dev/pci/if_em.c
if_em_hw.o: $S/dev/pci/if_em_hw.c
if_em_soc.o: $S/dev/pci/if_em_soc.c
if_ixgb.o: $S/dev/pci/if_ixgb.c
ixgb_ee.o: $S/dev/pci/ixgb_ee.c
ixgb_hw.o: $S/dev/pci/ixgb_hw.c
if_ix.o: $S/dev/pci/if_ix.c
ixgbe.o: $S/dev/pci/ixgbe.c
ixgbe_82598.o: $S/dev/pci/ixgbe_82598.c
ixgbe_82599.o: $S/dev/pci/ixgbe_82599.c
ixgbe_x540.o: $S/dev/pci/ixgbe_x540.c
ixgbe_x550.o: $S/dev/pci/ixgbe_x550.c
ixgbe_phy.o: $S/dev/pci/ixgbe_phy.c
if_ixl.o: $S/dev/pci/if_ixl.c
if_dwqe_pci.o: $S/dev/pci/if_dwqe_pci.c
if_xge.o: $S/dev/pci/if_xge.c
if_tht.o: $S/dev/pci/if_tht.c
if_myx.o: $S/dev/pci/if_myx.c
if_oce.o: $S/dev/pci/if_oce.c
if_dc_pci.o: $S/dev/pci/if_dc_pci.c
if_epic_pci.o: $S/dev/pci/if_epic_pci.c
if_ti_pci.o: $S/dev/pci/if_ti_pci.c
if_ne_pci.o: $S/dev/pci/if_ne_pci.c
if_gem_pci.o: $S/dev/pci/if_gem_pci.c
if_cas.o: $S/dev/pci/if_cas.c
if_sf_pci.o: $S/dev/pci/if_sf_pci.c
if_sis.o: $S/dev/pci/if_sis.c
if_se.o: $S/dev/pci/if_se.c
mbg.o: $S/dev/pci/mbg.c
uhci_pci.o: $S/dev/pci/uhci_pci.c
ohci_pci.o: $S/dev/pci/ohci_pci.c
ehci_pci.o: $S/dev/pci/ehci_pci.c
xhci_pci.o: $S/dev/pci/xhci_pci.c
pccbb.o: $S/dev/pci/pccbb.c
if_sk.o: $S/dev/pci/if_sk.c
if_msk.o: $S/dev/pci/if_msk.c
puc.o: $S/dev/pci/puc.c
pucdata.o: $S/dev/pci/pucdata.c
com_puc.o: $S/dev/puc/com_puc.c
lpt_puc.o: $S/dev/puc/lpt_puc.c
if_wi_pci.o: $S/dev/pci/if_wi_pci.c
if_an_pci.o: $S/dev/pci/if_an_pci.c
if_iwi.o: $S/dev/pci/if_iwi.c
if_wpi.o: $S/dev/pci/if_wpi.c
if_iwn.o: $S/dev/pci/if_iwn.c
if_iwm.o: $S/dev/pci/if_iwm.c
if_iwx.o: $S/dev/pci/if_iwx.c
cmpci.o: $S/dev/pci/cmpci.c
iha_pci.o: $S/dev/pci/iha_pci.c
pcscp.o: $S/dev/pci/pcscp.c
if_bge.o: $S/dev/pci/if_bge.c
if_bnx.o: $S/dev/pci/if_bnx.c
if_vge.o: $S/dev/pci/if_vge.c
if_stge.o: $S/dev/pci/if_stge.c
if_nfe.o: $S/dev/pci/if_nfe.c
if_et.o: $S/dev/pci/if_et.c
if_jme.o: $S/dev/pci/if_jme.c
if_age.o: $S/dev/pci/if_age.c
if_alc.o: $S/dev/pci/if_alc.c
if_ale.o: $S/dev/pci/if_ale.c
amdpm.o: $S/dev/pci/amdpm.c
if_bce.o: $S/dev/pci/if_bce.c
if_ath_pci.o: $S/dev/pci/if_ath_pci.c
if_athn_pci.o: $S/dev/pci/if_athn_pci.c
if_atw_pci.o: $S/dev/pci/if_atw_pci.c
if_rtw_pci.o: $S/dev/pci/if_rtw_pci.c
if_rtwn.o: $S/dev/pci/if_rtwn.c
if_ral_pci.o: $S/dev/pci/if_ral_pci.c
if_acx_pci.o: $S/dev/pci/if_acx_pci.c
if_pgt_pci.o: $S/dev/pci/if_pgt_pci.c
if_malo_pci.o: $S/dev/pci/if_malo_pci.c
if_bwi_pci.o: $S/dev/pci/if_bwi_pci.c
piixpm.o: $S/dev/pci/piixpm.c
if_vic.o: $S/dev/pci/if_vic.c
if_vmx.o: $S/dev/pci/if_vmx.c
vmwpvs.o: $S/dev/pci/vmwpvs.c
if_lii.o: $S/dev/pci/if_lii.c
ichiic.o: $S/dev/pci/ichiic.c
viapm.o: $S/dev/pci/viapm.c
amdiic.o: $S/dev/pci/amdiic.c
nviic.o: $S/dev/pci/nviic.c
sdhc_pci.o: $S/dev/pci/sdhc_pci.c
kate.o: $S/dev/pci/kate.c
km.o: $S/dev/pci/km.c
ksmn.o: $S/dev/pci/ksmn.c
iosf_pci.o: $S/dev/pci/iosf_pci.c
itherm.o: $S/dev/pci/itherm.c
pchtemp.o: $S/dev/pci/pchtemp.c
rtsx_pci.o: $S/dev/pci/rtsx_pci.c
xspd.o: $S/dev/pci/xspd.c
virtio_pci.o: $S/dev/pci/virtio_pci.c
dwiic_pci.o: $S/dev/pci/dwiic_pci.c
if_bwfm_pci.o: $S/dev/pci/if_bwfm_pci.c
ccp_pci.o: $S/dev/pci/ccp_pci.c
if_bnxt.o: $S/dev/pci/if_bnxt.c
if_mcx.o: $S/dev/pci/if_mcx.c
if_iavf.o: $S/dev/pci/if_iavf.c
if_rge.o: $S/dev/pci/if_rge.c
if_igc.o: $S/dev/pci/if_igc.c
igc_api.o: $S/dev/pci/igc_api.c
igc_base.o: $S/dev/pci/igc_base.c
igc_i225.o: $S/dev/pci/igc_i225.c
igc_mac.o: $S/dev/pci/igc_mac.c
igc_nvm.o: $S/dev/pci/igc_nvm.c
igc_phy.o: $S/dev/pci/igc_phy.c
if_ngbe.o: $S/dev/pci/if_ngbe.c
com_pci.o: $S/dev/pci/com_pci.c
agp.o: $S/dev/pci/agp.c
agp_i810.o: $S/dev/pci/agp_i810.c
dma-resv.o: $S/dev/pci/drm/dma-resv.c
drm_agpsupport.o: $S/dev/pci/drm/drm_agpsupport.c
drm_aperture.o: $S/dev/pci/drm/drm_aperture.c
drm_atomic.o: $S/dev/pci/drm/drm_atomic.c
drm_atomic_helper.o: $S/dev/pci/drm/drm_atomic_helper.c
drm_atomic_state_helper.o: $S/dev/pci/drm/drm_atomic_state_helper.c
drm_atomic_uapi.o: $S/dev/pci/drm/drm_atomic_uapi.c
drm_auth.o: $S/dev/pci/drm/drm_auth.c
drm_blend.o: $S/dev/pci/drm/drm_blend.c
drm_bridge.o: $S/dev/pci/drm/drm_bridge.c
drm_buddy.o: $S/dev/pci/drm/drm_buddy.c
drm_cache.o: $S/dev/pci/drm/drm_cache.c
drm_client.o: $S/dev/pci/drm/drm_client.c
drm_client_modeset.o: $S/dev/pci/drm/drm_client_modeset.c
drm_color_mgmt.o: $S/dev/pci/drm/drm_color_mgmt.c
drm_connector.o: $S/dev/pci/drm/drm_connector.c
drm_crtc.o: $S/dev/pci/drm/drm_crtc.c
drm_crtc_helper.o: $S/dev/pci/drm/drm_crtc_helper.c
drm_damage_helper.o: $S/dev/pci/drm/drm_damage_helper.c
drm_displayid.o: $S/dev/pci/drm/drm_displayid.c
drm_dumb_buffers.o: $S/dev/pci/drm/drm_dumb_buffers.c
drm_edid.o: $S/dev/pci/drm/drm_edid.c
drm_encoder.o: $S/dev/pci/drm/drm_encoder.c
drm_encoder_slave.o: $S/dev/pci/drm/drm_encoder_slave.c
drm_fb_helper.o: $S/dev/pci/drm/drm_fb_helper.c
drm_file.o: $S/dev/pci/drm/drm_file.c
drm_flip_work.o: $S/dev/pci/drm/drm_flip_work.c
drm_format_helper.o: $S/dev/pci/drm/drm_format_helper.c
drm_fourcc.o: $S/dev/pci/drm/drm_fourcc.c
drm_framebuffer.o: $S/dev/pci/drm/drm_framebuffer.c
drm_gem.o: $S/dev/pci/drm/drm_gem.c
drm_gem_atomic_helper.o: $S/dev/pci/drm/drm_gem_atomic_helper.c
drm_gem_framebuffer_helper.o: $S/dev/pci/drm/drm_gem_framebuffer_helper.c
drm_hashtab.o: $S/dev/pci/drm/drm_hashtab.c
drm_ioctl.o: $S/dev/pci/drm/drm_ioctl.c
drm_kms_helper_common.o: $S/dev/pci/drm/drm_kms_helper_common.c
drm_linux.o: $S/dev/pci/drm/drm_linux.c
drm_managed.o: $S/dev/pci/drm/drm_managed.c
drm_memory.o: $S/dev/pci/drm/drm_memory.c
drm_mipi_dsi.o: $S/dev/pci/drm/drm_mipi_dsi.c
drm_mm.o: $S/dev/pci/drm/drm_mm.c
drm_mode_config.o: $S/dev/pci/drm/drm_mode_config.c
drm_mode_object.o: $S/dev/pci/drm/drm_mode_object.c
drm_modes.o: $S/dev/pci/drm/drm_modes.c
drm_modeset_helper.o: $S/dev/pci/drm/drm_modeset_helper.c
drm_modeset_lock.o: $S/dev/pci/drm/drm_modeset_lock.c
drm_mtrr.o: $S/dev/pci/drm/drm_mtrr.c
drm_panel.o: $S/dev/pci/drm/drm_panel.c
drm_panel_orientation_quirks.o: $S/dev/pci/drm/drm_panel_orientation_quirks.c
drm_pci.o: $S/dev/pci/drm/drm_pci.c
drm_plane.o: $S/dev/pci/drm/drm_plane.c
drm_plane_helper.o: $S/dev/pci/drm/drm_plane_helper.c
drm_prime.o: $S/dev/pci/drm/drm_prime.c
drm_print.o: $S/dev/pci/drm/drm_print.c
drm_probe_helper.o: $S/dev/pci/drm/drm_probe_helper.c
drm_property.o: $S/dev/pci/drm/drm_property.c
drm_rect.o: $S/dev/pci/drm/drm_rect.c
drm_self_refresh_helper.o: $S/dev/pci/drm/drm_self_refresh_helper.c
drm_syncobj.o: $S/dev/pci/drm/drm_syncobj.c
drm_trace_points.o: $S/dev/pci/drm/drm_trace_points.c
drm_vblank.o: $S/dev/pci/drm/drm_vblank.c
drm_vblank_work.o: $S/dev/pci/drm/drm_vblank_work.c
drm_vma_manager.o: $S/dev/pci/drm/drm_vma_manager.c
hdmi.o: $S/dev/pci/drm/hdmi.c
linux_list_sort.o: $S/dev/pci/drm/linux_list_sort.c
linux_radix.o: $S/dev/pci/drm/linux_radix.c
linux_sort.o: $S/dev/pci/drm/linux_sort.c
drm_dp_dual_mode_helper.o: $S/dev/pci/drm/display/drm_dp_dual_mode_helper.c
drm_dp_helper.o: $S/dev/pci/drm/display/drm_dp_helper.c
drm_dp_mst_topology.o: $S/dev/pci/drm/display/drm_dp_mst_topology.c
drm_dsc_helper.o: $S/dev/pci/drm/display/drm_dsc_helper.c
drm_hdcp_helper.o: $S/dev/pci/drm/display/drm_hdcp_helper.c
drm_hdmi_helper.o: $S/dev/pci/drm/display/drm_hdmi_helper.c
drm_scdc_helper.o: $S/dev/pci/drm/display/drm_scdc_helper.c
drm_gem_ttm_helper.o: $S/dev/pci/drm/drm_gem_ttm_helper.c
ttm_agp_backend.o: $S/dev/pci/drm/ttm/ttm_agp_backend.c
ttm_bo.o: $S/dev/pci/drm/ttm/ttm_bo.c
ttm_bo_util.o: $S/dev/pci/drm/ttm/ttm_bo_util.c
ttm_bo_vm.o: $S/dev/pci/drm/ttm/ttm_bo_vm.c
ttm_device.o: $S/dev/pci/drm/ttm/ttm_device.c
ttm_execbuf_util.o: $S/dev/pci/drm/ttm/ttm_execbuf_util.c
ttm_module.o: $S/dev/pci/drm/ttm/ttm_module.c
ttm_pool.o: $S/dev/pci/drm/ttm/ttm_pool.c
ttm_range_manager.o: $S/dev/pci/drm/ttm/ttm_range_manager.c
ttm_resource.o: $S/dev/pci/drm/ttm/ttm_resource.c
ttm_sys_manager.o: $S/dev/pci/drm/ttm/ttm_sys_manager.c
ttm_tt.o: $S/dev/pci/drm/ttm/ttm_tt.c
sched_entity.o: $S/dev/pci/drm/scheduler/sched_entity.c
sched_fence.o: $S/dev/pci/drm/scheduler/sched_fence.c
sched_main.o: $S/dev/pci/drm/scheduler/sched_main.c
dvo_ch7017.o: $S/dev/pci/drm/i915/display/dvo_ch7017.c
dvo_ch7xxx.o: $S/dev/pci/drm/i915/display/dvo_ch7xxx.c
dvo_ivch.o: $S/dev/pci/drm/i915/display/dvo_ivch.c
dvo_ns2501.o: $S/dev/pci/drm/i915/display/dvo_ns2501.c
dvo_sil164.o: $S/dev/pci/drm/i915/display/dvo_sil164.c
dvo_tfp410.o: $S/dev/pci/drm/i915/display/dvo_tfp410.c
g4x_dp.o: $S/dev/pci/drm/i915/display/g4x_dp.c
g4x_hdmi.o: $S/dev/pci/drm/i915/display/g4x_hdmi.c
hsw_ips.o: $S/dev/pci/drm/i915/display/hsw_ips.c
i9xx_plane.o: $S/dev/pci/drm/i915/display/i9xx_plane.c
icl_dsi.o: $S/dev/pci/drm/i915/display/icl_dsi.c
intel_atomic.o: $S/dev/pci/drm/i915/display/intel_atomic.c
intel_atomic_plane.o: $S/dev/pci/drm/i915/display/intel_atomic_plane.c
intel_audio.o: $S/dev/pci/drm/i915/display/intel_audio.c
intel_backlight.o: $S/dev/pci/drm/i915/display/intel_backlight.c
intel_bios.o: $S/dev/pci/drm/i915/display/intel_bios.c
intel_bw.o: $S/dev/pci/drm/i915/display/intel_bw.c
intel_cdclk.o: $S/dev/pci/drm/i915/display/intel_cdclk.c
intel_color.o: $S/dev/pci/drm/i915/display/intel_color.c
intel_combo_phy.o: $S/dev/pci/drm/i915/display/intel_combo_phy.c
intel_connector.o: $S/dev/pci/drm/i915/display/intel_connector.c
intel_crt.o: $S/dev/pci/drm/i915/display/intel_crt.c
intel_crtc.o: $S/dev/pci/drm/i915/display/intel_crtc.c
intel_crtc_state_dump.o: $S/dev/pci/drm/i915/display/intel_crtc_state_dump.c
intel_cursor.o: $S/dev/pci/drm/i915/display/intel_cursor.c
intel_ddi.o: $S/dev/pci/drm/i915/display/intel_ddi.c
intel_ddi_buf_trans.o: $S/dev/pci/drm/i915/display/intel_ddi_buf_trans.c
intel_display.o: $S/dev/pci/drm/i915/display/intel_display.c
intel_display_power.o: $S/dev/pci/drm/i915/display/intel_display_power.c
intel_display_power_map.o: $S/dev/pci/drm/i915/display/intel_display_power_map.c
intel_display_power_well.o: $S/dev/pci/drm/i915/display/intel_display_power_well.c
intel_dkl_phy.o: $S/dev/pci/drm/i915/display/intel_dkl_phy.c
intel_dmc.o: $S/dev/pci/drm/i915/display/intel_dmc.c
intel_dp.o: $S/dev/pci/drm/i915/display/intel_dp.c
intel_dp_aux.o: $S/dev/pci/drm/i915/display/intel_dp_aux.c
intel_dp_aux_backlight.o: $S/dev/pci/drm/i915/display/intel_dp_aux_backlight.c
intel_dp_hdcp.o: $S/dev/pci/drm/i915/display/intel_dp_hdcp.c
intel_dp_link_training.o: $S/dev/pci/drm/i915/display/intel_dp_link_training.c
intel_dp_mst.o: $S/dev/pci/drm/i915/display/intel_dp_mst.c
intel_dpio_phy.o: $S/dev/pci/drm/i915/display/intel_dpio_phy.c
intel_dpll.o: $S/dev/pci/drm/i915/display/intel_dpll.c
intel_dpll_mgr.o: $S/dev/pci/drm/i915/display/intel_dpll_mgr.c
intel_dpt.o: $S/dev/pci/drm/i915/display/intel_dpt.c
intel_drrs.o: $S/dev/pci/drm/i915/display/intel_drrs.c
intel_dsb.o: $S/dev/pci/drm/i915/display/intel_dsb.c
intel_dsi.o: $S/dev/pci/drm/i915/display/intel_dsi.c
intel_dsi_dcs_backlight.o: $S/dev/pci/drm/i915/display/intel_dsi_dcs_backlight.c
intel_dsi_vbt.o: $S/dev/pci/drm/i915/display/intel_dsi_vbt.c
intel_dvo.o: $S/dev/pci/drm/i915/display/intel_dvo.c
intel_fb.o: $S/dev/pci/drm/i915/display/intel_fb.c
intel_fb_pin.o: $S/dev/pci/drm/i915/display/intel_fb_pin.c
intel_fbc.o: $S/dev/pci/drm/i915/display/intel_fbc.c
intel_fbdev.o: $S/dev/pci/drm/i915/display/intel_fbdev.c
intel_fdi.o: $S/dev/pci/drm/i915/display/intel_fdi.c
intel_fifo_underrun.o: $S/dev/pci/drm/i915/display/intel_fifo_underrun.c
intel_frontbuffer.o: $S/dev/pci/drm/i915/display/intel_frontbuffer.c
intel_global_state.o: $S/dev/pci/drm/i915/display/intel_global_state.c
intel_gmbus.o: $S/dev/pci/drm/i915/display/intel_gmbus.c
intel_hdcp.o: $S/dev/pci/drm/i915/display/intel_hdcp.c
intel_hdmi.o: $S/dev/pci/drm/i915/display/intel_hdmi.c
intel_hotplug.o: $S/dev/pci/drm/i915/display/intel_hotplug.c
intel_lpe_audio.o: $S/dev/pci/drm/i915/display/intel_lpe_audio.c
intel_lspcon.o: $S/dev/pci/drm/i915/display/intel_lspcon.c
intel_lvds.o: $S/dev/pci/drm/i915/display/intel_lvds.c
intel_modeset_setup.o: $S/dev/pci/drm/i915/display/intel_modeset_setup.c
intel_modeset_verify.o: $S/dev/pci/drm/i915/display/intel_modeset_verify.c
intel_opregion.o: $S/dev/pci/drm/i915/display/intel_opregion.c
intel_overlay.o: $S/dev/pci/drm/i915/display/intel_overlay.c
intel_panel.o: $S/dev/pci/drm/i915/display/intel_panel.c
intel_pch_display.o: $S/dev/pci/drm/i915/display/intel_pch_display.c
intel_pch_refclk.o: $S/dev/pci/drm/i915/display/intel_pch_refclk.c
intel_plane_initial.o: $S/dev/pci/drm/i915/display/intel_plane_initial.c
intel_pps.o: $S/dev/pci/drm/i915/display/intel_pps.c
intel_psr.o: $S/dev/pci/drm/i915/display/intel_psr.c
intel_qp_tables.o: $S/dev/pci/drm/i915/display/intel_qp_tables.c
intel_quirks.o: $S/dev/pci/drm/i915/display/intel_quirks.c
intel_sdvo.o: $S/dev/pci/drm/i915/display/intel_sdvo.c
intel_snps_phy.o: $S/dev/pci/drm/i915/display/intel_snps_phy.c
intel_sprite.o: $S/dev/pci/drm/i915/display/intel_sprite.c
intel_tc.o: $S/dev/pci/drm/i915/display/intel_tc.c
intel_tv.o: $S/dev/pci/drm/i915/display/intel_tv.c
intel_vdsc.o: $S/dev/pci/drm/i915/display/intel_vdsc.c
intel_vga.o: $S/dev/pci/drm/i915/display/intel_vga.c
intel_vrr.o: $S/dev/pci/drm/i915/display/intel_vrr.c
skl_scaler.o: $S/dev/pci/drm/i915/display/skl_scaler.c
skl_universal_plane.o: $S/dev/pci/drm/i915/display/skl_universal_plane.c
skl_watermark.o: $S/dev/pci/drm/i915/display/skl_watermark.c
vlv_dsi.o: $S/dev/pci/drm/i915/display/vlv_dsi.c
vlv_dsi_pll.o: $S/dev/pci/drm/i915/display/vlv_dsi_pll.c
i915_gem_busy.o: $S/dev/pci/drm/i915/gem/i915_gem_busy.c
i915_gem_clflush.o: $S/dev/pci/drm/i915/gem/i915_gem_clflush.c
i915_gem_context.o: $S/dev/pci/drm/i915/gem/i915_gem_context.c
i915_gem_create.o: $S/dev/pci/drm/i915/gem/i915_gem_create.c
i915_gem_dmabuf.o: $S/dev/pci/drm/i915/gem/i915_gem_dmabuf.c
i915_gem_domain.o: $S/dev/pci/drm/i915/gem/i915_gem_domain.c
i915_gem_execbuffer.o: $S/dev/pci/drm/i915/gem/i915_gem_execbuffer.c
i915_gem_internal.o: $S/dev/pci/drm/i915/gem/i915_gem_internal.c
i915_gem_lmem.o: $S/dev/pci/drm/i915/gem/i915_gem_lmem.c
i915_gem_mman.o: $S/dev/pci/drm/i915/gem/i915_gem_mman.c
i915_gem_object.o: $S/dev/pci/drm/i915/gem/i915_gem_object.c
i915_gem_pages.o: $S/dev/pci/drm/i915/gem/i915_gem_pages.c
i915_gem_phys.o: $S/dev/pci/drm/i915/gem/i915_gem_phys.c
i915_gem_pm.o: $S/dev/pci/drm/i915/gem/i915_gem_pm.c
i915_gem_region.o: $S/dev/pci/drm/i915/gem/i915_gem_region.c
i915_gem_shmem.o: $S/dev/pci/drm/i915/gem/i915_gem_shmem.c
i915_gem_shrinker.o: $S/dev/pci/drm/i915/gem/i915_gem_shrinker.c
i915_gem_stolen.o: $S/dev/pci/drm/i915/gem/i915_gem_stolen.c
i915_gem_throttle.o: $S/dev/pci/drm/i915/gem/i915_gem_throttle.c
i915_gem_tiling.o: $S/dev/pci/drm/i915/gem/i915_gem_tiling.c
i915_gem_ttm.o: $S/dev/pci/drm/i915/gem/i915_gem_ttm.c
i915_gem_ttm_move.o: $S/dev/pci/drm/i915/gem/i915_gem_ttm_move.c
i915_gem_ttm_pm.o: $S/dev/pci/drm/i915/gem/i915_gem_ttm_pm.c
i915_gem_userptr.o: $S/dev/pci/drm/i915/gem/i915_gem_userptr.c
i915_gem_wait.o: $S/dev/pci/drm/i915/gem/i915_gem_wait.c
i915_gemfs.o: $S/dev/pci/drm/i915/gem/i915_gemfs.c
agp_intel_gtt.o: $S/dev/pci/drm/i915/gt/agp_intel_gtt.c
gen2_engine_cs.o: $S/dev/pci/drm/i915/gt/gen2_engine_cs.c
gen6_engine_cs.o: $S/dev/pci/drm/i915/gt/gen6_engine_cs.c
gen6_ppgtt.o: $S/dev/pci/drm/i915/gt/gen6_ppgtt.c
gen6_renderstate.o: $S/dev/pci/drm/i915/gt/gen6_renderstate.c
gen7_renderclear.o: $S/dev/pci/drm/i915/gt/gen7_renderclear.c
gen7_renderstate.o: $S/dev/pci/drm/i915/gt/gen7_renderstate.c
gen8_engine_cs.o: $S/dev/pci/drm/i915/gt/gen8_engine_cs.c
gen8_ppgtt.o: $S/dev/pci/drm/i915/gt/gen8_ppgtt.c
gen8_renderstate.o: $S/dev/pci/drm/i915/gt/gen8_renderstate.c
gen9_renderstate.o: $S/dev/pci/drm/i915/gt/gen9_renderstate.c
intel_breadcrumbs.o: $S/dev/pci/drm/i915/gt/intel_breadcrumbs.c
intel_context.o: $S/dev/pci/drm/i915/gt/intel_context.c
intel_context_sseu.o: $S/dev/pci/drm/i915/gt/intel_context_sseu.c
intel_engine_cs.o: $S/dev/pci/drm/i915/gt/intel_engine_cs.c
intel_engine_heartbeat.o: $S/dev/pci/drm/i915/gt/intel_engine_heartbeat.c
intel_engine_pm.o: $S/dev/pci/drm/i915/gt/intel_engine_pm.c
intel_engine_user.o: $S/dev/pci/drm/i915/gt/intel_engine_user.c
intel_execlists_submission.o: $S/dev/pci/drm/i915/gt/intel_execlists_submission.c
intel_ggtt.o: $S/dev/pci/drm/i915/gt/intel_ggtt.c
intel_ggtt_fencing.o: $S/dev/pci/drm/i915/gt/intel_ggtt_fencing.c
intel_ggtt_gmch.o: $S/dev/pci/drm/i915/gt/intel_ggtt_gmch.c
intel_gsc.o: $S/dev/pci/drm/i915/gt/intel_gsc.c
intel_gt.o: $S/dev/pci/drm/i915/gt/intel_gt.c
intel_gt_buffer_pool.o: $S/dev/pci/drm/i915/gt/intel_gt_buffer_pool.c
intel_gt_clock_utils.o: $S/dev/pci/drm/i915/gt/intel_gt_clock_utils.c
intel_gt_debugfs.o: $S/dev/pci/drm/i915/gt/intel_gt_debugfs.c
intel_gt_engines_debugfs.o: $S/dev/pci/drm/i915/gt/intel_gt_engines_debugfs.c
intel_gt_irq.o: $S/dev/pci/drm/i915/gt/intel_gt_irq.c
intel_gt_mcr.o: $S/dev/pci/drm/i915/gt/intel_gt_mcr.c
intel_gt_pm.o: $S/dev/pci/drm/i915/gt/intel_gt_pm.c
intel_gt_pm_debugfs.o: $S/dev/pci/drm/i915/gt/intel_gt_pm_debugfs.c
intel_gt_pm_irq.o: $S/dev/pci/drm/i915/gt/intel_gt_pm_irq.c
intel_gt_requests.o: $S/dev/pci/drm/i915/gt/intel_gt_requests.c
intel_gt_sysfs.o: $S/dev/pci/drm/i915/gt/intel_gt_sysfs.c
intel_gt_sysfs_pm.o: $S/dev/pci/drm/i915/gt/intel_gt_sysfs_pm.c
intel_gtt.o: $S/dev/pci/drm/i915/gt/intel_gtt.c
intel_llc.o: $S/dev/pci/drm/i915/gt/intel_llc.c
intel_lrc.o: $S/dev/pci/drm/i915/gt/intel_lrc.c
intel_migrate.o: $S/dev/pci/drm/i915/gt/intel_migrate.c
intel_mocs.o: $S/dev/pci/drm/i915/gt/intel_mocs.c
intel_ppgtt.o: $S/dev/pci/drm/i915/gt/intel_ppgtt.c
intel_rc6.o: $S/dev/pci/drm/i915/gt/intel_rc6.c
intel_region_lmem.o: $S/dev/pci/drm/i915/gt/intel_region_lmem.c
intel_renderstate.o: $S/dev/pci/drm/i915/gt/intel_renderstate.c
intel_reset.o: $S/dev/pci/drm/i915/gt/intel_reset.c
intel_ring.o: $S/dev/pci/drm/i915/gt/intel_ring.c
intel_ring_submission.o: $S/dev/pci/drm/i915/gt/intel_ring_submission.c
intel_rps.o: $S/dev/pci/drm/i915/gt/intel_rps.c
intel_sa_media.o: $S/dev/pci/drm/i915/gt/intel_sa_media.c
intel_sseu.o: $S/dev/pci/drm/i915/gt/intel_sseu.c
intel_sseu_debugfs.o: $S/dev/pci/drm/i915/gt/intel_sseu_debugfs.c
intel_timeline.o: $S/dev/pci/drm/i915/gt/intel_timeline.c
intel_workarounds.o: $S/dev/pci/drm/i915/gt/intel_workarounds.c
shmem_utils.o: $S/dev/pci/drm/i915/gt/shmem_utils.c
sysfs_engines.o: $S/dev/pci/drm/i915/gt/sysfs_engines.c
intel_guc.o: $S/dev/pci/drm/i915/gt/uc/intel_guc.c
intel_guc_ads.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_ads.c
intel_guc_capture.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_capture.c
intel_guc_ct.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_ct.c
intel_guc_debugfs.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_debugfs.c
intel_guc_fw.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_fw.c
intel_guc_hwconfig.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_hwconfig.c
intel_guc_log.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_log.c
intel_guc_log_debugfs.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_log_debugfs.c
intel_guc_rc.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_rc.c
intel_guc_slpc.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_slpc.c
intel_guc_submission.o: $S/dev/pci/drm/i915/gt/uc/intel_guc_submission.c
intel_huc.o: $S/dev/pci/drm/i915/gt/uc/intel_huc.c
intel_huc_debugfs.o: $S/dev/pci/drm/i915/gt/uc/intel_huc_debugfs.c
intel_huc_fw.o: $S/dev/pci/drm/i915/gt/uc/intel_huc_fw.c
intel_uc.o: $S/dev/pci/drm/i915/gt/uc/intel_uc.c
intel_uc_debugfs.o: $S/dev/pci/drm/i915/gt/uc/intel_uc_debugfs.c
intel_uc_fw.o: $S/dev/pci/drm/i915/gt/uc/intel_uc_fw.c
i915_active.o: $S/dev/pci/drm/i915/i915_active.c
i915_cmd_parser.o: $S/dev/pci/drm/i915/i915_cmd_parser.c
i915_config.o: $S/dev/pci/drm/i915/i915_config.c
i915_deps.o: $S/dev/pci/drm/i915/i915_deps.c
i915_driver.o: $S/dev/pci/drm/i915/i915_driver.c
i915_drm_client.o: $S/dev/pci/drm/i915/i915_drm_client.c
i915_gem.o: $S/dev/pci/drm/i915/i915_gem.c
i915_gem_evict.o: $S/dev/pci/drm/i915/i915_gem_evict.c
i915_gem_gtt.o: $S/dev/pci/drm/i915/i915_gem_gtt.c
i915_gem_ww.o: $S/dev/pci/drm/i915/i915_gem_ww.c
i915_getparam.o: $S/dev/pci/drm/i915/i915_getparam.c
i915_gpu_error.o: $S/dev/pci/drm/i915/i915_gpu_error.c
i915_ioctl.o: $S/dev/pci/drm/i915/i915_ioctl.c
i915_irq.o: $S/dev/pci/drm/i915/i915_irq.c
i915_memcpy.o: $S/dev/pci/drm/i915/i915_memcpy.c
i915_mitigations.o: $S/dev/pci/drm/i915/i915_mitigations.c
i915_mm.o: $S/dev/pci/drm/i915/i915_mm.c
i915_module.o: $S/dev/pci/drm/i915/i915_module.c
i915_params.o: $S/dev/pci/drm/i915/i915_params.c
i915_pci.o: $S/dev/pci/drm/i915/i915_pci.c
i915_perf.o: $S/dev/pci/drm/i915/i915_perf.c
i915_query.o: $S/dev/pci/drm/i915/i915_query.c
i915_request.o: $S/dev/pci/drm/i915/i915_request.c
i915_scatterlist.o: $S/dev/pci/drm/i915/i915_scatterlist.c
i915_scheduler.o: $S/dev/pci/drm/i915/i915_scheduler.c
i915_suspend.o: $S/dev/pci/drm/i915/i915_suspend.c
i915_sw_fence.o: $S/dev/pci/drm/i915/i915_sw_fence.c
i915_sw_fence_work.o: $S/dev/pci/drm/i915/i915_sw_fence_work.c
i915_switcheroo.o: $S/dev/pci/drm/i915/i915_switcheroo.c
i915_syncmap.o: $S/dev/pci/drm/i915/i915_syncmap.c
i915_sysfs.o: $S/dev/pci/drm/i915/i915_sysfs.c
i915_ttm_buddy_manager.o: $S/dev/pci/drm/i915/i915_ttm_buddy_manager.c
i915_user_extensions.o: $S/dev/pci/drm/i915/i915_user_extensions.c
i915_utils.o: $S/dev/pci/drm/i915/i915_utils.c
i915_vgpu.o: $S/dev/pci/drm/i915/i915_vgpu.c
i915_vma.o: $S/dev/pci/drm/i915/i915_vma.c
i915_vma_resource.o: $S/dev/pci/drm/i915/i915_vma_resource.c
intel_device_info.o: $S/dev/pci/drm/i915/intel_device_info.c
intel_dram.o: $S/dev/pci/drm/i915/intel_dram.c
intel_memory_region.o: $S/dev/pci/drm/i915/intel_memory_region.c
intel_pch.o: $S/dev/pci/drm/i915/intel_pch.c
intel_pcode.o: $S/dev/pci/drm/i915/intel_pcode.c
intel_pm.o: $S/dev/pci/drm/i915/intel_pm.c
intel_region_ttm.o: $S/dev/pci/drm/i915/intel_region_ttm.c
intel_runtime_pm.o: $S/dev/pci/drm/i915/intel_runtime_pm.c
intel_sbi.o: $S/dev/pci/drm/i915/intel_sbi.c
intel_step.o: $S/dev/pci/drm/i915/intel_step.c
intel_stolen.o: $S/dev/pci/drm/i915/intel_stolen.c
intel_uncore.o: $S/dev/pci/drm/i915/intel_uncore.c
intel_wakeref.o: $S/dev/pci/drm/i915/intel_wakeref.c
intel_wopcm.o: $S/dev/pci/drm/i915/intel_wopcm.c
vlv_sideband.o: $S/dev/pci/drm/i915/vlv_sideband.c
vlv_suspend.o: $S/dev/pci/drm/i915/vlv_suspend.c
atom.o: $S/dev/pci/drm/radeon/atom.c
atombios_crtc.o: $S/dev/pci/drm/radeon/atombios_crtc.c
atombios_dp.o: $S/dev/pci/drm/radeon/atombios_dp.c
atombios_encoders.o: $S/dev/pci/drm/radeon/atombios_encoders.c
atombios_i2c.o: $S/dev/pci/drm/radeon/atombios_i2c.c
btc_dpm.o: $S/dev/pci/drm/radeon/btc_dpm.c
ci_dpm.o: $S/dev/pci/drm/radeon/ci_dpm.c
ci_smc.o: $S/dev/pci/drm/radeon/ci_smc.c
cik.o: $S/dev/pci/drm/radeon/cik.c
cik_sdma.o: $S/dev/pci/drm/radeon/cik_sdma.c
cypress_dpm.o: $S/dev/pci/drm/radeon/cypress_dpm.c
dce3_1_afmt.o: $S/dev/pci/drm/radeon/dce3_1_afmt.c
dce6_afmt.o: $S/dev/pci/drm/radeon/dce6_afmt.c
evergreen.o: $S/dev/pci/drm/radeon/evergreen.c
evergreen_cs.o: $S/dev/pci/drm/radeon/evergreen_cs.c
evergreen_dma.o: $S/dev/pci/drm/radeon/evergreen_dma.c
evergreen_hdmi.o: $S/dev/pci/drm/radeon/evergreen_hdmi.c
kv_dpm.o: $S/dev/pci/drm/radeon/kv_dpm.c
kv_smc.o: $S/dev/pci/drm/radeon/kv_smc.c
ni.o: $S/dev/pci/drm/radeon/ni.c
ni_dma.o: $S/dev/pci/drm/radeon/ni_dma.c
ni_dpm.o: $S/dev/pci/drm/radeon/ni_dpm.c
r100.o: $S/dev/pci/drm/radeon/r100.c
r200.o: $S/dev/pci/drm/radeon/r200.c
r300.o: $S/dev/pci/drm/radeon/r300.c
r420.o: $S/dev/pci/drm/radeon/r420.c
r520.o: $S/dev/pci/drm/radeon/r520.c
r600.o: $S/dev/pci/drm/radeon/r600.c
r600_cs.o: $S/dev/pci/drm/radeon/r600_cs.c
r600_dma.o: $S/dev/pci/drm/radeon/r600_dma.c
r600_dpm.o: $S/dev/pci/drm/radeon/r600_dpm.c
r600_hdmi.o: $S/dev/pci/drm/radeon/r600_hdmi.c
radeon_acpi.o: $S/dev/pci/drm/radeon/radeon_acpi.c
radeon_agp.o: $S/dev/pci/drm/radeon/radeon_agp.c
radeon_asic.o: $S/dev/pci/drm/radeon/radeon_asic.c
radeon_atombios.o: $S/dev/pci/drm/radeon/radeon_atombios.c
radeon_audio.o: $S/dev/pci/drm/radeon/radeon_audio.c
radeon_benchmark.o: $S/dev/pci/drm/radeon/radeon_benchmark.c
radeon_bios.o: $S/dev/pci/drm/radeon/radeon_bios.c
radeon_clocks.o: $S/dev/pci/drm/radeon/radeon_clocks.c
radeon_combios.o: $S/dev/pci/drm/radeon/radeon_combios.c
radeon_connectors.o: $S/dev/pci/drm/radeon/radeon_connectors.c
radeon_cs.o: $S/dev/pci/drm/radeon/radeon_cs.c
radeon_cursor.o: $S/dev/pci/drm/radeon/radeon_cursor.c
radeon_device.o: $S/dev/pci/drm/radeon/radeon_device.c
radeon_display.o: $S/dev/pci/drm/radeon/radeon_display.c
radeon_dp_auxch.o: $S/dev/pci/drm/radeon/radeon_dp_auxch.c
radeon_drv.o: $S/dev/pci/drm/radeon/radeon_drv.c
radeon_encoders.o: $S/dev/pci/drm/radeon/radeon_encoders.c
radeon_fb.o: $S/dev/pci/drm/radeon/radeon_fb.c
radeon_fence.o: $S/dev/pci/drm/radeon/radeon_fence.c
radeon_gart.o: $S/dev/pci/drm/radeon/radeon_gart.c
radeon_gem.o: $S/dev/pci/drm/radeon/radeon_gem.c
radeon_i2c.o: $S/dev/pci/drm/radeon/radeon_i2c.c
radeon_ib.o: $S/dev/pci/drm/radeon/radeon_ib.c
radeon_irq_kms.o: $S/dev/pci/drm/radeon/radeon_irq_kms.c
radeon_kms.o: $S/dev/pci/drm/radeon/radeon_kms.c
radeon_legacy_crtc.o: $S/dev/pci/drm/radeon/radeon_legacy_crtc.c
radeon_legacy_encoders.o: $S/dev/pci/drm/radeon/radeon_legacy_encoders.c
radeon_legacy_tv.o: $S/dev/pci/drm/radeon/radeon_legacy_tv.c
radeon_object.o: $S/dev/pci/drm/radeon/radeon_object.c
radeon_pm.o: $S/dev/pci/drm/radeon/radeon_pm.c
radeon_prime.o: $S/dev/pci/drm/radeon/radeon_prime.c
radeon_ring.o: $S/dev/pci/drm/radeon/radeon_ring.c
radeon_sa.o: $S/dev/pci/drm/radeon/radeon_sa.c
radeon_semaphore.o: $S/dev/pci/drm/radeon/radeon_semaphore.c
radeon_sync.o: $S/dev/pci/drm/radeon/radeon_sync.c
radeon_test.o: $S/dev/pci/drm/radeon/radeon_test.c
radeon_ttm.o: $S/dev/pci/drm/radeon/radeon_ttm.c
radeon_ucode.o: $S/dev/pci/drm/radeon/radeon_ucode.c
radeon_uvd.o: $S/dev/pci/drm/radeon/radeon_uvd.c
radeon_vce.o: $S/dev/pci/drm/radeon/radeon_vce.c
radeon_vm.o: $S/dev/pci/drm/radeon/radeon_vm.c
rs400.o: $S/dev/pci/drm/radeon/rs400.c
rs600.o: $S/dev/pci/drm/radeon/rs600.c
rs690.o: $S/dev/pci/drm/radeon/rs690.c
rs780_dpm.o: $S/dev/pci/drm/radeon/rs780_dpm.c
rv515.o: $S/dev/pci/drm/radeon/rv515.c
rv6xx_dpm.o: $S/dev/pci/drm/radeon/rv6xx_dpm.c
rv730_dpm.o: $S/dev/pci/drm/radeon/rv730_dpm.c
rv740_dpm.o: $S/dev/pci/drm/radeon/rv740_dpm.c
rv770.o: $S/dev/pci/drm/radeon/rv770.c
rv770_dma.o: $S/dev/pci/drm/radeon/rv770_dma.c
rv770_dpm.o: $S/dev/pci/drm/radeon/rv770_dpm.c
rv770_smc.o: $S/dev/pci/drm/radeon/rv770_smc.c
si.o: $S/dev/pci/drm/radeon/si.c
si_dma.o: $S/dev/pci/drm/radeon/si_dma.c
si_dpm.o: $S/dev/pci/drm/radeon/si_dpm.c
si_smc.o: $S/dev/pci/drm/radeon/si_smc.c
sumo_dpm.o: $S/dev/pci/drm/radeon/sumo_dpm.c
sumo_smc.o: $S/dev/pci/drm/radeon/sumo_smc.c
trinity_dpm.o: $S/dev/pci/drm/radeon/trinity_dpm.c
trinity_smc.o: $S/dev/pci/drm/radeon/trinity_smc.c
uvd_v1_0.o: $S/dev/pci/drm/radeon/uvd_v1_0.c
uvd_v2_2.o: $S/dev/pci/drm/radeon/uvd_v2_2.c
uvd_v3_1.o: $S/dev/pci/drm/radeon/uvd_v3_1.c
uvd_v4_2.o: $S/dev/pci/drm/radeon/uvd_v4_2.c
vce_v1_0.o: $S/dev/pci/drm/radeon/vce_v1_0.c
vce_v2_0.o: $S/dev/pci/drm/radeon/vce_v2_0.c
aldebaran.o: $S/dev/pci/drm/amd/amdgpu/aldebaran.c
aldebaran_reg_init.o: $S/dev/pci/drm/amd/amdgpu/aldebaran_reg_init.c
amdgpu_acpi.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_acpi.c
amdgpu_afmt.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_afmt.c
amdgpu_amdkfd.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_amdkfd.c
amdgpu_atom.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atom.c
amdgpu_atombios.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atombios.c
amdgpu_atombios_crtc.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_crtc.c
amdgpu_atombios_dp.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_dp.c
amdgpu_atombios_encoders.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_encoders.c
amdgpu_atombios_i2c.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atombios_i2c.c
amdgpu_atomfirmware.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_atomfirmware.c
amdgpu_benchmark.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_benchmark.c
amdgpu_bios.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_bios.c
amdgpu_bo_list.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_bo_list.c
amdgpu_cgs.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_cgs.c
amdgpu_connectors.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_connectors.c
amdgpu_cs.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_cs.c
amdgpu_csa.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_csa.c
amdgpu_ctx.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ctx.c
amdgpu_debugfs.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_debugfs.c
amdgpu_device.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_device.c
amdgpu_discovery.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_discovery.c
amdgpu_display.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_display.c
amdgpu_dma_buf.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_dma_buf.c
amdgpu_drv.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_drv.c
amdgpu_eeprom.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_eeprom.c
amdgpu_encoders.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_encoders.c
amdgpu_fdinfo.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_fdinfo.c
amdgpu_fence.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_fence.c
amdgpu_fru_eeprom.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_fru_eeprom.c
amdgpu_fw_attestation.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_fw_attestation.c
amdgpu_gart.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_gart.c
amdgpu_gem.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_gem.c
amdgpu_gfx.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_gfx.c
amdgpu_gmc.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_gmc.c
amdgpu_gtt_mgr.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_gtt_mgr.c
amdgpu_i2c.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_i2c.c
amdgpu_ib.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ib.c
amdgpu_ids.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ids.c
amdgpu_ih.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ih.c
amdgpu_irq.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_irq.c
amdgpu_job.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_job.c
amdgpu_jpeg.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_jpeg.c
amdgpu_kms.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_kms.c
amdgpu_lsdma.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_lsdma.c
amdgpu_mca.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_mca.c
amdgpu_mes.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_mes.c
amdgpu_nbio.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_nbio.c
amdgpu_object.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_object.c
amdgpu_pll.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_pll.c
amdgpu_preempt_mgr.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_preempt_mgr.c
amdgpu_psp.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_psp.c
amdgpu_psp_ta.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_psp_ta.c
amdgpu_rap.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_rap.c
amdgpu_ras.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ras.c
amdgpu_ras_eeprom.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ras_eeprom.c
amdgpu_reset.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_reset.c
amdgpu_ring.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ring.c
amdgpu_rlc.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_rlc.c
amdgpu_sa.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_sa.c
amdgpu_sched.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_sched.c
amdgpu_sdma.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_sdma.c
amdgpu_securedisplay.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_securedisplay.c
amdgpu_sync.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_sync.c
amdgpu_trace_points.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_trace_points.c
amdgpu_ttm.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ttm.c
amdgpu_ucode.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_ucode.c
amdgpu_umc.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_umc.c
amdgpu_uvd.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_uvd.c
amdgpu_vce.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vce.c
amdgpu_vcn.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vcn.c
amdgpu_vf_error.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vf_error.c
amdgpu_virt.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_virt.c
amdgpu_vkms.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vkms.c
amdgpu_vm.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vm.c
amdgpu_vm_cpu.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vm_cpu.c
amdgpu_vm_pt.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vm_pt.c
amdgpu_vm_sdma.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vm_sdma.c
amdgpu_vram_mgr.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_vram_mgr.c
amdgpu_xgmi.o: $S/dev/pci/drm/amd/amdgpu/amdgpu_xgmi.c
arct_reg_init.o: $S/dev/pci/drm/amd/amdgpu/arct_reg_init.c
athub_v1_0.o: $S/dev/pci/drm/amd/amdgpu/athub_v1_0.c
athub_v2_0.o: $S/dev/pci/drm/amd/amdgpu/athub_v2_0.c
athub_v2_1.o: $S/dev/pci/drm/amd/amdgpu/athub_v2_1.c
athub_v3_0.o: $S/dev/pci/drm/amd/amdgpu/athub_v3_0.c
cz_ih.o: $S/dev/pci/drm/amd/amdgpu/cz_ih.c
dce_v10_0.o: $S/dev/pci/drm/amd/amdgpu/dce_v10_0.c
dce_v11_0.o: $S/dev/pci/drm/amd/amdgpu/dce_v11_0.c
df_v1_7.o: $S/dev/pci/drm/amd/amdgpu/df_v1_7.c
df_v3_6.o: $S/dev/pci/drm/amd/amdgpu/df_v3_6.c
dimgrey_cavefish_reg_init.o: $S/dev/pci/drm/amd/amdgpu/dimgrey_cavefish_reg_init.c
emu_soc.o: $S/dev/pci/drm/amd/amdgpu/emu_soc.c
gfx_v10_0.o: $S/dev/pci/drm/amd/amdgpu/gfx_v10_0.c
gfx_v11_0.o: $S/dev/pci/drm/amd/amdgpu/gfx_v11_0.c
gfx_v8_0.o: $S/dev/pci/drm/amd/amdgpu/gfx_v8_0.c
gfx_v9_0.o: $S/dev/pci/drm/amd/amdgpu/gfx_v9_0.c
gfx_v9_4.o: $S/dev/pci/drm/amd/amdgpu/gfx_v9_4.c
gfx_v9_4_2.o: $S/dev/pci/drm/amd/amdgpu/gfx_v9_4_2.c
gfxhub_v1_0.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v1_0.c
gfxhub_v1_1.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v1_1.c
gfxhub_v2_0.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v2_0.c
gfxhub_v2_1.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v2_1.c
gfxhub_v3_0.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v3_0.c
gfxhub_v3_0_3.o: $S/dev/pci/drm/amd/amdgpu/gfxhub_v3_0_3.c
gmc_v10_0.o: $S/dev/pci/drm/amd/amdgpu/gmc_v10_0.c
gmc_v11_0.o: $S/dev/pci/drm/amd/amdgpu/gmc_v11_0.c
gmc_v7_0.o: $S/dev/pci/drm/amd/amdgpu/gmc_v7_0.c
gmc_v8_0.o: $S/dev/pci/drm/amd/amdgpu/gmc_v8_0.c
gmc_v9_0.o: $S/dev/pci/drm/amd/amdgpu/gmc_v9_0.c
hdp_v4_0.o: $S/dev/pci/drm/amd/amdgpu/hdp_v4_0.c
hdp_v5_0.o: $S/dev/pci/drm/amd/amdgpu/hdp_v5_0.c
hdp_v5_2.o: $S/dev/pci/drm/amd/amdgpu/hdp_v5_2.c
hdp_v6_0.o: $S/dev/pci/drm/amd/amdgpu/hdp_v6_0.c
iceland_ih.o: $S/dev/pci/drm/amd/amdgpu/iceland_ih.c
ih_v6_0.o: $S/dev/pci/drm/amd/amdgpu/ih_v6_0.c
imu_v11_0.o: $S/dev/pci/drm/amd/amdgpu/imu_v11_0.c
imu_v11_0_3.o: $S/dev/pci/drm/amd/amdgpu/imu_v11_0_3.c
jpeg_v1_0.o: $S/dev/pci/drm/amd/amdgpu/jpeg_v1_0.c
jpeg_v2_0.o: $S/dev/pci/drm/amd/amdgpu/jpeg_v2_0.c
jpeg_v2_5.o: $S/dev/pci/drm/amd/amdgpu/jpeg_v2_5.c
jpeg_v3_0.o: $S/dev/pci/drm/amd/amdgpu/jpeg_v3_0.c
jpeg_v4_0.o: $S/dev/pci/drm/amd/amdgpu/jpeg_v4_0.c
lsdma_v6_0.o: $S/dev/pci/drm/amd/amdgpu/lsdma_v6_0.c
mca_v3_0.o: $S/dev/pci/drm/amd/amdgpu/mca_v3_0.c
mes_v10_1.o: $S/dev/pci/drm/amd/amdgpu/mes_v10_1.c
mes_v11_0.o: $S/dev/pci/drm/amd/amdgpu/mes_v11_0.c
mmhub_v1_0.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v1_0.c
mmhub_v1_7.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v1_7.c
mmhub_v2_0.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v2_0.c
mmhub_v2_3.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v2_3.c
mmhub_v3_0.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v3_0.c
mmhub_v3_0_1.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v3_0_1.c
mmhub_v3_0_2.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v3_0_2.c
mmhub_v9_4.o: $S/dev/pci/drm/amd/amdgpu/mmhub_v9_4.c
mxgpu_ai.o: $S/dev/pci/drm/amd/amdgpu/mxgpu_ai.c
mxgpu_nv.o: $S/dev/pci/drm/amd/amdgpu/mxgpu_nv.c
mxgpu_vi.o: $S/dev/pci/drm/amd/amdgpu/mxgpu_vi.c
navi10_ih.o: $S/dev/pci/drm/amd/amdgpu/navi10_ih.c
nbio_v2_3.o: $S/dev/pci/drm/amd/amdgpu/nbio_v2_3.c
nbio_v4_3.o: $S/dev/pci/drm/amd/amdgpu/nbio_v4_3.c
nbio_v6_1.o: $S/dev/pci/drm/amd/amdgpu/nbio_v6_1.c
nbio_v7_0.o: $S/dev/pci/drm/amd/amdgpu/nbio_v7_0.c
nbio_v7_2.o: $S/dev/pci/drm/amd/amdgpu/nbio_v7_2.c
nbio_v7_4.o: $S/dev/pci/drm/amd/amdgpu/nbio_v7_4.c
nbio_v7_7.o: $S/dev/pci/drm/amd/amdgpu/nbio_v7_7.c
nv.o: $S/dev/pci/drm/amd/amdgpu/nv.c
psp_v10_0.o: $S/dev/pci/drm/amd/amdgpu/psp_v10_0.c
psp_v11_0.o: $S/dev/pci/drm/amd/amdgpu/psp_v11_0.c
psp_v11_0_8.o: $S/dev/pci/drm/amd/amdgpu/psp_v11_0_8.c
psp_v12_0.o: $S/dev/pci/drm/amd/amdgpu/psp_v12_0.c
psp_v13_0.o: $S/dev/pci/drm/amd/amdgpu/psp_v13_0.c
psp_v13_0_4.o: $S/dev/pci/drm/amd/amdgpu/psp_v13_0_4.c
psp_v3_1.o: $S/dev/pci/drm/amd/amdgpu/psp_v3_1.c
sdma_v2_4.o: $S/dev/pci/drm/amd/amdgpu/sdma_v2_4.c
sdma_v3_0.o: $S/dev/pci/drm/amd/amdgpu/sdma_v3_0.c
sdma_v4_0.o: $S/dev/pci/drm/amd/amdgpu/sdma_v4_0.c
sdma_v4_4.o: $S/dev/pci/drm/amd/amdgpu/sdma_v4_4.c
sdma_v5_0.o: $S/dev/pci/drm/amd/amdgpu/sdma_v5_0.c
sdma_v5_2.o: $S/dev/pci/drm/amd/amdgpu/sdma_v5_2.c
sdma_v6_0.o: $S/dev/pci/drm/amd/amdgpu/sdma_v6_0.c
sienna_cichlid.o: $S/dev/pci/drm/amd/amdgpu/sienna_cichlid.c
smu_v11_0_i2c.o: $S/dev/pci/drm/amd/amdgpu/smu_v11_0_i2c.c
smuio_v11_0.o: $S/dev/pci/drm/amd/amdgpu/smuio_v11_0.c
smuio_v11_0_6.o: $S/dev/pci/drm/amd/amdgpu/smuio_v11_0_6.c
smuio_v13_0.o: $S/dev/pci/drm/amd/amdgpu/smuio_v13_0.c
smuio_v13_0_6.o: $S/dev/pci/drm/amd/amdgpu/smuio_v13_0_6.c
smuio_v9_0.o: $S/dev/pci/drm/amd/amdgpu/smuio_v9_0.c
soc15.o: $S/dev/pci/drm/amd/amdgpu/soc15.c
soc21.o: $S/dev/pci/drm/amd/amdgpu/soc21.c
tonga_ih.o: $S/dev/pci/drm/amd/amdgpu/tonga_ih.c
umc_v6_0.o: $S/dev/pci/drm/amd/amdgpu/umc_v6_0.c
umc_v6_1.o: $S/dev/pci/drm/amd/amdgpu/umc_v6_1.c
umc_v6_7.o: $S/dev/pci/drm/amd/amdgpu/umc_v6_7.c
umc_v8_10.o: $S/dev/pci/drm/amd/amdgpu/umc_v8_10.c
umc_v8_7.o: $S/dev/pci/drm/amd/amdgpu/umc_v8_7.c
uvd_v5_0.o: $S/dev/pci/drm/amd/amdgpu/uvd_v5_0.c
uvd_v6_0.o: $S/dev/pci/drm/amd/amdgpu/uvd_v6_0.c
uvd_v7_0.o: $S/dev/pci/drm/amd/amdgpu/uvd_v7_0.c
vce_v3_0.o: $S/dev/pci/drm/amd/amdgpu/vce_v3_0.c
vce_v4_0.o: $S/dev/pci/drm/amd/amdgpu/vce_v4_0.c
vcn_sw_ring.o: $S/dev/pci/drm/amd/amdgpu/vcn_sw_ring.c
vcn_v1_0.o: $S/dev/pci/drm/amd/amdgpu/vcn_v1_0.c
vcn_v2_0.o: $S/dev/pci/drm/amd/amdgpu/vcn_v2_0.c
vcn_v2_5.o: $S/dev/pci/drm/amd/amdgpu/vcn_v2_5.c
vcn_v3_0.o: $S/dev/pci/drm/amd/amdgpu/vcn_v3_0.c
vcn_v4_0.o: $S/dev/pci/drm/amd/amdgpu/vcn_v4_0.c
vega10_ih.o: $S/dev/pci/drm/amd/amdgpu/vega10_ih.c
vega10_reg_init.o: $S/dev/pci/drm/amd/amdgpu/vega10_reg_init.c
vega20_ih.o: $S/dev/pci/drm/amd/amdgpu/vega20_ih.c
vega20_reg_init.o: $S/dev/pci/drm/amd/amdgpu/vega20_reg_init.c
vi.o: $S/dev/pci/drm/amd/amdgpu/vi.c
amdgpu_dm.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm.c
amdgpu_dm_color.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_color.c
amdgpu_dm_crtc.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_crtc.c
amdgpu_dm_helpers.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_helpers.c
amdgpu_dm_irq.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_irq.c
amdgpu_dm_mst_types.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_mst_types.c
amdgpu_dm_plane.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_plane.c
amdgpu_dm_pp_smu.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_pp_smu.c
amdgpu_dm_psr.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_psr.c
amdgpu_dm_services.o: $S/dev/pci/drm/amd/display/amdgpu_dm/amdgpu_dm_services.c
dc_fpu.o: $S/dev/pci/drm/amd/display/amdgpu_dm/dc_fpu.c
amdgpu_vector.o: $S/dev/pci/drm/amd/display/dc/basics/amdgpu_vector.c
conversion.o: $S/dev/pci/drm/amd/display/dc/basics/conversion.c
dc_common.o: $S/dev/pci/drm/amd/display/dc/basics/dc_common.c
fixpt31_32.o: $S/dev/pci/drm/amd/display/dc/basics/fixpt31_32.c
bios_parser.o: $S/dev/pci/drm/amd/display/dc/bios/bios_parser.c
bios_parser2.o: $S/dev/pci/drm/amd/display/dc/bios/bios_parser2.c
bios_parser_common.o: $S/dev/pci/drm/amd/display/dc/bios/bios_parser_common.c
bios_parser_helper.o: $S/dev/pci/drm/amd/display/dc/bios/bios_parser_helper.c
bios_parser_interface.o: $S/dev/pci/drm/amd/display/dc/bios/bios_parser_interface.c
command_table.o: $S/dev/pci/drm/amd/display/dc/bios/command_table.c
command_table2.o: $S/dev/pci/drm/amd/display/dc/bios/command_table2.c
command_table_helper.o: $S/dev/pci/drm/amd/display/dc/bios/command_table_helper.c
command_table_helper2.o: $S/dev/pci/drm/amd/display/dc/bios/command_table_helper2.c
command_table_helper_dce110.o: $S/dev/pci/drm/amd/display/dc/bios/dce110/command_table_helper_dce110.c
command_table_helper2_dce112.o: $S/dev/pci/drm/amd/display/dc/bios/dce112/command_table_helper2_dce112.c
command_table_helper_dce112.o: $S/dev/pci/drm/amd/display/dc/bios/dce112/command_table_helper_dce112.c
command_table_helper_dce80.o: $S/dev/pci/drm/amd/display/dc/bios/dce80/command_table_helper_dce80.c
clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/clk_mgr.c
dce_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dce100/dce_clk_mgr.c
dce110_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dce110/dce110_clk_mgr.c
dce112_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dce112/dce112_clk_mgr.c
dce120_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dce120/dce120_clk_mgr.c
rv1_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv1_clk_mgr.c
rv1_clk_mgr_vbios_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv1_clk_mgr_vbios_smu.c
rv2_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn10/rv2_clk_mgr.c
dcn20_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn20/dcn20_clk_mgr.c
dcn201_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn201/dcn201_clk_mgr.c
rn_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn21/rn_clk_mgr.c
rn_clk_mgr_vbios_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn21/rn_clk_mgr_vbios_smu.c
dcn30_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn30/dcn30_clk_mgr.c
dcn30_clk_mgr_smu_msg.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn30/dcn30_clk_mgr_smu_msg.c
dcn301_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn301/dcn301_smu.c
vg_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn301/vg_clk_mgr.c
dcn31_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn31/dcn31_clk_mgr.c
dcn31_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn31/dcn31_smu.c
dcn314_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn314/dcn314_clk_mgr.c
dcn314_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn314/dcn314_smu.c
dcn315_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn315/dcn315_clk_mgr.c
dcn315_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn315/dcn315_smu.c
dcn316_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn316/dcn316_clk_mgr.c
dcn316_smu.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn316/dcn316_smu.c
dcn32_clk_mgr.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn32/dcn32_clk_mgr.c
dcn32_clk_mgr_smu_msg.o: $S/dev/pci/drm/amd/display/dc/clk_mgr/dcn32/dcn32_clk_mgr_smu_msg.c
amdgpu_dc.o: $S/dev/pci/drm/amd/display/dc/core/amdgpu_dc.c
dc_debug.o: $S/dev/pci/drm/amd/display/dc/core/dc_debug.c
dc_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/core/dc_hw_sequencer.c
dc_link.o: $S/dev/pci/drm/amd/display/dc/core/dc_link.c
dc_link_ddc.o: $S/dev/pci/drm/amd/display/dc/core/dc_link_ddc.c
dc_link_dp.o: $S/dev/pci/drm/amd/display/dc/core/dc_link_dp.c
dc_link_dpcd.o: $S/dev/pci/drm/amd/display/dc/core/dc_link_dpcd.c
dc_link_dpia.o: $S/dev/pci/drm/amd/display/dc/core/dc_link_dpia.c
dc_link_enc_cfg.o: $S/dev/pci/drm/amd/display/dc/core/dc_link_enc_cfg.c
dc_resource.o: $S/dev/pci/drm/amd/display/dc/core/dc_resource.c
dc_sink.o: $S/dev/pci/drm/amd/display/dc/core/dc_sink.c
dc_stat.o: $S/dev/pci/drm/amd/display/dc/core/dc_stat.c
dc_stream.o: $S/dev/pci/drm/amd/display/dc/core/dc_stream.c
dc_surface.o: $S/dev/pci/drm/amd/display/dc/core/dc_surface.c
dc_vm_helper.o: $S/dev/pci/drm/amd/display/dc/core/dc_vm_helper.c
dc_dmub_srv.o: $S/dev/pci/drm/amd/display/dc/dc_dmub_srv.c
dc_edid_parser.o: $S/dev/pci/drm/amd/display/dc/dc_edid_parser.c
dc_helper.o: $S/dev/pci/drm/amd/display/dc/dc_helper.c
dce_abm.o: $S/dev/pci/drm/amd/display/dc/dce/dce_abm.c
dce_audio.o: $S/dev/pci/drm/amd/display/dc/dce/dce_audio.c
dce_aux.o: $S/dev/pci/drm/amd/display/dc/dce/dce_aux.c
dce_clock_source.o: $S/dev/pci/drm/amd/display/dc/dce/dce_clock_source.c
dce_dmcu.o: $S/dev/pci/drm/amd/display/dc/dce/dce_dmcu.c
dce_hwseq.o: $S/dev/pci/drm/amd/display/dc/dce/dce_hwseq.c
dce_i2c.o: $S/dev/pci/drm/amd/display/dc/dce/dce_i2c.c
dce_i2c_hw.o: $S/dev/pci/drm/amd/display/dc/dce/dce_i2c_hw.c
dce_i2c_sw.o: $S/dev/pci/drm/amd/display/dc/dce/dce_i2c_sw.c
dce_ipp.o: $S/dev/pci/drm/amd/display/dc/dce/dce_ipp.c
dce_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dce/dce_link_encoder.c
dce_mem_input.o: $S/dev/pci/drm/amd/display/dc/dce/dce_mem_input.c
dce_opp.o: $S/dev/pci/drm/amd/display/dc/dce/dce_opp.c
dce_panel_cntl.o: $S/dev/pci/drm/amd/display/dc/dce/dce_panel_cntl.c
dce_scl_filters.o: $S/dev/pci/drm/amd/display/dc/dce/dce_scl_filters.c
dce_scl_filters_old.o: $S/dev/pci/drm/amd/display/dc/dce/dce_scl_filters_old.c
dce_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dce/dce_stream_encoder.c
dce_transform.o: $S/dev/pci/drm/amd/display/dc/dce/dce_transform.c
dmub_abm.o: $S/dev/pci/drm/amd/display/dc/dce/dmub_abm.c
dmub_hw_lock_mgr.o: $S/dev/pci/drm/amd/display/dc/dce/dmub_hw_lock_mgr.c
dmub_outbox.o: $S/dev/pci/drm/amd/display/dc/dce/dmub_outbox.c
dmub_psr.o: $S/dev/pci/drm/amd/display/dc/dce/dmub_psr.c
dce100_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dce100/dce100_hw_sequencer.c
dce100_resource.o: $S/dev/pci/drm/amd/display/dc/dce100/dce100_resource.c
dce110_compressor.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_compressor.c
dce110_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_hw_sequencer.c
dce110_mem_input_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_mem_input_v.c
dce110_opp_csc_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_csc_v.c
dce110_opp_regamma_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_regamma_v.c
dce110_opp_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_opp_v.c
dce110_resource.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_resource.c
dce110_timing_generator.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_timing_generator.c
dce110_timing_generator_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_timing_generator_v.c
dce110_transform_v.o: $S/dev/pci/drm/amd/display/dc/dce110/dce110_transform_v.c
dce112_compressor.o: $S/dev/pci/drm/amd/display/dc/dce112/dce112_compressor.c
dce112_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dce112/dce112_hw_sequencer.c
dce112_resource.o: $S/dev/pci/drm/amd/display/dc/dce112/dce112_resource.c
dce120_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dce120/dce120_hw_sequencer.c
dce120_resource.o: $S/dev/pci/drm/amd/display/dc/dce120/dce120_resource.c
dce120_timing_generator.o: $S/dev/pci/drm/amd/display/dc/dce120/dce120_timing_generator.c
dce80_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dce80/dce80_hw_sequencer.c
dce80_resource.o: $S/dev/pci/drm/amd/display/dc/dce80/dce80_resource.c
dce80_timing_generator.o: $S/dev/pci/drm/amd/display/dc/dce80/dce80_timing_generator.c
dcn10_cm_common.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_cm_common.c
dcn10_dpp.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp.c
dcn10_dpp_cm.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp_cm.c
dcn10_dpp_dscl.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dpp_dscl.c
dcn10_dwb.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_dwb.c
dcn10_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hubbub.c
dcn10_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hubp.c
dcn10_hw_sequencer.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hw_sequencer.c
dcn10_hw_sequencer_debug.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_hw_sequencer_debug.c
dcn10_init.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_init.c
dcn10_ipp.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_ipp.c
dcn10_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_link_encoder.c
dcn10_mpc.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_mpc.c
dcn10_opp.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_opp.c
dcn10_optc.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_optc.c
dcn10_resource.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_resource.c
dcn10_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn10/dcn10_stream_encoder.c
dcn20_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dccg.c
dcn20_dpp.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dpp.c
dcn20_dpp_cm.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dpp_cm.c
dcn20_dsc.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dsc.c
dcn20_dwb.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dwb.c
dcn20_dwb_scl.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_dwb_scl.c
dcn20_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hubbub.c
dcn20_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hubp.c
dcn20_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_hwseq.c
dcn20_init.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_init.c
dcn20_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_link_encoder.c
dcn20_mmhubbub.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_mmhubbub.c
dcn20_mpc.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_mpc.c
dcn20_opp.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_opp.c
dcn20_optc.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_optc.c
dcn20_resource.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_resource.c
dcn20_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_stream_encoder.c
dcn20_vmid.o: $S/dev/pci/drm/amd/display/dc/dcn20/dcn20_vmid.c
dcn201_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_dccg.c
dcn201_dpp.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_dpp.c
dcn201_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hubbub.c
dcn201_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hubp.c
dcn201_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_hwseq.c
dcn201_init.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_init.c
dcn201_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_link_encoder.c
dcn201_mpc.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_mpc.c
dcn201_opp.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_opp.c
dcn201_optc.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_optc.c
dcn201_resource.o: $S/dev/pci/drm/amd/display/dc/dcn201/dcn201_resource.c
dcn21_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_dccg.c
dcn21_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hubbub.c
dcn21_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hubp.c
dcn21_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_hwseq.c
dcn21_init.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_init.c
dcn21_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_link_encoder.c
dcn21_resource.o: $S/dev/pci/drm/amd/display/dc/dcn21/dcn21_resource.c
dcn30_afmt.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_afmt.c
dcn30_cm_common.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_cm_common.c
dcn30_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dccg.c
dcn30_dio_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dio_link_encoder.c
dcn30_dio_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dio_stream_encoder.c
dcn30_dpp.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dpp.c
dcn30_dpp_cm.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dpp_cm.c
dcn30_dwb.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dwb.c
dcn30_dwb_cm.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_dwb_cm.c
dcn30_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hubbub.c
dcn30_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hubp.c
dcn30_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_hwseq.c
dcn30_init.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_init.c
dcn30_mmhubbub.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_mmhubbub.c
dcn30_mpc.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_mpc.c
dcn30_optc.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_optc.c
dcn30_resource.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_resource.c
dcn30_vpg.o: $S/dev/pci/drm/amd/display/dc/dcn30/dcn30_vpg.c
dcn301_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_dccg.c
dcn301_dio_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_dio_link_encoder.c
dcn301_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_hubbub.c
dcn301_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_hwseq.c
dcn301_init.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_init.c
dcn301_panel_cntl.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_panel_cntl.c
dcn301_resource.o: $S/dev/pci/drm/amd/display/dc/dcn301/dcn301_resource.c
dcn302_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn302/dcn302_hwseq.c
dcn302_init.o: $S/dev/pci/drm/amd/display/dc/dcn302/dcn302_init.c
dcn302_resource.o: $S/dev/pci/drm/amd/display/dc/dcn302/dcn302_resource.c
dcn303_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn303/dcn303_hwseq.c
dcn303_init.o: $S/dev/pci/drm/amd/display/dc/dcn303/dcn303_init.c
dcn303_resource.o: $S/dev/pci/drm/amd/display/dc/dcn303/dcn303_resource.c
dcn31_afmt.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_afmt.c
dcn31_apg.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_apg.c
dcn31_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_dccg.c
dcn31_dio_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_dio_link_encoder.c
dcn31_hpo_dp_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hpo_dp_link_encoder.c
dcn31_hpo_dp_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hpo_dp_stream_encoder.c
dcn31_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hubbub.c
dcn31_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hubp.c
dcn31_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_hwseq.c
dcn31_init.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_init.c
dcn31_optc.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_optc.c
dcn31_panel_cntl.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_panel_cntl.c
dcn31_resource.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_resource.c
dcn31_vpg.o: $S/dev/pci/drm/amd/display/dc/dcn31/dcn31_vpg.c
dcn314_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_dccg.c
dcn314_dio_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_dio_stream_encoder.c
dcn314_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_hwseq.c
dcn314_init.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_init.c
dcn314_optc.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_optc.c
dcn314_resource.o: $S/dev/pci/drm/amd/display/dc/dcn314/dcn314_resource.c
dcn315_resource.o: $S/dev/pci/drm/amd/display/dc/dcn315/dcn315_resource.c
dcn316_resource.o: $S/dev/pci/drm/amd/display/dc/dcn316/dcn316_resource.c
dcn32_dccg.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dccg.c
dcn32_dio_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dio_link_encoder.c
dcn32_dio_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dio_stream_encoder.c
dcn32_dpp.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_dpp.c
dcn32_hpo_dp_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hpo_dp_link_encoder.c
dcn32_hubbub.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hubbub.c
dcn32_hubp.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hubp.c
dcn32_hwseq.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_hwseq.c
dcn32_init.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_init.c
dcn32_mmhubbub.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_mmhubbub.c
dcn32_mpc.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_mpc.c
dcn32_optc.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_optc.c
dcn32_resource.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_resource.c
dcn32_resource_helpers.o: $S/dev/pci/drm/amd/display/dc/dcn32/dcn32_resource_helpers.c
dcn321_dio_link_encoder.o: $S/dev/pci/drm/amd/display/dc/dcn321/dcn321_dio_link_encoder.c
dcn321_resource.o: $S/dev/pci/drm/amd/display/dc/dcn321/dcn321_resource.c
bw_fixed.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/bw_fixed.c
custom_float.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/custom_float.c
dce_calcs.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dce_calcs.c
dcn_calc_auto.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_auto.c
dcn_calc_math.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calc_math.c
dcn_calcs.o: $S/dev/pci/drm/amd/display/dc/dml/calcs/dcn_calcs.c
dcn10_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn10/dcn10_fpu.c
dcn20_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/dcn20_fpu.c
display_mode_vba_20.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20.c
display_mode_vba_20v2.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_mode_vba_20v2.c
display_rq_dlg_calc_20.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20.c
display_rq_dlg_calc_20v2.o: $S/dev/pci/drm/amd/display/dc/dml/dcn20/display_rq_dlg_calc_20v2.c
display_mode_vba_21.o: $S/dev/pci/drm/amd/display/dc/dml/dcn21/display_mode_vba_21.c
display_rq_dlg_calc_21.o: $S/dev/pci/drm/amd/display/dc/dml/dcn21/display_rq_dlg_calc_21.c
dcn30_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/dcn30_fpu.c
display_mode_vba_30.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/display_mode_vba_30.c
display_rq_dlg_calc_30.o: $S/dev/pci/drm/amd/display/dc/dml/dcn30/display_rq_dlg_calc_30.c
dcn301_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn301/dcn301_fpu.c
dcn302_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn302/dcn302_fpu.c
dcn303_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn303/dcn303_fpu.c
dcn31_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/dcn31_fpu.c
display_mode_vba_31.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/display_mode_vba_31.c
display_rq_dlg_calc_31.o: $S/dev/pci/drm/amd/display/dc/dml/dcn31/display_rq_dlg_calc_31.c
dcn314_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/dcn314_fpu.c
display_mode_vba_314.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/display_mode_vba_314.c
display_rq_dlg_calc_314.o: $S/dev/pci/drm/amd/display/dc/dml/dcn314/display_rq_dlg_calc_314.c
dcn32_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/dcn32_fpu.c
display_mode_vba_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_32.c
display_mode_vba_util_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_mode_vba_util_32.c
display_rq_dlg_calc_32.o: $S/dev/pci/drm/amd/display/dc/dml/dcn32/display_rq_dlg_calc_32.c
dcn321_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dcn321/dcn321_fpu.c
display_mode_lib.o: $S/dev/pci/drm/amd/display/dc/dml/display_mode_lib.c
display_mode_vba.o: $S/dev/pci/drm/amd/display/dc/dml/display_mode_vba.c
display_rq_dlg_helpers.o: $S/dev/pci/drm/amd/display/dc/dml/display_rq_dlg_helpers.c
dml1_display_rq_dlg_calc.o: $S/dev/pci/drm/amd/display/dc/dml/dml1_display_rq_dlg_calc.c
rc_calc_fpu.o: $S/dev/pci/drm/amd/display/dc/dml/dsc/rc_calc_fpu.c
dc_dsc.o: $S/dev/pci/drm/amd/display/dc/dsc/dc_dsc.c
rc_calc.o: $S/dev/pci/drm/amd/display/dc/dsc/rc_calc.c
rc_calc_dpi.o: $S/dev/pci/drm/amd/display/dc/dsc/rc_calc_dpi.c
hw_factory_dce110.o: $S/dev/pci/drm/amd/display/dc/gpio/dce110/hw_factory_dce110.c
hw_translate_dce110.o: $S/dev/pci/drm/amd/display/dc/gpio/dce110/hw_translate_dce110.c
hw_factory_dce120.o: $S/dev/pci/drm/amd/display/dc/gpio/dce120/hw_factory_dce120.c
hw_translate_dce120.o: $S/dev/pci/drm/amd/display/dc/gpio/dce120/hw_translate_dce120.c
hw_factory_dce80.o: $S/dev/pci/drm/amd/display/dc/gpio/dce80/hw_factory_dce80.c
hw_translate_dce80.o: $S/dev/pci/drm/amd/display/dc/gpio/dce80/hw_translate_dce80.c
hw_factory_dcn10.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn10/hw_factory_dcn10.c
hw_translate_dcn10.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn10/hw_translate_dcn10.c
hw_factory_dcn20.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn20/hw_factory_dcn20.c
hw_translate_dcn20.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn20/hw_translate_dcn20.c
hw_factory_dcn21.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn21/hw_factory_dcn21.c
hw_translate_dcn21.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn21/hw_translate_dcn21.c
hw_factory_dcn30.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn30/hw_factory_dcn30.c
hw_translate_dcn30.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn30/hw_translate_dcn30.c
hw_factory_dcn315.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn315/hw_factory_dcn315.c
hw_translate_dcn315.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn315/hw_translate_dcn315.c
hw_factory_dcn32.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn32/hw_factory_dcn32.c
hw_translate_dcn32.o: $S/dev/pci/drm/amd/display/dc/gpio/dcn32/hw_translate_dcn32.c
gpio_base.o: $S/dev/pci/drm/amd/display/dc/gpio/gpio_base.c
gpio_service.o: $S/dev/pci/drm/amd/display/dc/gpio/gpio_service.c
hw_ddc.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_ddc.c
hw_factory.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_factory.c
hw_generic.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_generic.c
hw_gpio.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_gpio.c
hw_hpd.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_hpd.c
hw_translate.o: $S/dev/pci/drm/amd/display/dc/gpio/hw_translate.c
hdcp_msg.o: $S/dev/pci/drm/amd/display/dc/hdcp/hdcp_msg.c
irq_service_dce110.o: $S/dev/pci/drm/amd/display/dc/irq/dce110/irq_service_dce110.c
irq_service_dce120.o: $S/dev/pci/drm/amd/display/dc/irq/dce120/irq_service_dce120.c
irq_service_dce80.o: $S/dev/pci/drm/amd/display/dc/irq/dce80/irq_service_dce80.c
irq_service_dcn10.o: $S/dev/pci/drm/amd/display/dc/irq/dcn10/irq_service_dcn10.c
irq_service_dcn20.o: $S/dev/pci/drm/amd/display/dc/irq/dcn20/irq_service_dcn20.c
irq_service_dcn201.o: $S/dev/pci/drm/amd/display/dc/irq/dcn201/irq_service_dcn201.c
irq_service_dcn21.o: $S/dev/pci/drm/amd/display/dc/irq/dcn21/irq_service_dcn21.c
irq_service_dcn30.o: $S/dev/pci/drm/amd/display/dc/irq/dcn30/irq_service_dcn30.c
irq_service_dcn302.o: $S/dev/pci/drm/amd/display/dc/irq/dcn302/irq_service_dcn302.c
irq_service_dcn303.o: $S/dev/pci/drm/amd/display/dc/irq/dcn303/irq_service_dcn303.c
irq_service_dcn31.o: $S/dev/pci/drm/amd/display/dc/irq/dcn31/irq_service_dcn31.c
irq_service_dcn314.o: $S/dev/pci/drm/amd/display/dc/irq/dcn314/irq_service_dcn314.c
irq_service_dcn315.o: $S/dev/pci/drm/amd/display/dc/irq/dcn315/irq_service_dcn315.c
irq_service_dcn32.o: $S/dev/pci/drm/amd/display/dc/irq/dcn32/irq_service_dcn32.c
irq_service.o: $S/dev/pci/drm/amd/display/dc/irq/irq_service.c
link_dp_trace.o: $S/dev/pci/drm/amd/display/dc/link/link_dp_trace.c
link_hwss_dio.o: $S/dev/pci/drm/amd/display/dc/link/link_hwss_dio.c
link_hwss_dpia.o: $S/dev/pci/drm/amd/display/dc/link/link_hwss_dpia.c
link_hwss_hpo_dp.o: $S/dev/pci/drm/amd/display/dc/link/link_hwss_hpo_dp.c
virtual_link_encoder.o: $S/dev/pci/drm/amd/display/dc/virtual/virtual_link_encoder.c
virtual_link_hwss.o: $S/dev/pci/drm/amd/display/dc/virtual/virtual_link_hwss.c
virtual_stream_encoder.o: $S/dev/pci/drm/amd/display/dc/virtual/virtual_stream_encoder.c
dmub_dcn20.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn20.c
dmub_dcn21.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn21.c
dmub_dcn30.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn30.c
dmub_dcn301.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn301.c
dmub_dcn302.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn302.c
dmub_dcn303.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn303.c
dmub_dcn31.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn31.c
dmub_dcn314.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn314.c
dmub_dcn315.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn315.c
dmub_dcn316.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn316.c
dmub_dcn32.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_dcn32.c
dmub_reg.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_reg.c
dmub_srv.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_srv.c
dmub_srv_stat.o: $S/dev/pci/drm/amd/display/dmub/src/dmub_srv_stat.c
color_gamma.o: $S/dev/pci/drm/amd/display/modules/color/color_gamma.c
color_table.o: $S/dev/pci/drm/amd/display/modules/color/color_table.c
freesync.o: $S/dev/pci/drm/amd/display/modules/freesync/freesync.c
info_packet.o: $S/dev/pci/drm/amd/display/modules/info_packet/info_packet.c
power_helpers.o: $S/dev/pci/drm/amd/display/modules/power/power_helpers.c
vmid.o: $S/dev/pci/drm/amd/display/modules/vmid/vmid.c
amdgpu_dpm.o: $S/dev/pci/drm/amd/pm/amdgpu_dpm.c
amdgpu_dpm_internal.o: $S/dev/pci/drm/amd/pm/amdgpu_dpm_internal.c
amdgpu_pm.o: $S/dev/pci/drm/amd/pm/amdgpu_pm.c
legacy_dpm.o: $S/dev/pci/drm/amd/pm/legacy-dpm/legacy_dpm.c
amd_powerplay.o: $S/dev/pci/drm/amd/pm/powerplay/amd_powerplay.c
ci_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/ci_baco.c
common_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/common_baco.c
fiji_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/fiji_baco.c
hardwaremanager.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/hardwaremanager.c
hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/hwmgr.c
polaris_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/polaris_baco.c
pp_overdriver.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/pp_overdriver.c
pp_psm.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/pp_psm.c
ppatomctrl.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/ppatomctrl.c
ppatomfwctrl.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/ppatomfwctrl.c
pppcielanes.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/pppcielanes.c
process_pptables_v1_0.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/process_pptables_v1_0.c
processpptables.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/processpptables.c
smu10_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu10_hwmgr.c
smu7_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_baco.c
smu7_clockpowergating.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_clockpowergating.c
smu7_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_hwmgr.c
smu7_powertune.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_powertune.c
smu7_thermal.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu7_thermal.c
smu8_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu8_hwmgr.c
smu9_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu9_baco.c
smu_helper.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/smu_helper.c
tonga_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/tonga_baco.c
vega10_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_baco.c
vega10_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_hwmgr.c
vega10_powertune.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_powertune.c
vega10_processpptables.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_processpptables.c
vega10_thermal.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega10_thermal.c
vega12_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_baco.c
vega12_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_hwmgr.c
vega12_processpptables.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_processpptables.c
vega12_thermal.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega12_thermal.c
vega20_baco.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_baco.c
vega20_hwmgr.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_hwmgr.c
vega20_powertune.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_powertune.c
vega20_processpptables.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_processpptables.c
vega20_thermal.o: $S/dev/pci/drm/amd/pm/powerplay/hwmgr/vega20_thermal.c
ci_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/ci_smumgr.c
fiji_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/fiji_smumgr.c
iceland_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/iceland_smumgr.c
polaris10_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/polaris10_smumgr.c
smu10_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/smu10_smumgr.c
smu7_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/smu7_smumgr.c
smu8_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/smu8_smumgr.c
smu9_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/smu9_smumgr.c
smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/smumgr.c
tonga_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/tonga_smumgr.c
vega10_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/vega10_smumgr.c
vega12_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/vega12_smumgr.c
vega20_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/vega20_smumgr.c
vegam_smumgr.o: $S/dev/pci/drm/amd/pm/powerplay/smumgr/vegam_smumgr.c
amdgpu_smu.o: $S/dev/pci/drm/amd/pm/swsmu/amdgpu_smu.c
arcturus_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/arcturus_ppt.c
cyan_skillfish_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/cyan_skillfish_ppt.c
navi10_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/navi10_ppt.c
sienna_cichlid_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/sienna_cichlid_ppt.c
smu_v11_0.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/smu_v11_0.c
vangogh_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu11/vangogh_ppt.c
renoir_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu12/renoir_ppt.c
smu_v12_0.o: $S/dev/pci/drm/amd/pm/swsmu/smu12/smu_v12_0.c
aldebaran_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/aldebaran_ppt.c
smu_v13_0.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0.c
smu_v13_0_0_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_0_ppt.c
smu_v13_0_4_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_4_ppt.c
smu_v13_0_5_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_5_ppt.c
smu_v13_0_7_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/smu_v13_0_7_ppt.c
yellow_carp_ppt.o: $S/dev/pci/drm/amd/pm/swsmu/smu13/yellow_carp_ppt.c
smu_cmn.o: $S/dev/pci/drm/amd/pm/swsmu/smu_cmn.c
pci_machdep.o: $S/arch/amd64/pci/pci_machdep.c
pciide_machdep.o: $S/arch/amd64/pci/pciide_machdep.c
vga_post.o: $S/arch/amd64/pci/vga_post.c
pchb.o: $S/arch/amd64/pci/pchb.c
amas.o: $S/dev/pci/amas.c
agp_machdep.o: $S/arch/amd64/pci/agp_machdep.c
cardslot.o: $S/dev/cardbus/cardslot.c
cardbus.o: $S/dev/cardbus/cardbus.c
cardbus_map.o: $S/dev/cardbus/cardbus_map.c
cardbus_exrom.o: $S/dev/cardbus/cardbus_exrom.c
rbus.o: $S/dev/cardbus/rbus.c
com_cardbus.o: $S/dev/cardbus/com_cardbus.c
if_xl_cardbus.o: $S/dev/cardbus/if_xl_cardbus.c
if_dc_cardbus.o: $S/dev/cardbus/if_dc_cardbus.c
if_fxp_cardbus.o: $S/dev/cardbus/if_fxp_cardbus.c
if_rl_cardbus.o: $S/dev/cardbus/if_rl_cardbus.c
if_re_cardbus.o: $S/dev/cardbus/if_re_cardbus.c
if_ath_cardbus.o: $S/dev/cardbus/if_ath_cardbus.c
if_athn_cardbus.o: $S/dev/cardbus/if_athn_cardbus.c
if_atw_cardbus.o: $S/dev/cardbus/if_atw_cardbus.c
if_rtw_cardbus.o: $S/dev/cardbus/if_rtw_cardbus.c
if_ral_cardbus.o: $S/dev/cardbus/if_ral_cardbus.c
if_acx_cardbus.o: $S/dev/cardbus/if_acx_cardbus.c
if_pgt_cardbus.o: $S/dev/cardbus/if_pgt_cardbus.c
ehci_cardbus.o: $S/dev/cardbus/ehci_cardbus.c
ohci_cardbus.o: $S/dev/cardbus/ohci_cardbus.c
uhci_cardbus.o: $S/dev/cardbus/uhci_cardbus.c
if_malo_cardbus.o: $S/dev/cardbus/if_malo_cardbus.c
if_bwi_cardbus.o: $S/dev/cardbus/if_bwi_cardbus.c
rbus_machdep.o: $S/arch/amd64/amd64/rbus_machdep.c
pcmcia.o: $S/dev/pcmcia/pcmcia.c
pcmcia_cis.o: $S/dev/pcmcia/pcmcia_cis.c
pcmcia_cis_quirks.o: $S/dev/pcmcia/pcmcia_cis_quirks.c
if_ep_pcmcia.o: $S/dev/pcmcia/if_ep_pcmcia.c
if_ne_pcmcia.o: $S/dev/pcmcia/if_ne_pcmcia.c
aic_pcmcia.o: $S/dev/pcmcia/aic_pcmcia.c
com_pcmcia.o: $S/dev/pcmcia/com_pcmcia.c
wdc_pcmcia.o: $S/dev/pcmcia/wdc_pcmcia.c
if_sm_pcmcia.o: $S/dev/pcmcia/if_sm_pcmcia.c
if_xe.o: $S/dev/pcmcia/if_xe.c
if_wi_pcmcia.o: $S/dev/pcmcia/if_wi_pcmcia.c
if_malo.o: $S/dev/pcmcia/if_malo.c
if_an_pcmcia.o: $S/dev/pcmcia/if_an_pcmcia.c
pcib.o: $S/arch/amd64/pci/pcib.c
amdpcib.o: $S/dev/pci/amdpcib.c
tcpcib.o: $S/dev/pci/tcpcib.c
aapic.o: $S/arch/amd64/pci/aapic.c
hme.o: $S/dev/ic/hme.c
if_hme_pci.o: $S/dev/pci/if_hme_pci.c
isa.o: $S/dev/isa/isa.c
isadma.o: $S/dev/isa/isadma.c
fdc.o: $S/dev/isa/fdc.c
fd.o: $S/dev/isa/fd.c
com_isa.o: $S/dev/isa/com_isa.c
pckbc_isa.o: $S/dev/isa/pckbc_isa.c
vga_isa.o: $S/dev/isa/vga_isa.c
wdc_isa.o: $S/dev/isa/wdc_isa.c
mpu401.o: $S/dev/isa/mpu401.c
mpu_isa.o: $S/dev/isa/mpu_isa.c
pcppi.o: $S/dev/isa/pcppi.c
spkr.o: $S/dev/isa/spkr.c
lpt_isa.o: $S/dev/isa/lpt_isa.c
wbsio.o: $S/dev/isa/wbsio.c
sch311x.o: $S/dev/isa/sch311x.c
lm78_isa.o: $S/dev/isa/lm78_isa.c
it.o: $S/dev/isa/it.c
uguru.o: $S/dev/isa/uguru.c
aps.o: $S/dev/isa/aps.c
isa_machdep.o: $S/arch/amd64/isa/isa_machdep.c
wsdisplay.o: $S/dev/wscons/wsdisplay.c
wsdisplay_compat_usl.o: $S/dev/wscons/wsdisplay_compat_usl.c
wsevent.o: $S/dev/wscons/wsevent.c
wskbd.o: $S/dev/wscons/wskbd.c
wskbdutil.o: $S/dev/wscons/wskbdutil.c
wsmouse.o: $S/dev/wscons/wsmouse.c
wstpad.o: $S/dev/wscons/wstpad.c
wsmux.o: $S/dev/wscons/wsmux.c
wsemulconf.o: $S/dev/wscons/wsemulconf.c
wsemul_subr.o: $S/dev/wscons/wsemul_subr.c
wsemul_vt100.o: $S/dev/wscons/wsemul_vt100.c
wsemul_vt100_subr.o: $S/dev/wscons/wsemul_vt100_subr.c
wsemul_vt100_chars.o: $S/dev/wscons/wsemul_vt100_chars.c
wsemul_vt100_keys.o: $S/dev/wscons/wsemul_vt100_keys.c
pckbd.o: $S/dev/pckbc/pckbd.c
wskbdmap_mfii.o: $S/dev/pckbc/wskbdmap_mfii.c
pms.o: $S/dev/pckbc/pms.c
wscons_machdep.o: $S/arch/amd64/amd64/wscons_machdep.c
skgpio.o: $S/dev/isa/skgpio.c
pctr.o: $S/arch/amd64/amd64/pctr.c
nvram.o: $S/arch/amd64/amd64/nvram.c
hid.o: $S/dev/hid/hid.c
hidkbd.o: $S/dev/hid/hidkbd.c
hidms.o: $S/dev/hid/hidms.c
hidmt.o: $S/dev/hid/hidmt.c
hidcc.o: $S/dev/hid/hidcc.c
usb.o: $S/dev/usb/usb.c
usbdi.o: $S/dev/usb/usbdi.c
usbdi_util.o: $S/dev/usb/usbdi_util.c
usb_mem.o: $S/dev/usb/usb_mem.c
usb_subr.o: $S/dev/usb/usb_subr.c
usb_quirks.o: $S/dev/usb/usb_quirks.c
uhub.o: $S/dev/usb/uhub.c
uaudio.o: $S/dev/usb/uaudio.c
uvideo.o: $S/dev/usb/uvideo.c
utvfu.o: $S/dev/usb/utvfu.c
udl.o: $S/dev/usb/udl.c
umidi.o: $S/dev/usb/umidi.c
umidi_quirks.o: $S/dev/usb/umidi_quirks.c
ucom.o: $S/dev/usb/ucom.c
ugen.o: $S/dev/usb/ugen.c
uhidev.o: $S/dev/usb/uhidev.c
uhid.o: $S/dev/usb/uhid.c
fido.o: $S/dev/usb/fido.c
ujoy.o: $S/dev/usb/ujoy.c
ukbdmap.o: $S/dev/usb/ukbdmap.c
ukbd.o: $S/dev/usb/ukbd.c
ums.o: $S/dev/usb/ums.c
umt.o: $S/dev/usb/umt.c
uts.o: $S/dev/usb/uts.c
ubcmtp.o: $S/dev/usb/ubcmtp.c
ucycom.o: $S/dev/usb/ucycom.c
uslhcom.o: $S/dev/usb/uslhcom.c
ulpt.o: $S/dev/usb/ulpt.c
umass.o: $S/dev/usb/umass.c
umass_quirks.o: $S/dev/usb/umass_quirks.c
umass_scsi.o: $S/dev/usb/umass_scsi.c
uthum.o: $S/dev/usb/uthum.c
ugold.o: $S/dev/usb/ugold.c
utrh.o: $S/dev/usb/utrh.c
uoak_subr.o: $S/dev/usb/uoak_subr.c
uoakrh.o: $S/dev/usb/uoakrh.c
uoaklux.o: $S/dev/usb/uoaklux.c
uoakv.o: $S/dev/usb/uoakv.c
uonerng.o: $S/dev/usb/uonerng.c
urng.o: $S/dev/usb/urng.c
udcf.o: $S/dev/usb/udcf.c
umbg.o: $S/dev/usb/umbg.c
uvisor.o: $S/dev/usb/uvisor.c
udsbr.o: $S/dev/usb/udsbr.c
utwitch.o: $S/dev/usb/utwitch.c
if_aue.o: $S/dev/usb/if_aue.c
if_axe.o: $S/dev/usb/if_axe.c
if_axen.o: $S/dev/usb/if_axen.c
if_smsc.o: $S/dev/usb/if_smsc.c
if_cue.o: $S/dev/usb/if_cue.c
if_kue.o: $S/dev/usb/if_kue.c
if_cdce.o: $S/dev/usb/if_cdce.c
if_urndis.o: $S/dev/usb/if_urndis.c
if_mos.o: $S/dev/usb/if_mos.c
if_mue.o: $S/dev/usb/if_mue.c
if_udav.o: $S/dev/usb/if_udav.c
if_upl.o: $S/dev/usb/if_upl.c
if_ugl.o: $S/dev/usb/if_ugl.c
if_url.o: $S/dev/usb/if_url.c
if_ure.o: $S/dev/usb/if_ure.c
if_uaq.o: $S/dev/usb/if_uaq.c
umodem.o: $S/dev/usb/umodem.c
uftdi.o: $S/dev/usb/uftdi.c
uplcom.o: $S/dev/usb/uplcom.c
umct.o: $S/dev/usb/umct.c
uvscom.o: $S/dev/usb/uvscom.c
ubsa.o: $S/dev/usb/ubsa.c
ukspan.o: $S/dev/usb/ukspan.c
uslcom.o: $S/dev/usb/uslcom.c
uark.o: $S/dev/usb/uark.c
moscom.o: $S/dev/usb/moscom.c
umcs.o: $S/dev/usb/umcs.c
uscom.o: $S/dev/usb/uscom.c
ucrcom.o: $S/dev/usb/ucrcom.c
uxrcom.o: $S/dev/usb/uxrcom.c
uipaq.o: $S/dev/usb/uipaq.c
umsm.o: $S/dev/usb/umsm.c
uchcom.o: $S/dev/usb/uchcom.c
uticom.o: $S/dev/usb/uticom.c
if_wi_usb.o: $S/dev/usb/if_wi_usb.c
if_atu.o: $S/dev/usb/if_atu.c
if_ral.o: $S/dev/usb/if_ral.c
if_rum.o: $S/dev/usb/if_rum.c
if_run.o: $S/dev/usb/if_run.c
if_mtw.o: $S/dev/usb/if_mtw.c
if_zyd.o: $S/dev/usb/if_zyd.c
if_upgt.o: $S/dev/usb/if_upgt.c
if_urtw.o: $S/dev/usb/if_urtw.c
if_urtwn.o: $S/dev/usb/if_urtwn.c
if_rsu.o: $S/dev/usb/if_rsu.c
if_otus.o: $S/dev/usb/if_otus.c
if_umb.o: $S/dev/usb/if_umb.c
if_uath.o: $S/dev/usb/if_uath.c
if_athn_usb.o: $S/dev/usb/if_athn_usb.c
uow.o: $S/dev/usb/uow.c
uberry.o: $S/dev/usb/uberry.c
upd.o: $S/dev/usb/upd.c
uwacom.o: $S/dev/usb/uwacom.c
if_bwfm_usb.o: $S/dev/usb/if_bwfm_usb.c
umstc.o: $S/dev/usb/umstc.c
uhidpp.o: $S/dev/usb/uhidpp.c
ucc.o: $S/dev/usb/ucc.c
i2c.o: $S/dev/i2c/i2c.c
i2c_exec.o: $S/dev/i2c/i2c_exec.c
i2c_scan.o: $S/dev/i2c/i2c_scan.c
i2c_bitbang.o: $S/dev/i2c/i2c_bitbang.c
lm75.o: $S/dev/i2c/lm75.c
lm93.o: $S/dev/i2c/lm93.c
lm87.o: $S/dev/i2c/lm87.c
maxim6690.o: $S/dev/i2c/maxim6690.c
ad741x.o: $S/dev/i2c/ad741x.c
adm1021.o: $S/dev/i2c/adm1021.c
adm1024.o: $S/dev/i2c/adm1024.c
adm1025.o: $S/dev/i2c/adm1025.c
adm1030.o: $S/dev/i2c/adm1030.c
adm1031.o: $S/dev/i2c/adm1031.c
ds1631.o: $S/dev/i2c/ds1631.c
adt7460.o: $S/dev/i2c/adt7460.c
lm78_i2c.o: $S/dev/i2c/lm78_i2c.c
adm1026.o: $S/dev/i2c/adm1026.c
w83793g.o: $S/dev/i2c/w83793g.c
w83795g.o: $S/dev/i2c/w83795g.c
asc7621.o: $S/dev/i2c/asc7621.c
asc7611.o: $S/dev/i2c/asc7611.c
spdmem_i2c.o: $S/dev/i2c/spdmem_i2c.c
sdtemp.o: $S/dev/i2c/sdtemp.c
lis331dl.o: $S/dev/i2c/lis331dl.c
ihidev.o: $S/dev/i2c/ihidev.c
ikbd.o: $S/dev/i2c/ikbd.c
ims.o: $S/dev/i2c/ims.c
imt.o: $S/dev/i2c/imt.c
iatp.o: $S/dev/i2c/iatp.c
ietp.o: $S/dev/i2c/ietp.c
bmc150.o: $S/dev/i2c/bmc150.c
icc.o: $S/dev/i2c/icc.c
gpio.o: $S/dev/gpio/gpio.c
acpi.o: $S/dev/acpi/acpi.c
acpiutil.o: $S/dev/acpi/acpiutil.c
dsdt.o: $S/dev/acpi/dsdt.c
acpidebug.o: $S/dev/acpi/acpidebug.c
acpitimer.o: $S/dev/acpi/acpitimer.c
acpiac.o: $S/dev/acpi/acpiac.c
acpibat.o: $S/dev/acpi/acpibat.c
acpibtn.o: $S/dev/acpi/acpibtn.c
acpicmos.o: $S/dev/acpi/acpicmos.c
acpicpu.o: $S/dev/acpi/acpicpu.c
acpihpet.o: $S/dev/acpi/acpihpet.c
acpiec.o: $S/dev/acpi/acpiec.c
acpitz.o: $S/dev/acpi/acpitz.c
acpimadt.o: $S/dev/acpi/acpimadt.c
acpimcfg.o: $S/dev/acpi/acpimcfg.c
acpiprt.o: $S/dev/acpi/acpiprt.c
acpidmar.o: $S/dev/acpi/acpidmar.c
acpidock.o: $S/dev/acpi/acpidock.c
abl.o: $S/dev/acpi/abl.c
asmc.o: $S/dev/acpi/asmc.c
acpiasus.o: $S/dev/acpi/acpiasus.c
acpithinkpad.o: $S/dev/acpi/acpithinkpad.c
acpitoshiba.o: $S/dev/acpi/acpitoshiba.c
acpisony.o: $S/dev/acpi/acpisony.c
acpivideo.o: $S/dev/acpi/acpivideo.c
acpivout.o: $S/dev/acpi/acpivout.c
acpipwrres.o: $S/dev/acpi/acpipwrres.c
atk0110.o: $S/dev/acpi/atk0110.c
aplgpio.o: $S/dev/acpi/aplgpio.c
bytgpio.o: $S/dev/acpi/bytgpio.c
chvgpio.o: $S/dev/acpi/chvgpio.c
glkgpio.o: $S/dev/acpi/glkgpio.c
pchgpio.o: $S/dev/acpi/pchgpio.c
tipmic.o: $S/dev/acpi/tipmic.c
ccpmic.o: $S/dev/acpi/ccpmic.c
com_acpi.o: $S/dev/acpi/com_acpi.c
sdhc_acpi.o: $S/dev/acpi/sdhc_acpi.c
dwiic_acpi.o: $S/dev/acpi/dwiic_acpi.c
acpicbkbd.o: $S/dev/acpi/acpicbkbd.c
acpials.o: $S/dev/acpi/acpials.c
tpm.o: $S/dev/acpi/tpm.c
acpihve.o: $S/dev/acpi/acpihve.c
acpisbs.o: $S/dev/acpi/acpisbs.c
acpisurface.o: $S/dev/acpi/acpisurface.c
ipmi_acpi.o: $S/dev/acpi/ipmi_acpi.c
amdgpio.o: $S/dev/acpi/amdgpio.c
acpihid.o: $S/dev/acpi/acpihid.c
iosf_acpi.o: $S/dev/acpi/iosf_acpi.c
acpi_machdep.o: $S/arch/amd64/amd64/acpi_machdep.c
acpi_wakecode.o: $S/arch/amd64/amd64/acpi_wakecode.S
acpi_x86.o: $S/dev/acpi/acpi_x86.c
acpi_apm.o: $S/dev/acpi/acpi_apm.c
acpipci.o: $S/arch/amd64/pci/acpipci.c
efi.o: $S/dev/efi/efi.c
efi_machdep.o: $S/arch/amd64/amd64/efi_machdep.c
vmm.o: $S/dev/vmm/vmm.c
vmm_machdep.o: $S/arch/amd64/amd64/vmm_machdep.c
vmm_support.o: $S/arch/amd64/amd64/vmm_support.S
sdmmc.o: $S/dev/sdmmc/sdmmc.c
sdmmc_cis.o: $S/dev/sdmmc/sdmmc_cis.c
sdmmc_io.o: $S/dev/sdmmc/sdmmc_io.c
sdmmc_mem.o: $S/dev/sdmmc/sdmmc_mem.c
sdmmc_scsi.o: $S/dev/sdmmc/sdmmc_scsi.c
if_bwfm_sdio.o: $S/dev/sdmmc/if_bwfm_sdio.c
onewire.o: $S/dev/onewire/onewire.c
onewire_subr.o: $S/dev/onewire/onewire_subr.c
owid.o: $S/dev/onewire/owid.c
owsbm.o: $S/dev/onewire/owsbm.c
owtemp.o: $S/dev/onewire/owtemp.c
owctr.o: $S/dev/onewire/owctr.c

.PHONY: config
config:
	cd /home/tmp/new/src/cobaltbsd/sys/arch/amd64/compile/GENERIC.MP && config -s /home/tmp/new/src/cobaltbsd/sys -b /home/tmp/new/src/cobaltbsd/sys/arch/amd64/compile/GENERIC.MP/obj /home/tmp/new/src/cobaltbsd/sys/arch/amd64/conf/GENERIC.MP
