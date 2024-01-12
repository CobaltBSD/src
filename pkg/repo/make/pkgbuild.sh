PKG_NAME='make'
PKG_VERS='4.4.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	./configure --prefix=/usr --enable-year2038 --program-prefix=g
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
