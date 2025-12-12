/* sph_luffa.h - Versione modificata per compatibilità con Ravencoin luffa.c */
#ifndef SPH_LUFFA_H__
#define SPH_LUFFA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

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
 * MODIFICATO: Questa struttura è un contesto per i calcoli Luffa.
 * La struttura è stata modificata da V[3][8] a V[32] per compatibilità
 * con l'implementazione luffa.c presente in Ravencoin.
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
    unsigned char buf[32];    /* first field, for alignment */
    size_t ptr;
    uint32_t V[32];           /* MODIFICATO: Array lineare di 32 elementi */
#endif
} sph_luffa224_context;

/**
 * Questo è un contesto per calcoli Luffa-256. È identico a
 * <code>sph_luffa224_context</code>.
 */
typedef sph_luffa224_context sph_luffa256_context;

/**
 * Contesto per Luffa-384 (usa la stessa struttura di Luffa-224).
 */
typedef sph_luffa224_context sph_luffa384_context;

/**
 * Contesto per Luffa-512 (usa la stessa struttura di Luffa-224).
 */
typedef sph_luffa224_context sph_luffa512_context;

/* Funzioni di supporto per la lettura e scrittura di interi in little-endian */
static inline uint32_t dec32le_aligned(const void *p) {
    const uint8_t *buf = (const uint8_t *)p;
    return (uint32_t)buf[0] | ((uint32_t)buf[1] << 8) |
           ((uint32_t)buf[2] << 16) | ((uint32_t)buf[3] << 24);
}

static inline void enc32le(void *dst, uint32_t x) {
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = (uint8_t)(x);
    buf[1] = (uint8_t)(x >> 8);
    buf[2] = (uint8_t)(x >> 16);
    buf[3] = (uint8_t)(x >> 24);
}

/* Macro per dichiarare le variabili di stato locali */
#define DECLARE_STATE_VARS \
    uint32_t V00, V01, V02, V03, V04, V05, V06, V07; \
    uint32_t V10, V11, V12, V13, V14, V15, V16, V17; \
    uint32_t V20, V21, V22, V23, V24, V25, V26, V27; \
    uint32_t V30, V31, V32, V33, V34, V35, V36, V37;

/* Macro per leggere lo stato in variabili locali */
#define READ_STATE(state) do { \
    V00 = (state)->V[0]; \
    V01 = (state)->V[1]; \
    V02 = (state)->V[2]; \
    V03 = (state)->V[3]; \
    V04 = (state)->V[4]; \
    V05 = (state)->V[5]; \
    V06 = (state)->V[6]; \
    V07 = (state)->V[7]; \
    V10 = (state)->V[8]; \
    V11 = (state)->V[9]; \
    V12 = (state)->V[10]; \
    V13 = (state)->V[11]; \
    V14 = (state)->V[12]; \
    V15 = (state)->V[13]; \
    V16 = (state)->V[14]; \
    V17 = (state)->V[15]; \
    V20 = (state)->V[16]; \
    V21 = (state)->V[17]; \
    V22 = (state)->V[18]; \
    V23 = (state)->V[19]; \
    V24 = (state)->V[20]; \
    V25 = (state)->V[21]; \
    V26 = (state)->V[22]; \
    V27 = (state)->V[23]; \
    V30 = (state)->V[24]; \
    V31 = (state)->V[25]; \
    V32 = (state)->V[26]; \
    V33 = (state)->V[27]; \
    V34 = (state)->V[28]; \
    V35 = (state)->V[29]; \
    V36 = (state)->V[30]; \
    V37 = (state)->V[31]; \
} while(0)

/* Macro per scrivere lo stato dalle variabili locali */
#define WRITE_STATE(state) do { \
    (state)->V[0] = V00; \
    (state)->V[1] = V01; \
    (state)->V[2] = V02; \
    (state)->V[3] = V03; \
    (state)->V[4] = V04; \
    (state)->V[5] = V05; \
    (state)->V[6] = V06; \
    (state)->V[7] = V07; \
    (state)->V[8] = V10; \
    (state)->V[9] = V11; \
    (state)->V[10] = V12; \
    (state)->V[11] = V13; \
    (state)->V[12] = V14; \
    (state)->V[13] = V15; \
    (state)->V[14] = V16; \
    (state)->V[15] = V17; \
    (state)->V[16] = V20; \
    (state)->V[17] = V21; \
    (state)->V[18] = V22; \
    (state)->V[19] = V23; \
    (state)->V[20] = V24; \
    (state)->V[21] = V25; \
    (state)->V[22] = V26; \
    (state)->V[23] = V27; \
    (state)->V[24] = V30; \
    (state)->V[25] = V31; \
    (state)->V[26] = V32; \
    (state)->V[27] = V33; \
    (state)->V[28] = V34; \
    (state)->V[29] = V35; \
    (state)->V[30] = V36; \
    (state)->V[31] = V37; \
} while(0)

/**
 * Inizializza un contesto Luffa-224.
 *
 * @param cc   il contesto Luffa-224
 */
void sph_luffa224_init(void *cc);

/**
 * Processa alcuni byte di dati.
 *
 * @param cc     il contesto Luffa-224
 * @param data   i dati di input
 * @param len    la lunghezza dei dati di input (in byte)
 */
void sph_luffa224(void *cc, const void *data, size_t len);

/**
 * Termina il calcolo Luffa-224 corrente e restituisce il risultato.
 *
 * @param cc    il contesto Luffa-224
 * @param dst   il buffer di destinazione (deve essere di almeno 28 byte)
 */
void sph_luffa224_close(void *cc, void *dst);

/**
 * Aggiunge alcuni bit addizionali, poi termina il calcolo.
 *
 * @param cc    il contesto Luffa-224
 * @param ub    i bit extra
 * @param n     il numero di bit extra (0 to 7)
 * @param dst   il buffer di destinazione (deve essere di almeno 28 byte)
 */
void sph_luffa224_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Inizializza un contesto Luffa-256.
 */
void sph_luffa256_init(void *cc);

/**
 * Processa dati con Luffa-256.
 */
void sph_luffa256(void *cc, const void *data, size_t len);

/**
 * Termina il calcolo Luffa-256.
 */
void sph_luffa256_close(void *cc, void *dst);

/**
 * Aggiunge bit e termina il calcolo Luffa-256.
 */
void sph_luffa256_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Inizializza un contesto Luffa-384.
 */
void sph_luffa384_init(void *cc);

/**
 * Processa dati con Luffa-384.
 */
void sph_luffa384(void *cc, const void *data, size_t len);

/**
 * Termina il calcolo Luffa-384.
 */
void sph_luffa384_close(void *cc, void *dst);

/**
 * Aggiunge bit e termina il calcolo Luffa-384.
 */
void sph_luffa384_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Inizializza un contesto Luffa-512.
 */
void sph_luffa512_init(void *cc);

/**
 * Processa dati con Luffa-512.
 */
void sph_luffa512(void *cc, const void *data, size_t len);

/**
 * Termina il calcolo Luffa-512.
 */
void sph_luffa512_close(void *cc, void *dst);

/**
 * Aggiunge bit e termina il calcolo Luffa-512.
 */
void sph_luffa512_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

#ifdef __cplusplus
}
#endif

#endif /* SPH_LUFFA_H__ ```
