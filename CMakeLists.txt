# Imposta la versione minima di CMake
cmake_minimum_required(VERSION 3.10)

# Imposta il nome del progetto
project(libsph VERSION 1.0 LANGUAGES C)

# Definisci le directory di installazione
set(PREFIX "/usr/local")
set(INSTALL_BIN "${PREFIX}/bin")
set(INSTALL_LIB "${PREFIX}/lib")
set(INSTALL_INC "${PREFIX}/include")

# Flags del compilatore
set(CMAKE_C_FLAGS "-W -Wall -O1 -fomit-frame-pointer")

# Aggiungi la directory 'c/' ai percorsi di ricerca
include_directories(${CMAKE_SOURCE_DIR}/c)

# Definisci il nome della libreria
set(LIBRARY_NAME "libsph")

# Aggiungi i file sorgenti dalla directory 'c/'
set(SOURCE_FILES
    c/blake.c c/bmw.c c/cubehash.c c/echo.c c/fugue.c c/groestl.c c/gost.c c/hamsi.c
    c/haval.c c/jh.c c/keccak.c c/luffa.c c/md2.c c/md4.c c/md5.c c/panama.c c/radiogatun.c
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

# Aggiungi i file di oggetti
set(OBJ_FILES)
foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    set(OBJ_FILES ${OBJ_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.o)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.o
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.o ${CMAKE_SOURCE_DIR}/${SOURCE_FILE}
        DEPENDS ${SOURCE_FILE}
    )
endforeach()

# Crea la libreria condivisa
add_library(${LIBRARY_NAME} SHARED ${OBJ_FILES})

# Imposta la regola di installazione per la libreria condivisa
install(TARGETS ${LIBRARY_NAME} DESTINATION ${INSTALL_LIB})

# Aggiungi la regola di installazione per gli header
install(FILES ${HEADERS} DESTINATION ${INSTALL_INC})

# Definisci i test
set(TESTS
    test_types test_blake test_bmw test_cubehash test_echo test_fugue test_groestl test_gost
    test_hamsi test_haval test_jh test_keccak test_luffa test_md2 test_md4 test_md5 test_panama
    test_radiogatun test_ripemd test_sha0 test_sha1 test_sha2 test_sha2big test_shabal test_shavite
    test_simd test_skein test_tiger test_whirlpool
)

# Aggiungi gli eseguibili per i test
foreach(TEST ${TESTS})
    set(TEST_OBJ "${TEST}.o")
    set(TEST_SRC "${TEST}.c")
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TEST_OBJ}
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${TEST_OBJ} ${CMAKE_SOURCE_DIR}/test/${TEST_SRC}
        DEPENDS ${CMAKE_SOURCE_DIR}/test/${TEST_SRC}
    )
    add_executable(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_OBJ})
    target_link_libraries(${TEST} ${LIBRARY_NAME})
endforeach()

# Imposta la regola di installazione per i test
install(TARGETS ${TESTS} DESTINATION ${INSTALL_BIN})

# Definisci una regola di pulizia personalizzata
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/CMakeLists.txt
)

