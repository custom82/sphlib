/* GOST R 34.11-94 implementation for SPHLIB */
#ifndef SPH_GOST_H__
#define SPH_GOST_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
    #endif

    /* SPH GOST context structure */
    typedef struct {
        unsigned char buffer[32];  /* Input buffer */
        unsigned long long count;  /* Total message length in bits */
        unsigned int state[8];     /* Hash state */
        unsigned int sigma[8];     /* Accumulator for message length */
        size_t buf_ptr;            /* Buffer pointer */
    } sph_gost_context;

    /* GOST hash size in bits */
    #define SPH_SIZE_gost 256

    /* Function prototypes */
    void sph_gost_init(void *cc);
    void sph_gost(void *cc, const void *data, size_t len);
    void sph_gost_close(void *cc, void *dst);
    void sph_gost_addbits_and_close(void *cc, unsigned ub, unsigned n, void *dst);

    /* ================ INIZIO MODIFICHE PER COMPATIBILITÀ RAVENCOIN ================ */

    /*
     * Definizione di alias per la compatibilità con il codice esistente.
     * Il tipo `sph_gost512_context` era utilizzato nelle versioni precedenti
     * ed è funzionalmente identico a `sph_gost_context` in questa implementazione.
     */
    typedef sph_gost_context sph_gost512_context;

    /*
     * Dichiarazioni delle funzioni compatibili per GOST-512.
     * Queste funzioni sono wrapper per le funzioni esistenti.
     */
    void sph_gost512_init(void *cc);
    void sph_gost512(void *cc, const void *data, size_t len);
    void sph_gost512_close(void *cc, void *dst);

    /* ================ FINE MODIFICHE PER COMPATIBILITÀ RAVENCOIN ================ */

    #ifdef __cplusplus
}
#endif

#endif /* SPH_GOST_H__ */
