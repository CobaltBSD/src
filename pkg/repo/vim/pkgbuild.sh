PKG_NAME='vim'
PKG_VERS='9.0.2103'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar"

src_prepare() {
	echo '#define SYS_VIMRC_FILE "/etc/vimrc"' >> src/feature.h
}

src_configure() {
	cd src # Running configure from top directory causes a variable conflict with `pkg`.

	#./configure --prefix=/usr --with-features=huge --with-tlib=ncursestw --with-luajit --enable-terminal --enable-multibyte
	./configure --prefix=/usr --with-features=huge --with-tlib=curses --with-luajit --enable-terminal --enable-multibyte
	#TODO: switch to ncursestw
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
