PKG_NAME='byacc'
PKG_VERS='20230219'
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

	ln -s yacc "${DEST}/usr/bin/byacc"
	ln -s yacc.1 "${DEST}/usr/share/man/man1/byacc.1"
}
