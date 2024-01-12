PKG_NAME='zsh-syntax-highlighting'
PKG_VERS='0.7.1'
PKG_DESC='.' # TODO
HOMEPAGE='.' # TODO
LICENSE='.' # TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_install() {
	make DESTDIR="${DEST}" PREFIX=/usr install
}
# TODO delete docs
