PKG_NAME='zsh'
PKG_VERS='5.9'
PKG_DESC='.' # TODO
HOMEPAGE='.' # TODO
LICENSE='.' # TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_configure() {
	./configure --prefix=/usr --sysconfdir=/etc/zsh --enable-etcdir=/etc/zsh --enable-multibyte --enable-zsh-secure-free

	# Needs to be applied after `./configure` or else GNU autotools will complain
	sed -e 's/-Wl,-E//' -i Config/defs.mk
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}

# TODO: add to /etc/shells?
