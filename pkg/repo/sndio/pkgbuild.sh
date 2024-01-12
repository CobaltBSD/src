PKG_NAME='sndio'
PKG_VERS='1.9.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	./configure --disable-sun --disable-rmidi --prefix=/usr
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
