#!/bin/sh
#
# $OpenBSD: gen_libdrm_intel.sh,v 1.1 2021/02/11 10:34:51 jsg Exp $
#
# Copyright (c) 2010,2011 Jasper Lievisse Adriaanse <jasper@openbsd.org>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Generate pkg-config file for libdrm_intel

usage() {
	echo "usage: ${0##*/} -c current_directory -o obj_directory"
	exit 1
}

curdir=
objdir=
while getopts "c:o:" flag; do
	case "$flag" in
		c)
			curdir=$OPTARG
			;;
		o)
			objdir=$OPTARG
			;;
		*)
			usage
			;;
	esac
done

[ -n "${curdir}" ] || usage
if [ ! -d "${curdir}" ]; then
	echo "${0##*/}: ${curdir}: not found"
	exit 1
fi
[ -n "${objdir}" ] || usage
if [ ! -w "${objdir}" ]; then
	echo "${0##*/}: ${objdir}: not found or not writable"
	exit 1
fi

lib_version=$(fgrep -m1 version ${curdir}/../../meson.build | sed -e "s/^.*'\(.*\)'.*$/\1/")

pc_file="${objdir}/libdrm_intel.pc"
cat > ${pc_file} << __EOF__
prefix=/usr/X11R6
libdir=\${prefix}/lib
includedir=\${prefix}/include

Name: libdrm_intel
Description: Userspace interface to intel kernel DRM services
Version: ${lib_version}
Requires: libdrm
Libs: -L\${libdir} -ldrm_intel
Cflags: -I\${includedir} -I\${includedir}/libdrm
__EOF__
