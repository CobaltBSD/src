PKG_NAME='pkgconf'
PKG_VERS='2.0.3'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/test(/#/' -e "s/subdir('tests')//" -i meson.build # Necessary to fully disable tests
	sed -e 's/__PRETTY_FUNCTION__/__func__/' -i libpkgconf/libpkgconf.h # Build fix
}

src_configure() {
	muon setup -Dprefix=/usr -Dbuildtype=release -Dtests=disabled -Ddefault_library=shared build
}

src_compile() {
	samu -C build
}

src_install() {
	DESTDIR="${DEST}" muon -C build install

	ln -s pkgconf "${DEST}/usr/bin/pkg-config"
}
#FIXME: segfault when in chroot without job control and no pkgs specified?
