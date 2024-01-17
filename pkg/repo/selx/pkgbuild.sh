PKG_NAME='selx'
PKG_VERS='1.0.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-v${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/__builtin_unreachable()/abort()/' -i selx.c
}

src_compile() {
	cc selx.c -I/usr/X11R6/include -lX11 -L/usr/X11R6/lib -lXext -o selx
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	cp -v selx "${DEST}/usr/bin"

	mkdir -p "${DEST}/usr/share/man/man1"
	cp -v selx.1 "${DEST}/usr/share/man/man1"
}
