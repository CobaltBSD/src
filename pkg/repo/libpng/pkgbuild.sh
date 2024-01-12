PKG_NAME='libpng'
PKG_VERS='1.6.39'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	gunzip -ck "${FILESDIR}/${PKG_NAME}-${PKG_VERS}-apng.patch.gz" | patch -Np1 # Apply APNG patch

	sed -e 's/-Wl,--version-script=libpng.vers//' -i Makefile.in # Versioned symbols unsupported by tcc
}

src_configure() {
	./configure --enable-hardware-optimizations --prefix=/usr --disable-static
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
