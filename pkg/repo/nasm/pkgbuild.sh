PKG_NAME='nasm'
PKG_VERS='2.15.05'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
