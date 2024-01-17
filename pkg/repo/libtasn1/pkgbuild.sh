PKG_NAME='libtasn1'
PKG_VERS='4.19.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's@#  define _ASN1_GCC_VERSION@#define _ASN_GCC_VERSION 0 //@' -i lib/includes/libtasn1.h.in # Fix p11-kit building
}

src_configure() {
	./configure --prefix=/usr --with-packager=Cobalt --disable-static
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
