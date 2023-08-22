# src
Cobalt core repository (currently a stub)

## What is Cobalt?
Cobalt is a microscopic but extremely versatile distribution of Linux geared towards towards being distribution that is highly secure but also practical to use. Cobalt contains a minimal desktop environment and utilities for creating and accessing sandboxes in the form of nested Wayland sessions.

The Cobalt desktop environment is currently very small and missing several relatively critical components which will need to be developed from scratch, but the sandboxing infrastructure is complete. Cobalt ships with NeoSurf, its dedicated web browser.

By design, most of your work will likely occur in a sandbox anyways, and the base system can be thought of as essentially immutable. Unlike virtual machines, Linux sandboxes generally have very little performance overhead. These sandboxes are essentially sub-distributions. They can be built from the ground up, or pre-installed.

## Why?
Distributions that are touted as being privacy and security-oriented, such as Qemu and Tails, do so at the immense cost of practicality. They are great to have, but not suitable for every-day usage. Cobalt intends to accomodate a vast range of purposes. It can be used for common tasks such as gaming and browsing the Internet, or for [REDACTED].

## Core Packages (136)
alsa-lib
alsa-utils
atk
bcachefs-tools
bpytop
busybox
bzip2
cairo
cbtutils
clang
cmake
cobalt-userspace
compiler-rt
curl
dhcp
dosfstools
execline
expat
fastfetch
fcft
ffmpeg
file
findutils
flex
fontconfig
foot
freetype
fribidi
fuzzel
gdk-pixbuf
gettext-tiny
girara
glib
gperf
grep
grim
gtk+
harfbuzz
hwdata
ImageMagick
jsoncpp
kanshi
keyutils
kwiml
labwc
libaio
libarchive
libass
libbsd
libcxx
libcxxabi
libdrm
libelf
libepoxy
libevdev
libevent
libffi
libfifomsg
libinput
mozjpeg
libmd
libpciaccess
libpng
libressl
libsodium
libtasn1
libudev-zero
libunwind
libusb
libuv
libvpx
libwebp
libxkbcommon
libxml2
linux (with frandom, lunatik, lkrg and bcachefs patches)
llvm
llvm-cmake
LuaJIT
lz4
m4
make
make-ca
mandoc
mdevd
mesa
mold
mpv
msgpack-c
mtdev
muon
musl
musl-fts
ncurses
neosurf
nickle
oneTBB
opendoas
openresolv
p11-kit
pango
pax-utils
pcre2
pigz
pixman
pkgconf
poppler
rhash
samurai
seatd
sixel
slurp
swappy
tiff
tllist
tmux
usbutils
userspace-rcu
util-linux
vim
wayland
wayland-protocols
wbg
wdisplays
wlroots
wlr-randr
xkeyboard-config
xz
yasm
zathura
zathura-pdf-poppler
zlib-ng
zopfli
zsh
zsh-syntax-highlighting
zstd
