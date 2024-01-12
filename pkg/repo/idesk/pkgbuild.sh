PKG_NAME='idesk'
PKG_VERS='0.7.8'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	echo 'define DEFAULT_PREFIX "/usr"' > defaults.h
     
	sed -e 's/test "$IMLIB2_CONFIG" = "no" ; then/test "$IMLIB2_CONFIG" = "" ; then/' -i configure # Remove check for obsolescent `imlib2-config`
}

src_configure() {
	PKG_CONFIG_PATH=/usr/lib/pkgconfig:/opt/new/lib/pkgconfig CXX="c++.old `pkg-config --cflags --libs imlib2` -I/usr/X11R6/include -L/usr/X11R6/lib" ./configure --prefix=/usr
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
#TODO: fix too many redraws when moving icons
#FIXME: reimplement in pure C
