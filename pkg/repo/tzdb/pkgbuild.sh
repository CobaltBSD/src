PKG_NAME='tzdb'
PKG_VERS='2023c'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
