# src
Cobalt core repository (currently a stub)

## What is Cobalt?
Cobalt is a security-focused operating system with a focus on security, minimalism and compatibility.

Cobalt can be installed under an OpenBSD-forked kernel or as a Linux distribution ("Cobalt Lite"). The latter lacks many of Cobalt's more advanced features but carries with it the wide-ranging driver support that Linux provides. Cobalt Lite is recommended for a more traditional GNU/Linux experience.

Cobalt Lite is experimental and support in the future isn't guaranteed..

More detailed information can be found at [CobaltBSD.github,io](https://cobaltbsd.github.io).

This repository contains the "glue" that makes Cobalt, such as build scripts and installation tools.

Cobalt and Cobalt Lite shared TBA common components. These are:
`LuaJIT Mako MarkupSafe Python Vanilla-DMZ acl alsa-lib alsa-utils attr bpytop bubblewrap busybox byacc bzip2 cairo cbtutils clang cmake cobalt-userspace compiler-rt core-fonts curl dav1d dialog dosfstools e2fsprogs elfutils expat fastfetch fcft ffmpeg file findutils flex flit_core fontconfig foot freetype fribidi glib gperf grep grim grub hardened_malloc harfbuzz hwdata jsoncpp labwc lavalauncher less libarchive libass libcap libcxx libcxxabi libdrm libevdev libevent libffi libinput libpciaccess libpng libpsl libressl libtasn1 libudev-zero libunwind libuv libwebp libxkbcommon libxml2 linux linux-headers lld llvm llvm-cmake make man-pages man-pages-posix mandoc mesa mozjpeg mpdecimal mpv mtdev muon musl nanosvg nasm ncurses neosurf p11-kit pango patch pax-utils pciutils pcre2 pigz pixman pkgconf psutil pyelftools rhash samurai seatd shadow slurp smack thc-secure-delete tllist tmux tzdb upx usbutils util-linux vim wayland wayland-protocols waypipe wbg wheel wlr-randr wlrctl-ng wlroots wlsunset xkeyboard-config xz zlib-ng zopfli zsh zsh-autosuggestions zsh-syntax-highlighting zxcvbn-c`
