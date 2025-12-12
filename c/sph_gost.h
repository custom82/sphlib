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

#ifdef __cplusplus
}
#endif

#endif /* SPH_GOST_H__ */
