PKG_NAME='imlib2'
PKG_VERS='1.9.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	sed -e 's/SUBDIRS = lib bin modules/SUBDIRS = lib modules/' -i src/Makefile.in # Prevent attempting to build useless tools
}

src_configure() {
	CC='cc -I/usr/X11R6/include' ./configure --prefix=/usr --disable-static --disable-amd64 --with-jpeg --with-png
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install

	# Imlib2 is for some reason adding junk to the loader names, thus giving us another mess to clean up.
	cd "${DEST}/usr/lib/imlib2/loaders"
	for I in `find . -name "*.so.0.0"`; do
		mv -v ${I} ${I%%.so.0.0}.so
	done
}
