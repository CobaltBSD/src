PKG_NAME='mpv'
PKG_VERS='0.35.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

#FIXME: build without Python

src_prepare() {
	sed -e 's/#if HAVE_GLIBC_THREAD_NAME/#if 0/' -i osdep/threads.c
	sed -e 's/#ifdef __GNUC__/#if 0/' -i osdep/compiler.h
}

src_configure() {
	PKG_CONFIG_PATH=/usr/lib/pkgconfig:/opt/new/lib/pkgconfig:/usr/X11R6/lib/pkgconfig LDFLAGS='-L/opt/new/lib -L/usr/X11R6/lib -lm' muon setup -Dprefix=/usr -Dbuildtype=release -Dx11=enabled -Dlua=luajit build
}

src_compile() {
	samu -C build
}

src_install() {
	DESTDIR="${DEST}" muon -C build install
}
