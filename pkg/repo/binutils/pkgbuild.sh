PKG_NAME='binutils'
PKG_VERS='2.17-openbsd'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	./configure --prefix=/usr --sysconfdir=/etc --enable-plugins --enable-shared --disable-werror --enable-64-bit-bfd --with-system-zlib --disable-nls --infodir=/usr/share/info
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
