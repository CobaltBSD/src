PKG_NAME='Vanilla-DMZ'
PKG_VERS='0.4'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.bz2"

src_install() {
	mkdir -p "${DEST}/usr/X11R6/share/icons/Vanilla-DMZ"
	cp -rv cursors index.theme "${DEST}/usr/X11R6/share/icons/Vanilla-DMZ"
}
