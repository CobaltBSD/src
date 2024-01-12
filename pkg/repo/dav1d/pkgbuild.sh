PKG_NAME='dav1d'
PKG_VERS='1.3.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/__builtin_unreachable();/0;/' -i include/common/attributes.h # Remove builtin that TCC doesn't have
}

src_configure() {
	muon setup -Dprefix=/usr -Dbuildtype=release -Denable_tests=false -Denable_tools=false -Ddefault_library=shared build
}

src_compile() {
	samu -C build
}

src_install() {
	DESTDIR="${DEST}" muon -C build install

	ln -s libdav1d.so.7.0.0 "${DEST}/usr/lib/libdav1d.so.7.0" # soname fix
}
