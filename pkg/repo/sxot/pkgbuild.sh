PKG_NAME='sxot'
PKG_VERS='0.1.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-v${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/__builtin_unreachable()/abort()/' -i sxot.c
}

src_compile() {
	cc sxot.c -I/usr/X11R6/include -lX11 -L/usr/X11R6/lib -lXfixes -o sxot
}

src_install() {
	mkdir -p "${DEST}/usr/bin"
	cp -v sxot "${DEST}/usr/bin"
}
