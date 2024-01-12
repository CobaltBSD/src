PKG_NAME='xlockmore'
PKG_VERS='5.32'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.bz2"

src_prepare() {
	# Disable C++ code
	sed -e 's/$(DOG)i_/#/g' -i modes/glx/Makefile.in
	sed -e 's/$(DOG)i_/#/g' -i modes/Makefile.in
	sed -e 's/$(DOM)solitaire/#/' -e 's/$(CX)$(O)/#/' -e 's/$(CXX) -c/#/' -e 's/$(DOG)i_/#/g' -e 's/@XLOCKLDFLAGS@//' -i modes/Makefile.in
}

src_configure() {
	./configure --prefix="${DEST}/usr" --enable-appdefaultdir="${DEST}/usr/X11R6/share/X11/app-defaults" # DESTDIR unsupported
	sed -e 's/#define HAVE_CXX 1//' -i config.h
}

src_compile() {
	make
}

src_install() {
	make install
}
