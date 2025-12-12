/* sph_luffa_raven.h - Versione compatibile con Ravencoin luffa.c */
#ifndef SPH_LUFFA_RAVEN_H__
#define SPH_LUFFA_RAVEN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Includi l'header di sistema per le funzioni di utilità */
#include "sph_types.h"

#define SPH_SIZE_luffa224   224
#define SPH_SIZE_luffa256   256
#define SPH_SIZE_luffa384   384
#define SPH_SIZE_luffa512   512

/* Struttura modificata per luffa.c di Ravencoin */
typedef struct {
#ifndef DOXYGEN_IGNORE
    unsigned char buf[32];
    size_t ptr;
    uint32_t V[32];           /* MODIFICATO: Array lineare di 32 elementi */
#endif
} sph_luffa224_context;

typedef sph_luffa224_context sph_luffa256_context;
typedef sph_luffa224_context sph_luffa384_context;
typedef sph_luffa224_context sph_luffa512_context;

/* 1. PROTEGGI la definizione di SPH_C32 per evitare conflitti */
#ifndef SPH_C32
#define SPH_C32(x)    ((uint32_t)(x))
#endif

/* 2. RINOMINA le macro con un prefisso specifico (es. RAVEN_) */
/* Macro per dichiarare tutte le variabili Vxx */
#define RAVEN_DECLARE_VARS \
    uint32_t V00, V01, V02, V03, V04, V05, V06, V07; \
    uint32_t V10, V11, V12, V13, V14, V15, V16, V17; \
    uint32_t V20, V21, V22, V23, V24, V25, V26, V27; \
    uint32_t V30, V31, V32, V33, V34, V35, V36, V37;

/* Macro per leggere lo stato */
#define RAVEN_READ_STATE(state) \
    V00 = (state)->V[0];  V01 = (state)->V[1];  V02 = (state)->V[2];  V03 = (state)->V[3]; \
    V04 = (state)->V[4];  V05 = (state)->V[5];  V06 = (state)->V[6];  V07 = (state)->V[7]; \
    V10 = (state)->V[8];  V11 = (state)->V[9];  V12 = (state)->V[10]; V13 = (state)->V[11]; \
    V14 = (state)->V[12]; V15 = (state)->V[13]; V16 = (state)->V[14]; V17 = (state)->V[15]; \
    V20 = (state)->V[16]; V21 = (state)->V[17]; V22 = (state)->V[18]; V23 = (state)->V[19]; \
    V24 = (state)->V[20]; V25 = (state)->V[21]; V26 = (state)->V[22]; V27 = (state)->V[23]; \
    V30 = (state)->V[24]; V31 = (state)->V[25]; V32 = (state)->V[26]; V33 = (state)->V[27]; \
    V34 = (state)->V[28]; V35 = (state)->V[29]; V36 = (state)->V[30]; V37 = (state)->V[31]

/* Macro per scrivere lo stato */
#define RAVEN_WRITE_STATE(state) \
    (state)->V[0] = V00;  (state)->V[1] = V01;  (state)->V[2] = V02;  (state)->V[3] = V03; \
    (state)->V[4] = V04;  (state)->V[5] = V05;  (state)->V[6] = V06;  (state)->V[7] = V07; \
    (state)->V[8] = V10;  (state)->V[9] = V11;  (state)->V[10] = V12; (state)->V[11] = V13; \
    (state)->V[12] = V14; (state)->V[13] = V15; (state)->V[14] = V16; (state)->V[15] = V17; \
    (state)->V[16] = V20; (state)->V[17] = V21; (state)->V[18] = V22; (state)->V[19] = V23; \
    (state)->V[20] = V24; (state)->V[21] = V25; (state)->V[22] = V26; (state)->V[23] = V27; \
    (state)->V[24] = V30; (state)->V[25] = V31; (state)->V[26] = V32; (state)->V[27] = V33; \
    (state)->V[28] = V34; (state)->V[29] = V35; (state)->V[30] = V36; (state)->V[31] = V37

/* 3. VERIFICA/fornisci le funzioni di utilità mancanti */
/* Se le funzioni non sono definite in sph_types.h, forniscile qui */
#ifndef sph_dec32le_aligned
/* Implementazione di fallback o errore di compilazione controllato */
#error "sph_dec32le_aligned non definita. Verifica la tua versione di sph_types.h"
#endif

#ifndef sph_enc32le
#error "sph_enc32le non definita. Verifica la tua versione di sph_types.h"
#endif

/* Alias per i nomi usati nel codice Ravencoin (se necessario) */
#define dec32le_aligned sph_dec32le_aligned
#define enc32le sph_enc32le

/* Prototipi delle funzioni (rimangono invariati) */
void sph_luffa224_init(void *cc);
void sph_luffa224(void *cc, const void *data, size_t len);
void sph_luffa224_close(void *cc, void *dst);
void sph_luffa224_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

void sph_luffa256_init(void *cc);
void sph_luffa256(void *cc, const void *data, size_t len);
void sph_luffa256_close(void *cc, void *dst);
void sph_luffa256_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

void sph_luffa384_init(void *cc);
void sph_luffa384(void *cc, const void *data, size_t len);
void sph_luffa384_close(void *cc, void *dst);
void sph_luffa384_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

void sph_luffa512_init(void *cc);
void sph_luffa512(void *cc, const void *data, size_t len);
void sph_luffa512_close(void *cc, void *dst);
void sph_luffa512_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

#ifdef __cplusplus
}
#endif

#endif /* SPH_LUFFA_RAVEN_H__ */
