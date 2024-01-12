PKG_NAME='samurai'
PKG_VERS='1.2'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

#TODO: patch so output overwrites previous line (and flushes stdout)
src_compile() {
	samu
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	mkdir -p "${DEST}/usr/share/man/man1"

	cp -v samu "${DEST}/usr/bin/"
	cp -v samu.1 "${DEST}/usr/share/man/man1/"
}
