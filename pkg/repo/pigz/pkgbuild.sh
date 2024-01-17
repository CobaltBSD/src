PKG_NAME='pigz'
PKG_VERS='2.7'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/if (zlib_vernum() < 0x1230)/if (0)/' -i pigz.c # Disable a false-positive error
}

src_compile() {
	make CC=cc
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	cp -v pigz unpigz "${DEST}/usr/bin"

	ln -s pigz "${DEST}/usr/bin/gzip"
	ln -s unpigz "${DEST}/usr/bin/gunzip"

	mkdir -p "${DEST}/usr/share/man/man1"
	cp -v pigz.1 "${DEST}/usr/share/man/man1"

	ln -s pigz.1 "${DEST}/usr/share/man/man1/unpigz.1"
	ln -s pigz.1 "${DEST}/usr/share/man/man1/gzip.1"
	ln -s pigz.1 "${DEST}/usr/share/man/man1/gunzip.1"
}
