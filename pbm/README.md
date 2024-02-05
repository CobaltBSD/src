# pbm

PBM is a fork of NetPBM designed to fit in better integrate with the rest of CobaltBSD. Various proprietary or ancient formats have removed and it has fewer dependencies.

In Cobalt, its main use-case is for image processing. Most format conversions have been outsourced to FFmpeg, but they can be accomplished with the help of libpbm too.

## Installation

`pbm` is expects itself to be installed when you build it. There are a few circular dependencies. As a general rule, the library and its headers should be installed first.
