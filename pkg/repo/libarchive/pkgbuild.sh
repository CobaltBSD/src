PKG_NAME='libarchive'
PKG_VERS='3.7.2'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_configure() {
	./configure --prefix=/usr --disable-static --disable-bsdcat
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}

#TODO: symlinks for tar and cpio (bsdtar and bsdpcio respectively)
