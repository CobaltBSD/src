PKG_NAME='compton'
PKG_VERS='git-v0.1_beta2-2013-10-21'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	sed -e 's/ -Wl,-O1//' -e 's/ -lrt//'  -i Makefile
}

src_compile() {
	gmake NO_LIBCONFIG=1 NO_DBUS=1 NO_REGEX_PCRE=1
}

src_install() {
	# We could patch the Makefile to install correctly, but it is easier to just copy them
	mkdir -p "${DEST}/usr/bin"
	cp -v compton bin/compton-trans "${DEST}/usr/bin"

	mkdir -p "${DEST}/usr/share/applications"
	cp -v compton.desktop "${DEST}/usr/share/applications"
}
