PKG_NAME='Nordic-darker'
PKG_VERS='40'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-v${PKG_VERS}.tar.gz"

src_install() {
	mkdir -p "${DEST}/usr/share/themes/Nordic-darker"
	cp -rv * "${DEST}/usr/share/themes/Nordic-darker"
}
