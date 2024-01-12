PKG_NAME='expat'
PKG_VERS='2.5.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
