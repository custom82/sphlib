/* $Id: sph_luffa.h 260 2011-01-18 16:16:10Z tp $ */
/**
 * Luffa interface. Luffa is a family of hash functions with one
 * output size (in bits) for each instance: 224, 256, 384 and 512.
 *
 * ==========================(LICENSE BEGIN)============================
 *
 * Copyright (c) 2007-2010  Projet RNRT SAPHIR
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ===========================(LICENSE END)=============================
 *
 * @file     sph_luffa.h
 * @author   Thomas Pornin <thomas.pornin@cryptolog.com>
 */

#ifndef SPH_LUFFA_H__
#define SPH_LUFFA_H__

#include <stddef.h>
#include "sph_types.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Output size (in bits) for Luffa-224.
 */
#define SPH_SIZE_luffa224   224

/**
 * Output size (in bits) for Luffa-256.
 */
#define SPH_SIZE_luffa256   256

/**
 * Output size (in bits) for Luffa-384.
 */
#define SPH_SIZE_luffa384   384

/**
 * Output size (in bits) for Luffa-512.
 */
#define SPH_SIZE_luffa512   512

/**
 * This structure is a context for Luffa-224 computations. It is
 * identical to the common `luffa_small_context`. Please use the
 * latter for any in-pace hashing.
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[32];    /* first field, for alignment */
	size_t ptr;
	uint32_t V[32];           /* MODIFICATO: Array lineare per compatibilità Ravencoin */
#endif
} sph_luffa224_context;

/**
 * This structure is a context for Luffa-256 computations. It is
 * identical to the common `luffa_small_context`.
 */
typedef sph_luffa224_context sph_luffa256_context;

/**
 * This structure is a context for Luffa-384 computations. It is
 * identical to the common `luffa_small_context`.
 */
typedef sph_luffa224_context sph_luffa384_context;

/**
 * This structure is a context for Luffa-512 computations. It is
 * identical to the common `luffa_small_context`.
 */
typedef sph_luffa224_context sph_luffa512_context;

/**
 * Type for a Luffa-224 context (identical to the common context).
 */
typedef sph_luffa224_context sph_luffa_small_context;

/* MACRO AGGIUNTE PER COMPATIBILITÀ CON RAVENCOIN luffa.c */
#ifndef LUFFA_DECLARE_VARS
#define LUFFA_DECLARE_VARS \
    uint32_t V00, V01, V02, V03, V04, V05, V06, V07; \
    uint32_t V10, V11, V12, V13, V14, V15, V16, V17; \
    uint32_t V20, V21, V22, V23, V24, V25, V26, V27; \
    uint32_t V30, V31, V32, V33, V34, V35, V36, V37;
#endif

#ifndef LUFFA_READ_STATE
#define LUFFA_READ_STATE(state) \
    V00 = (state)->V[0];  V01 = (state)->V[1];  V02 = (state)->V[2];  V03 = (state)->V[3]; \
    V04 = (state)->V[4];  V05 = (state)->V[5];  V06 = (state)->V[6];  V07 = (state)->V[7]; \
    V10 = (state)->V[8];  V11 = (state)->V[9];  V12 = (state)->V[10]; V13 = (state)->V[11]; \
    V14 = (state)->V[12]; V15 = (state)->V[13]; V16 = (state)->V[14]; V17 = (state)->V[15]; \
    V20 = (state)->V[16]; V21 = (state)->V[17]; V22 = (state)->V[18]; V23 = (state)->V[19]; \
    V24 = (state)->V[20]; V25 = (state)->V[21]; V26 = (state)->V[22]; V27 = (state)->V[23]; \
    V30 = (state)->V[24]; V31 = (state)->V[25]; V32 = (state)->V[26]; V33 = (state)->V[27]; \
    V34 = (state)->V[28]; V35 = (state)->V[29]; V36 = (state)->V[30]; V37 = (state)->V[31]
#endif

