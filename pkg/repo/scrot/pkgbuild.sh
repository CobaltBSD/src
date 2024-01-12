PKG_NAME='scrot'
PKG_VERS='1.10'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_configure() {
	SCROT_DEPS_CFLAGS='-I/usr/X11R6/include -I/opt/new/include' SCROT_DEPS_LIBS='-L/opt/new/lib -lImlib2 -L/usr/X11R6/lib -lX11 -lXinerama -lXfixes -lXcomposite -lXext' ./configure --prefix=/usr
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
