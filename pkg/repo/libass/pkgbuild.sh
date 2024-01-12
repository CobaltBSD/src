PKG_NAME='libass'
PKG_VERS='0.14.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

#TODO: enable asm

src_prepare() {
	sed -e "s/lt_prog_compiler_pic='-fPIC/lt_prog_compiler_pic='/g" -i configure # Remove any attempt to use -fPIC. The --without-pic configure option isn't suitable for this purpose, and since we use TCC, there is no other drawback to removing this option.
}

src_configure() {
	FRIBIDI_LIBS=/opt/new/lib FRIBIDI_CFLAGS='-I/opt/new/include/fribidi' ./configure --prefix=/usr --disable-static --disable-harfbuzz
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
