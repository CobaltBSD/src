PKG_NAME='muon'
PKG_VERS='0.2.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	muon setup -Dprefix=/usr -Dbuildtype=release -Dwrap_mode=nofallback -Dbestline=disabled build
}

src_compile() {
	samu -C build
}

src_install() {
	DESTDIR="${DEST}" muon -C build install
}
