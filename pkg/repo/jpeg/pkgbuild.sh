PKG_NAME='jpeg'
PKG_VERS='6b'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}src.v${PKG_VERS}.tar.gz"

PATCHES=(
	'jpeg-6b-v8-compat-CVE-2020-14152-1.patch' # Backports a few functions from the jpeg v8 API to support Imlib2. Also, fixes CVE-2020-14152
)

src_configure() {
	./configure --prefix="${DEST}/usr" --mandir="${DEST}/share/man" # DESTDIR not supported

	# Take a compilation detour and only build a shared library
	cat >> Makefile << "EOF"
libjpeg.so.0.0:  $(LIBOBJECTS)
	${CC} -shared $(LIBOBJECTS) -Wl,-soname,$@ -o $@
EOF
}

src_compile() {
	make libjpeg.so.0.0
}

src_install() {
	mkdir -p "${DEST}/usr/lib/pkgconfig"
	cp -v libjpeg.so.0.0 "${DEST}/usr/lib"
	cp -v "${FILESDIR}/libjpeg.pc" "${DEST}/usr/lib/pkgconfig"

	mkdir "${DEST}/usr/include"
	cp -v jpeglib.h jconfig.h jmorecfg.h "${DEST}/usr/include"
}
