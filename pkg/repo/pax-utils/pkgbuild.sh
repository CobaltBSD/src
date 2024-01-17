PKG_NAME='pax-utils'
PKG_VERS='1.3.7'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

PATCHES=(
	'pax-utils-consolidated-1.patch'
)

src_configure() {
	muon setup -Dprefix=/usr -Dbuildtype=release -Dlddtree_implementation=sh -Duse_seccomp=false -Duse_fuzzing=false -Dtests=false build
}

src_compile() {
	samu -C build
}

src_install() {
	DESTDIR="${DEST}" muon -C build install
}
