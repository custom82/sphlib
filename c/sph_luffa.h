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

#endif /* SPH_LUFFA_H__ */
