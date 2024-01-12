PKG_NAME='dialog'
PKG_VERS='1.3-20221229'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tgz"

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
