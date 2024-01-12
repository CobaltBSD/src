# Cobalt BSD

The source tree for Cobalt, a lightweight and secure desktop operating system for the x86\_64 architecture.

Cobalt is a fork of OpenBSD.

This repository is currently incomplete. Come back later for updates.

## What is Cobalt?

Cobalt is a security-focused desktop operating system designed for everyday usage. It is designed to be small, efficient and modern.

If you are not willing to commit to using Cobalt, you can opt for [Cobalt Linux](https://github.com/cobaltbsd/cobalt-linux), a micro-distribution of Linux built on Cobalt's ecosystem.

More detailed information about this project can be found at [CobaltBSD.github.io](https://cobaltbsd.github.io).

## Features
* 100% written in C: No C++ compilation is required to build, and Cobalt will compile successfully in TinyCC.
* Easy extensibility and application development provided by LuaJIT interfaces.
* Your data is better protected by the advanced HAMMER2 filesystem, adapted from DragonflyBSD.
* Excellent multimedia support and acceleration provided by ffmpeg
* Ships with NeoSurf, a fork of the NetSurf web browser designed to better protect your anonymity online.
* Small: The entire installed operating system, including necessary compilation tools, is around 500MB.

## Roadmap
Cobalt is still in early development.
* Fix building the libc and kernel using tinycc
* Replace idesk with a C alternative
* Figure out what to do about Mesa's GLSL compiler, which is the only other unavoidable C++ component

## Directories
`distrib` - Various scripts and Makefiles related to the packaging of Cobalt

`etc` - Various configurations that do not belong with any other package

`include` - Header files belong to the C library

`lib` - The core libraries

`libexec` - Various programs intended to be used by other programs and libraries

`lua` - The LuaJIT infrastructure and interfaces

`pkg` - Various third-party packages that the base system is comprised of

`share` - Various miscellaneous assets

`sys` - The kernel sources

`usr.bin` - Unprivileged executables

`usr.sbin` - Executables intended for system administration

`xenocara` - The display server sources and related libraries. Note that this is not identical to OpenBSD's xenocara
