# Imposta la versione minima di CMake
cmake_minimum_required(VERSION 3.10)

# Imposta il nome del progetto e specifica il linguaggio C
project(libsph VERSION 1.0 LANGUAGES C)

# Aggiungi la directory 'c/' ai percorsi di ricerca
include_directories(${CMAKE_SOURCE_DIR}/c)

# Definisci il nome della libreria
set(LIBRARY_NAME "libsph")

# Aggiungi i file sorgenti dalla directory 'c/' (rimosso gost.c)
set(SOURCE_FILES
    c/blake.c c/bmw.c c/cubehash.c c/echo.c c/fugue.c c/gost.c c/groestl.c c/hamsi.c c/haval.c
    c/jh.c c/keccak.c c/luffa.c c/md2.c c/md4.c c/md5.c c/panama.c c/radiogatun.c
    c/ripemd.c c/sha0.c c/sha1.c c/sha2.c c/sha2big.c c/shabal.c c/shavite.c c/simd.c c/skein.c
    c/tiger.c c/whirlpool.c
)

# Aggiungi gli header dalla directory 'c/'
set(HEADERS
    c/sph_blake.h c/sph_bmw.h c/sph_cubehash.h c/sph_echo.h c/sph_fugue.h c/sph_groestl.h
    c/sph_gost.h c/sph_hamsi.h c/sph_haval.h c/sph_jh.h c/sph_keccak.h c/sph_luffa.h
    c/sph_md2.h c/sph_md4.h c/sph_md5.h c/sph_panama.h c/sph_radiogatun.h c/sph_ripemd.h
    c/sph_sha0.h c/sph_sha1.h c/sph_sha2.h c/sph_sha3.h c/sph_shabal.h c/sph_shavite.h
    c/sph_simd.h c/sph_skein.h c/sph_tiger.h c/sph_types.h c/sph_whirlpool.h
)

# Crea la libreria condivisa (specifica linguaggio C)
add_library(${LIBRARY_NAME} SHARED)

# Imposta il nome dell'output della libreria senza il prefisso "lib"
set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME "sph")

# Aggiungi esplicitamente i file sorgenti alla libreria
target_sources(${LIBRARY_NAME} PRIVATE ${SOURCE_FILES})

