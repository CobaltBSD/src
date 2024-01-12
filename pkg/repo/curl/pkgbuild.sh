PKG_NAME='curl'
PKG_VERS='8.4.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_configure() {
	./configure --prefix=/usr --disable-static --with-openssl --enable-threaded-resolver --with-ca-path=/etc/ssl/certs --without-fish-functions-dir
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}