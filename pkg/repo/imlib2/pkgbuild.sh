PKG_NAME='imlib2'
PKG_VERS='1.9.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	sed -e 's/SUBDIRS = lib bin modules/SUBDIRS = lib modules/' -i src/Makefile.in # Prevent attempting to build useless tools
}

src_configure() {
	CC='cc -I/usr/X11R6/include' ./configure --prefix=/usr --disable-static --disable-amd64 #TODO enable asm
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
	#TODO: should at least require libjpeg and libpng?
}
