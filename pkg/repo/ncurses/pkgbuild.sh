PKG_NAME='ncurses'
PKG_VERS='6.4'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e "s/-Wl,-Bshareable,-soname,'\$cf_cv_shared_soname',-stats,-lc/-Wl,-soname,'\$cf_cv_shared_soname'/" -i configure # TCC fix
}

src_configure() {
	./configure --prefix=/usr --mandir=/usr/share/man --with-shared --without-debug --without-normal --enable-widec --with-pthread --enable-reentrant --enable-symlinks --enable-bsdpad --without-cxx --with-default-terminfo-dir=/usr/share/terminfo
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install

	for lib in ncurses form panel menu; do
		echo "INPUT(-l${lib}w)" > "${DEST}/usr/lib/lib${lib}.so"
	done

	echo "INPUT(-lncursesw)" > "${DEST}/usr/lib/libcurses.so"
}
