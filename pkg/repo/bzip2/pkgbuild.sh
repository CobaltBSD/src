PKG_NAME='bzip2'
PKG_VERS='1.0.8'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's@\(ln -s -f \)$(PREFIX)/bin/@\1@' -i Makefile # Ensure relative symbolic links
	sed -e 's@(PREFIX)/man@(PREFIX)/share/man@g' -i Makefile # Ensure man pages in correct location
}

src_compile() {
	make -f Makefile-libbz2_so CC=cc
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	mkdir "${DEST}/usr/lib"

	cp -v bzip2-shared "${DEST}/usr/bin/bzip2"
	cp -av libbz2.so* "${DEST}/usr/lib/"

	mkdir "${DEST}/usr/include"
	cp bzlib.h "${DEST}/usr/include"
}
