PKG_NAME='st'
PKG_VERS='0.9'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

PATCHES=(
	'st-consolidated-1.patch'
)

src_prepare() {
	sed -e 's/-lrt //' -i config.mk # This library is part of libc on OpenBSD
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" PREFIX=/usr install
}
