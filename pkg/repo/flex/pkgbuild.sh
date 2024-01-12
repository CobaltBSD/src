PKG_NAME='flex'
PKG_VERS='2.6.4'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install

	ln -s flex "${DEST}/usr/bin/lex"
	ln -s flex.1 "${DEST}/usr/share/man/man1/lex.1"
}
