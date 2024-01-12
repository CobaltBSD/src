PKG_NAME='LuaJIT'
PKG_VERS='2.1.0-beta3'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.gz"

# Can compile and assemble on TinyCC, with some barbaric hacking

src_prepare() {
	# Replace bswap with __swap32md (may not be ideal for 64 bit)
	sed -e 's/__asm__("bswap %0" : "=r" (r) : "0" (x)); return r;/return __swap32md(x);/g' -i src/lj_def.h

	# Remove unsupported linker option
	sed -e 's/-Wl,-E//' -i src/Makefile

	# Build the vm builder and minilua
	gmake -C src host/buildvm CC='cc'

	./src/host/buildvm -m elfasm -o lj_vm.tmp

	cat > test.lua << "EOF"
for line in io.lines() do
	if line:find(".section") then os.exit(0) end
	io.write(line:gsub("%.p2align", ".align"):gsub("%.hidden", "#.hidden"):gsub("%.L", "_L"):gsub("@PLT", " # @PLT"), "\n")
end
EOF

	cat lj_vm.tmp | ./src/host/minilua test.lua > src/lj_vm.S
}

src_compile() {
	gmake CC='cc -DLJ_NO_UNWIND'
}

src_install() {
	gmake PREFIX=/usr DESTDIR="${DEST}" install
	ln -s luajit-${PKG_VERS} "${DEST}/usr/bin/luajit"
}
