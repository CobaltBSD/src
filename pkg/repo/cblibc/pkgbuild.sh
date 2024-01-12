PKG_NAME='cblibc'
PKG_VERS='0.1.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_compile() {
	make CC=clang.old
}

src_install() {
	make DESTDIR="${DEST}" install
}
#FIXME: adapt for tcc
