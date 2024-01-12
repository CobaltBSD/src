PKG_NAME='libev'
PKG_VERS='4.33'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/if ECB_MEMORY_FENCE_NEEDS_PTHREADS/if 0/' -i ev.c # Remove benign error message
}

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install
}
#TODO: might need libev pkgconfig for picom to find it