#ifndef LUFFA_WRITE_STATE
#define LUFFA_WRITE_STATE(state) \
    (state)->V[0] = V00;  (state)->V[1] = V01;  (state)->V[2] = V02;  (state)->V[3] = V03; \
    (state)->V[4] = V04;  (state)->V[5] = V05;  (state)->V[6] = V06;  (state)->V[7] = V07; \
    (state)->V[8] = V10;  (state)->V[9] = V11;  (state)->V[10] = V12; (state)->V[11] = V13; \
    (state)->V[12] = V14; (state)->V[13] = V15; (state)->V[14] = V16; (state)->V[15] = V17; \
    (state)->V[16] = V20; (state)->V[17] = V21; (state)->V[18] = V22; (state)->V[19] = V23; \
    (state)->V[20] = V24; (state)->V[21] = V25; (state)->V[22] = V26; (state)->V[23] = V27; \
    (state)->V[24] = V30; (state)->V[25] = V31; (state)->V[26] = V32; (state)->V[27] = V33; \
    (state)->V[28] = V34; (state)->V[29] = V35; (state)->V[30] = V36; (state)->V[31] = V37
#endif
/* FINE MACRO AGGIUNTE */

/**
 * Initialize a Luffa-224 context. This process performs no memory
 * allocation.
 *
 * @param cc   the Luffa-224 context (pointer to a
 *             <code>sph_luffa224_context</code>)
 */
void sph_luffa224_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is
 * zero (in which case this function does nothing).
 *
 * @param cc     the Luffa-224 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_luffa224(void *cc, const void *data, size_t len);

/**
 * Terminate the current Luffa-224 computation and output the result
 * into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (28 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the Luffa-224 context
 * @param dst   the destination buffer
 */
void sph_luffa224_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result. If bit length is not a multiple
 * of 8, then the extra bits are taken from the high bits of
 * <code>ub</code>. The context is automatically reinitialized.
 *
 * @param cc    the Luffa-224 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_luffa224_addbits_and_close(void *cc, unsigned ub, unsigned n,
	void *dst);

/**
 * Initialize a Luffa-256 context. This process performs no memory
 * allocation.
 *
 * @param cc   the Luffa-256 context (pointer to a
 *             <code>sph_luffa256_context</code>)
 */
void sph_luffa256_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is
 * zero (in which case this function does nothing).
 *
 * @param cc     the Luffa-256 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_luffa256(void *cc, const void *data, size_t len);

/**
 * Terminate the current Luffa-256 computation and output the result
 * into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (32 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the Luffa-256 context
 * @param dst   the destination buffer
 */
void sph_luffa256_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result. If bit length is not a multiple
 * of 8, then the extra bits are taken from the high bits of
 * <code>ub</code>. The context is automatically reinitialized.
 *
 * @param cc    the Luffa-256 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_luffa256_addbits_and_close(void *cc, unsigned ub, unsigned n,
	void *dst);

/**
 * Initialize a Luffa-384 context. This process performs no memory
 * allocation.
 *
 * @param cc   the Luffa-384 context (pointer to a
 *             <code>sph_luffa384_context</code>)
 */
void sph_luffa384_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is
 * zero (in which case this function does nothing).
 *
 * @param cc     the Luffa-384 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_luffa384(void *cc, const void *data, size_t len);

/**
 * Terminate the current Luffa-384 computation and output the result
 * into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (48 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the Luffa-384 context
 * @param dst   the destination buffer
 */
void sph_luffa384_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result. If bit length is not a multiple
 * of 8, then the extra bits are taken from the high bits of
 * <code>ub</code>. The context is automatically reinitialized.
 *
 * @param cc    the Luffa-384 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_luffa384_addbits_and_close(void *cc, unsigned ub, unsigned n,
	void *dst);

/**
 * Initialize a Luffa-512 context. This process performs no memory
 * allocation.
 *
 * @param cc   the Luffa-512 context (pointer to a
 *             <code>sph_luffa512_context</code>)
 */
void sph_luffa512_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is
 * zero (in which case this function does nothing).
 *
 * @param cc     the Luffa-512 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_luffa512(void *cc, const void *data, size_t len);

/**
 * Terminate the current Luffa-512 computation and output the result
 * into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (64 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the Luffa-512 context
 * @param dst   the destination buffer
 */
void sph_luffa512_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result. If bit length is not a multiple
 * of 8, then the extra bits are taken from the high bits of
 * <code>ub</code>. The context is automatically reinitialized.
 *
 * @param cc    the Luffa-512 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_luffa512_addbits_and_close(void *cc, unsigned ub, unsigned n,
	void *dst);

#ifdef __cplusplus
}
#endif

#endif
