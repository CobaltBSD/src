PROG=		vmd
OBJS=		vmd.o control.o log.o priv.o proc.o config.o vmm.o
OBJS+=		vm.o loadfile_elf.o pci.o virtio.o i8259.o mc146818.o
OBJS+=		ns8250.o i8253.o dhcp.o packet.o mmio.o
OBJS+=		parse.tab.o atomicio.o vioscsi.o vioraw.o vioqcow2.o fw_cfg.o
OBJS+=		vioblk.o vionet.o

CFLAGS+=	-Wall
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+=	-Wsign-compare

LIBS=		-lutil -lpthread -levent -lz

MAN=		vmd.8 vm.conf.5

BINDIR=${SBINDIR}

include cobalt.prog.mk
