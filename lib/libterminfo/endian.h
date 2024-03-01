/*	$NetBSD: endian.h,v 1.32 2024/01/03 18:43:52 christos Exp $	*/

/*
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)endian.h	8.1 (Berkeley) 6/11/93
 */

#ifndef _SYS2_ENDIAN_H_
#define _SYS2_ENDIAN_H_

#include <stdint.h>

#define __CAST(__dt, __st) ((__dt)(__st))

//#include <sys/featuretest.h>

#endif /* _XOPEN_SOURCE || _NETBSD_SOURCE */


//#include <machine/endian_machdep.h>

#if 1
/*
 *  Traditional names for byteorder.  These are defined as the numeric
 *  sequences so that third party code can "#define XXX_ENDIAN" and not
 *  cause errors.
 */
#define BYTE_ORDER	_BYTE_ORDER

//#include <machine/bswap.h>

/*
 * Routines to encode/decode big- and little-endian multi-octet values
 * to/from an octet stream.
 */

static __inline void __unused
be16enc(void *buf, uint16_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	p[0] = __CAST(uint8_t, ((__CAST(unsigned, u) >> 8) & 0xff));
	p[1] = __CAST(uint8_t, (u & 0xff));
}

static __inline void __unused
le16enc(void *buf, uint16_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	p[0] = __CAST(uint8_t, (u & 0xff));
	p[1] = __CAST(uint8_t, ((__CAST(unsigned, u) >> 8) & 0xff));
}

static __inline uint16_t __unused
be16dec(const void *buf)
{
	const uint8_t *p = __CAST(const uint8_t *, buf);

	return ((__CAST(uint16_t, p[0]) << 8) | p[1]);
}

static __inline uint16_t __unused
le16dec(const void *buf)
{
	const uint8_t *p = __CAST(const uint8_t *, buf);

	return (p[0] | (__CAST(uint16_t, p[1]) << 8));
}

static __inline void __unused
be32enc(void *buf, uint32_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	p[0] = __CAST(uint8_t, ((u >> 24) & 0xff));
	p[1] = __CAST(uint8_t, ((u >> 16) & 0xff));
	p[2] = __CAST(uint8_t, ((u >> 8) & 0xff));
	p[3] = __CAST(uint8_t, (u & 0xff));
}

static __inline void __unused
le32enc(void *buf, uint32_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	p[0] = __CAST(uint8_t, (u & 0xff));
	p[1] = __CAST(uint8_t, ((u >> 8) & 0xff));
	p[2] = __CAST(uint8_t, ((u >> 16) & 0xff));
	p[3] = __CAST(uint8_t, ((u >> 24) & 0xff));
}

static __inline uint32_t __unused
be32dec(const void *buf)
{
	const uint8_t *p = __CAST(const uint8_t *, buf);

	return ((__CAST(uint32_t, be16dec(p)) << 16) | be16dec(p + 2));
}

static __inline uint32_t __unused
le32dec(const void *buf)
{
	const uint8_t *p = __CAST(const uint8_t *, buf);

	return (le16dec(p) | (__CAST(uint32_t, le16dec(p + 2)) << 16));
}

static __inline void __unused
be64enc(void *buf, uint64_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	be32enc(p, __CAST(uint32_t, (u >> 32)));
	be32enc(p + 4, __CAST(uint32_t, (u & 0xffffffffULL)));
}

static __inline void __unused
le64enc(void *buf, uint64_t u)
{
	uint8_t *p = __CAST(uint8_t *, buf);

	le32enc(p, __CAST(uint32_t, (u & 0xffffffffULL)));
	le32enc(p + 4, __CAST(uint32_t, (u >> 32)));
}

static __inline uint64_t __unused
be64dec(const void *buf)
{
	const uint8_t *p = (const uint8_t *)buf;

	return ((__CAST(uint64_t, be32dec(p)) << 32) | be32dec(p + 4));
}

static __inline uint64_t __unused
le64dec(const void *buf)
{
	const uint8_t *p = (const uint8_t *)buf;

	return (le32dec(p) | (__CAST(uint64_t, le32dec(p + 4)) << 32));
}

#endif /* !_SYS2_ENDIAN_H_ */
