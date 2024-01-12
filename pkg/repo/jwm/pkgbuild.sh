PKG_NAME='jwm'
PKG_VERS='2.4.3'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_configure() {
	./configure --prefix=/usr --sysconfdir=/etc
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
