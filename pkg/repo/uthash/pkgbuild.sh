PKG_NAME='uthash'
PKG_VERS='2.3.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_install() {
	mkdir -p "${DEST}/usr/include"
	cp -rfv include/* "${DEST}/usr/include/"
}
