PKG_NAME='ffmpeg'
PKG_VERS='6.0'
PKG_DESC='.' #TODO
HOMEPAGE='.' #TODO
LICENSE='.' #TODO
SRC_URI="file://${SRCDIR}/${PKG_NAME}-${PKG_VERS}.tar.xz"

#TODO: ffmpeg tools

src_prepare() {
	# TinyCC fixes
	sed -e 's/av_unused//' -i libavfilter/vf_curves.c
	sed -e 's/av_unused//g' -i libavutil/ripemd.c

	ln -s libavutil.so.58 libavutil/libavutil.so.58.2
	ln -s libswresample.so.4 libswresample/libswresample.so.4.10
	ln -s libavcodec.so.60 libavcodec/libavcodec.so.60.3
	ln -s libswscale.so.7 libswscale/libswscale.so.7.1
	ln -s libavformat.so.60 libavformat/libavformat.so.60.3
	ln -s libavfilter.so.9 libavfilter/libavfilter.so.9.3
	ln -s libavdevice.so.60 libavdevice/libavdevice.so.60.1
}

src_configure() {
	PKG_CONFIG_PATH=/usr/lib/pkgconfig:/opt/new/lib/pkgconfig CFLAGS='-D_Pragma' ./configure --enable-version3 --disable-static --enable-shared --disable-debug --enable-libfreetype --enable-openssl --disable-large-tests --enable-pic --cc=tcc --enable-x86asm --prefix=/usr --disable-inline-asm --enable-libdav1d --toolchain=hardened
	sed -e "s/#define CC_IDENT \"Unknown compiler\"/#define CC_IDENT \"`tcc --version`\"/" -i config.h # Display TCC when running `ffmpeg`
}

src_compile() {
	gmake
}

src_install() {
	gmake DESTDIR="${DEST}" install
}
