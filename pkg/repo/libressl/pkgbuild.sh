PKG_NAME='libressl'
PKG_VERS='3.8.2'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	# Sweeping build fix for TCC
	find crypto ssl include tls \( -name "*.h" -o -name "*.c" \) -exec sed -e 's/__BEGIN_HIDDEN_DECLS//g' -e 's/__END_HIDDEN_DECLS//g' -i {} \;
}

src_configure() {
	./configure --prefix=/usr --with-openssldir=/etc/ssl --enable-nc --disable-tests --disable-asm
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
#TODO: ocspcheck belongs in `bin`, but should probably be omitted altogether
