#!/usr/bin/zsh -e

# Cobalt Package Manager (Atlas)

# Based off of a watered-down implementation of the Gentoo Package Management Specification (PMS)

# TODO /var/db should be /var/lib (FHS compliance)
# TODO rewrite in Lua
# TODO handle missing programs
# TODO die command
# TODO checksumming
# TODO dependencies can be handled using `tsort`

# Default directory locations
GUEST=${GUEST:=/}
CONF=${CONF:=/etc/pkg.conf} # Location of the configuration file
REPODIR=${REPODIR:=/var/db/repos}

# The pkg.conf file is just a shell script which sets the following variables
USE=${USE:=()}
REPOS=(${REPOS:=}) # Array of repositories to search (sorted by highest to lowest precedence)
FETCHCMD=${FETCHCMD:='curl -s -O'}
SRCDIR=${SRCDIR:='/usr/lib64/pkgdist'}

# If no init daemon is running, determine that the user is inside a sandbox
#pidof init > /dev/null || SANDBOX=1

# Source the configuration file as a shell script
if [ -f "${CONF}" ]; then
	source "${CONF}"
else
	echo "Configuration file not found at ${CONF}"
	exit 1
fi

# Ensure REPODIR exist
mkdir -p "${REPODIR}"

if [ -z "${REPOS[1]}" ]; then
	echo "No repo specified"
	exit 1
fi

# Defaults for variables to be specified in the build script
PKG_NAME=''
PKG_VERS=''
PKG_DESC=''
PKG_DEPS=() # Array of package build and runtime dependencies # TODO
HOMEPAGE=''
SRC_URI=''
LICENSE=() # Array of licenses said package is under
PATCHES=() # Order of patches to be applied before processing

if [ "${#}" -lt 1 ]; then
	echo "pkg expects at least two arguments; See pkg help"
	exit 1
fi

# Check if specified package exists; only required if running install, uninstall or build
PKG_DIR=
if [[ "${1}" == "merge" ]] && [ "${#}" -ge 2 ]; then
	for REPO in ${REPOS}; do
		if [[ -d ${REPODIR}/${REPO}/${2} ]]; then
			PKG_DIR=${REPODIR}/${REPO}/${2%%:*}
			if [ -f ${PKG_DIR}/pkgbuild.sh ]; then
				source ${PKG_DIR}/pkgbuild.sh
				break
			else
				echo "pkgbuild.sh missing or unreadable"
				exit 1
			fi
		fi
	done
	if [[ -z ${PKG_DIR} ]]; then
		echo "Package not found in repo"
		exit 1
	fi
fi

# Built-in build script variables
WORK="$(mktemp -d ${HOME}/.cache/WORK.XXXXXX)" # Working directory
DEST="$(mktemp -d ${HOME}/.cache/DEST.XXXXXX)" # Package's temporary DESTDIR
ARCH=$(uname -m)

