PKG_NAME='nsxiv'
PKG_VERS='32'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_compile() {
	make CFLAGS='-I/opt/new/include -I/usr/X11R6/include -I/usr/X11R6/include/freetype2' LDFLAGS='-L/opt/new/lib -L/usr/X11R6/lib -lm' HAVE_INOTIFY=0
}

src_install() {
	make CFLAGS='-I/opt/new/include -I/usr/X11R6/include -I/usr/X11R6/include/freetype2' LDFLAGS='-L/opt/new/lib -L/usr/X11R6/lib -lm' DESTDIR="${DEST}" PREFIX=/usr install
}
