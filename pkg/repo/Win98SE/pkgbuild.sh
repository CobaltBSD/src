PKG_NAME='Win98SE'
PKG_VERS='10252023'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.bz2"

src_install() {
	mkdir -p "${DEST}/usr/share/icons"
	cp -rv SE98 "${DEST}/usr/share/icons"
}
