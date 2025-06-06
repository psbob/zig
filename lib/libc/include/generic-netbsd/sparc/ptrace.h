/*	$NetBSD: ptrace.h,v 1.16 2020/09/14 09:47:43 kamil Exp $ */

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
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
 *	@(#)ptrace.h	8.1 (Berkeley) 6/11/93
 */

/*
 * SPARC-dependent ptrace definitions.
 */
#define	PT_GETREGS	(PT_FIRSTMACH + 0)
#define	PT_SETREGS	(PT_FIRSTMACH + 1)
#define	PT_GETFPREGS	(PT_FIRSTMACH + 2)
#define	PT_SETFPREGS	(PT_FIRSTMACH + 3)

#define PT_MACHDEP_STRINGS \
	"PT_GETREGS", \
	"PT_SETREGS", \
	"PT_GETFPREGS", \
	"PT_SETFPREGS",

#include <machine/reg.h>
#define PTRACE_REG_PC(r)	((unsigned long int)(r)->r_pc)
#define PTRACE_REG_FP(r)	0 /* not stored in struct reg */
#define PTRACE_REG_SET_PC(r, v)	do {	\
	(r)->r_pc = (v);		\
	(r)->r_npc = (v) + 4;		\
    } while (/*CONSTCOND*/0)
#define PTRACE_REG_SP(r)	((unsigned long int)(r)->r_out[6])
#define PTRACE_REG_INTRV(r)	((unsigned long int)(r)->r_out[0])

#define PTRACE_ILLEGAL_ASM	__asm __volatile (".word 0" : : : "memory")

#define PTRACE_BREAKPOINT	((const uint8_t[]) { 0x91, 0xd0, 0x20, 0x01 })
#define PTRACE_BREAKPOINT_ASM	__asm __volatile("ta 1")
#define PTRACE_BREAKPOINT_SIZE	4

#ifdef _KERNEL
#define PTRACE_LWP_GETPRIVATE(l) (l)->l_md.md_tf->tf_global[7]
#endif