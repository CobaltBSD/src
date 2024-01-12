PKG_NAME='less'
PKG_VERS='633'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	# Build fix
	sed -e 's/#if defined WIFSIGNALED && defined WTERMSIG && HAVE_STRSIGNAL/#if 0/' -i edit.c
}

src_configure() {
	./configure --prefix=/usr
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
