PKG_NAME='fribidi'
PKG_VERS='1.0.12'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	# Fix for tcc
	sed -e 's/-Wall -ansi/-Wall/' -i configure
}

src_configure() {
	./configure --prefix=/usr --disable-deprecated
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
