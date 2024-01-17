PKG_NAME='p11-kit'
PKG_VERS='0.24.1'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

src_prepare() {
	# Prepare anchor hook
	sed -e '20,$ d' -i trust/trust-extract-compat

	cat >> trust/trust-extract-compat << "EOF"
# Copy existing anchor modifications to /etc/ssl/local
/usr/libexec/make-ca/copy-trust-modifications

# Update trst stores
/usr/sbin/make-ca -r
EOF

	# Various build fixes
	sed -e 's/__PRETTY_FUNCTION__/__func__/g' -i common/debug.h
	sed -e 's/__PRETTY_FUNCTION__/__func__/g' -i p11-kit/modules.c
	sed -e 's/#if defined(SO_PEERCRED)/#if 0/' -i common/unix-peer.c
	sed -e 's/#ifdef HAVE_STRERROR_L/#if 0/g' -i common/message.c
	sed -e 's/#ifdef HAVE_STRERROR_L/#if 0/g' -i common/debug.c
	sed -e 's/#ifdef HAVE_STRERROR_L/#if 0/g' -i common/library.c
}

src_configure() {
	LDFLAGS='-lpthread' muon setup -Dprefix=/usr -Dbuildtype=release -Dtrust_paths=/etc/pki/anchors -Dnls=false -Dtest=false -Dtrust_module=enabled p11-build
}

src_compile() {
	samu -C p11-build
}

src_install() {
	DESTDIR="${DEST}" muon -C p11-build install

	ln -fs /usr/libexec/p11-kit/trust-extract-compat "${DEST}/usr/bin/update-ca-certificates"
	ln -fs ./pkcs11/p11-kit-trust.so "${DEST}/usr/lib/libnssckbi.so"

	mkdir "${DEST}/usr/libexec/make-ca"
	cp -v "${FILESDIR}/copy-trust-modifications" "${DEST}/usr/libexec/make-ca"

	install -dm755 "${DEST}/etc/ssl/local" # Expected by make-ca

	mkdir "${DEST}/usr/sbin"
	cp -v "${FILESDIR}/make-ca" "${DEST}/usr/sbin"
}
