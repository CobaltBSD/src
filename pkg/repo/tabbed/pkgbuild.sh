PKG_NAME='tabbed'
PKG_VERS='0.7'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

#TODO: apply suckless patches
src_compile() {
	make CC='cc -I/usr/X11R6/include/freetype2'
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	cp -v tabbed xembed "${DEST}/usr/bin"

	mkdir -p "${DEST}/usr/share/man/man1"
	cp -v tabbed.1 "${DEST}/usr/share/man/man1"
}
