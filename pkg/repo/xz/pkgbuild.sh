PKG_NAME='xz'
PKG_VERS='5.4.5'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_configure() {
	./configure --prefix=/usr --disable-static --enable-sandbox=pledge --disable-doc --disable-scripts --disable-lzma-links --disable-lzmainfo --disable-lzmadec --disable-xzdec
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
