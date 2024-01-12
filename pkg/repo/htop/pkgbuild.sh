PKG_NAME='htop'
PKG_VERS='3.2.2'
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
