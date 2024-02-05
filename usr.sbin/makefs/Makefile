PROG=	makefs

OBJS=	makefs.o walk.o xmalloc.o
OBJS+=	cd9660.o cd9660/cd9660_strings.o cd9660/cd9660_debug.o cd9660/cd9660_eltorito.o
OBJS+=	cd9660/cd9660_write.o cd9660/cd9660_conversion.o cd9660/iso9660_rrip.o
OBJS+=	ffs.o ffs/ffs_alloc.o ffs/ffs_balloc.o ffs/ffs_subr.o
OBJS+=	ffs/ffs_tables.o ffs/ufs_bmap.o ffs/buf.o ffs/mkfs.o
OBJS+=	msdos.o msdos/mkfs_msdos.o msdos/msdosfs_fat.o msdos/msdosfs_conv.o msdos/msdosfs_vfsops.o
OBJS+=	msdos/msdosfs_lookup.o msdos/msdosfs_denode.o msdos/msdosfs_vnops.o msdos/msdosfs_unicode.o

MAN=	makefs.8

#CFLAGS+=	-DMSDOSFS_DEBUG
CFLAGS+=-I${CURDIR}

LIBS= -lutil

BINDIR=${SBINDIR}

include cobalt.prog.mk
