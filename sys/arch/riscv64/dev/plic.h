/*	$OpenBSD: plic.h,v 1.3 2021/05/12 01:20:52 jsg Exp $	*/

/*
 * Copyright (c) 2020, Mars Li <mengshi.li.mars@gmail.com>
 * Copyright (c) 2020, Brian Bamsch <bbamsch@google.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _RISCV_PLIC_H_
#define _RISCV_PLIC_H_

#ifndef _LOCORE

void	plic_splx(int);
int	plic_spllower(int);
int	plic_splraise(int);
void	plic_setipl(int);

void	*plic_intr_establish(int, int, int (*)(void *),
		void *, char *);
void	*plic_intr_establish_fdt(void *, int *, int,
		int (*)(void *), void *, char *);
void	plic_intr_disestablish(void *);

#endif /* ! _LOCORE */

#endif /* _RISCV_PLIC_H_*/