INSTALLRULE=${2##*:}

case "${1}" in
	search)
		if [ ${#} -lt 2 ]; then
			echo "Missing an argument for the package to search for"
			exit 1
		fi

		find "${REPODIR}" -maxdepth 3 -name "pkgbuild.sh" | rev | cut -f2-2 -d/ | rev | grep -i ${2%:*} # Isolate package names
		;;
	merge)
		if [ ${#} -lt 2 ]; then
			echo "Missing an argument for the package to compile"
			exit 1
		fi

		echo "### You are compiling: ###"
		echo "name: ${PKG_NAME}"
		echo "vers: ${PKG_VERS}"
		echo "desc: ${PKG_DESC}"
		echo "##########################"

		trap "rm -rf ${WORK}" INT

		# Build and install using pkgbuild
		pushd "${WORK}" > /dev/null
		eval ${FETCHCMD} ${SRC_URI}
		bsdtar xf ${SRC_URI##*/} --strip-components=1

		FILESDIR="${PKG_DIR}/files"

		echo "Applying patches, if any"
		for PATCH in ${PATCHES[@]}; do
			patch -Np1 -i "${FILESDIR}/${PATCH}"
		done

		# "MALLOC" argument dictates which allocator to link with.
		# Note that some packages ignore these environment variables.
		#if [[ "${MALLOC}" == 'hardened' ]]; then
		#	CFLAGS="${CFLAGS} -lhardened_malloc"
		#	CXXFLAGS="${CXXFLAGS} -lhardened_malloc"
		#elif [[ "${MALLOC}" == 'light' ]]; then
		#	CFLAGS="${CFLAGS} -lhardened_malloc-light"
		#	CXXFLAGS="${CXXFLAGS} -lhardened_malloc-light"
		#elif [[ ! "${MALLOC}" == 'standard' ]]; then
		#	echo "Received invalid allocator option ('hardened', 'light' or 'standard')"
		#	exit 1
		#fi

		echo "Running build procedure"
		if [[ ! -z $(type "src_prepare" | grep 'function') ]]; then
			src_prepare
		fi
		if [[ ! -z $(type "src_configure" | grep 'function') ]]; then
			src_configure
		fi
		if [[ ! -z $(type "src_compile" | grep 'function') ]]; then
			src_compile
		fi
		if [[ ! -z $(type "src_install" | grep 'function') ]]; then
			src_install
		fi

		if [[ ! -z $(type "src_postinst" | grep 'function') ]]; then
			src_postinst
		fi

		mkdir -p "${GUEST}" # In case GUEST is a new directory

		# Reduce size
		echo "Optimizing install size"
		setopt nullglob
		# Strip shared objects
		if [[ -d "${DEST}/usr/lib" ]]; then
			for I in $(find "${DEST}/usr/lib" -name "*.so*"); do
				if [[ ! -z $(file "${I}" | grep "shared object") ]]; then
					strip --strip-unneeded "${I}"
					echo "Stripped ${I}"
				else
					echo "${I} is not a shared object"
				fi
			done
		fi
		# Strip executables
		if [[ -d "${DEST}/usr/libexec" ]]; then
			for I in $(find "${DEST}/usr/libexec"); do
				if [[ ! -z $(file "${I}" | grep "LSB") ]]; then
					strip --strip-all "${I}"
					echo "Stripped ${I}"
				fi
			done
		fi
		if [[ -d "${DEST}/usr/sbin" ]]; then
			for I in $(find "${DEST}/usr/sbin"); do
				if [[ ! -z $(file "${I}" | grep "LSB") ]]; then
					strip --strip-all "${I}"
					echo "Stripped ${I}"
				fi
			done
		fi
		if [[ -d "${DEST}/usr/bin" ]]; then
			for I in $(find "${DEST}/usr/bin"); do
				if [[ ! -z $(file "${I}" | grep "LSB") ]]; then
					strip --strip-all "${I}"
					echo "Stripped ${I}"
				fi
			done
		fi
		unsetopt nullglob

		# Install package
		if [ "$(ls -1 ${DEST} | wc -l)" -ne 0 ]; then # The DEST folder should never be empty, but avoid an error if it is
			cp -rvfp "${DEST}"/* "${GUEST}" 2>/dev/null # Some special files will try to print harmless warnings regarding chmod failing
		fi

		popd > /dev/null

		# Cleanup
		rm -rf "${WORK}"
		trap SIGINT

		echo "Finished."
		;;
	help)
		cat << EOF
pkg merge <pkgname> - Install the latest package with a given name
pkg search <query> - Search for packages including the text in the query
pkg help - Display this help menu
EOF
		;;
	*)
		echo "Unknown command. See pkg help"
		exit 1
		;;
esac

# XXX
# Re-run the command for each additional package specified
#if [ $# -ge 3 ]; then
#	"$0" $1 ${@:3}
#fi
