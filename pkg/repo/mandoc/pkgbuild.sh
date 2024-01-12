PKG_NAME='mandoc'
PKG_VERS='1.14.6'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's@PREFIX="/usr/local"@PREFIX="/usr"@' -i configure # Fix prefix
	sed -e 's@MANDIR=@MANDIR="/usr/share/man"@' -i configure # Fix man page install directory
}

src_configure() {
	./configure
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
