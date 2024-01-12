PKG_NAME='zsh-autosuggestions'
PKG_VERS='0.7.0'
PKG_DESC='.' # TODO
HOMEPAGE='.' # TODO
LICENSE='.' # TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_install() {
	mkdir -p "${DEST}/usr/share/zsh-autosuggestions"
	cp -v zsh-autosuggestions.zsh "${DEST}/usr/share/zsh-autosuggestions"
}
