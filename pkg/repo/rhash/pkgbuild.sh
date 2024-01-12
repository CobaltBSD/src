PKG_NAME='rhash'
PKG_VERS='1.4.3'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

src_prepare() {
	sed -e 's/1.4.2/1.4.3/' -i version.h # Fix incorrect version string

	sed -e 's/test -z "$cc_vendor"/#/' -i configure # Fix `configure` failing erroneously
	sed -e 's@# define USE_GCC_ASM@//@g' -i librhash/gost94.c # Disable inline assembly to allow building with TCC
}

src_configure() {
	./configure --prefix=/usr --cc=tcc --sysconfdir=/etc
}

src_compile() {
	make
}

src_install() {
	make DESTDIR="${DEST}" install

	echo "rhash --md5 -" > "${DEST}/usr/bin/md5sum"
	echo "rhash --sha1 -" > "${DEST}/usr/bin/sha1sum"
	echo "rhash --sha256 -" > "${DEST}/usr/bin/sha256sum"
	echo "rhash --sha512 -" > "${DEST}/usr/bin/sha512sum"
	echo "rhash --base32 -" > "${DEST}/usr/bin/base32"
	echo "rhash --base64 -" > "${DEST}/usr/bin/base64"

	chmod +x "${DEST}/usr/bin"/{{md5,sha{1,256,512}}sum,base{32,64}}
}
