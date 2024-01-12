PKG_NAME='cairo'
PKG_VERS='1.17.6'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_configure() {
	PKG_CONFIG_PATH=/usr/lib/pkgconfig:/opt/new/lib/pkgconfig ./configure --prefix=/opt/new
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
