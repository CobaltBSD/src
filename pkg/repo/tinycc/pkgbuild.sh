PKG_NAME='tinycc'
PKG_VERS='12072023'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.zip"

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	gmake CC=tcc
}

src_install() {
	gmake DESTDIR="${DEST}" install

	ln -s tcc "${DEST}/usr/bin/cc"
}
