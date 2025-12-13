# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project definition
project(SPH)

# Set default installation directories
set(PREFIX "/usr")
set(INSTALL_BIN "${PREFIX}/bin")
set(INSTALL_LIB "${PREFIX}/lib")
set(INSTALL_INC "${PREFIX}/include")

# Uncomment and modify the flags based on architecture if needed
# set(CMAKE_C_FLAGS "-W -Wall -O1 -fomit-frame-pointer -mtune=athlon-xp -march=athlon-xp")
# set(CMAKE_C_FLAGS "-W -Wall -O1 -fomit-frame-pointer -mtune=athlon64 -march=athlon64")

# Define the shared library output name
set(LIBRARY_NAME "libsph")

# Define the source files
set(SOURCE_FILES
    blake.c bmw.c cubehash.c echo.c fugue.c groestl.c gost.c hamsi.c haval.c
    jh.c keccak.c luffa.c md2.c md4.c md5.c panama.c radiogatun.c ripemd.c sha0.c
    sha1.c sha2.c sha2big.c shabal.c shavite.c simd.c skein.c tiger.c whirlpool.c
)

# Define the header files
set(HEADERS
    sph_blake.h sph_bmw.h sph_cubehash.h sph_echo.h sph_fugue.h sph_groestl.h sph_gost.h
    sph_hamsi.h sph_haval.h sph_jh.h sph_keccak.h sph_luffa.h sph_md2.h sph_md4.h
    sph_md5.h sph_panama.h sph_radiogatun.h sph_ripemd.h sph_sha0.h sph_sha1.h sph_sha2.h
    sph_sha3.h sph_shabal.h sph_shavite.h sph_simd.h sph_skein.h sph_tiger.h sph_types.h
    sph_whirlpool.h
)

# Add the source files to be compiled into object files
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

# Create the shared library
add_library(${LIBRARY_NAME} SHARED ${OBJ_FILES})

# Set the installation rules for the shared library
install(TARGETS ${LIBRARY_NAME} DESTINATION ${INSTALL_LIB})

# Add the installation rules for headers
install(FILES ${HEADERS} DESTINATION ${INSTALL_INC})

# Define the test executables
set(TESTS
    test_types test_blake test_bmw test_cubehash test_echo test_fugue test_groestl test_gost
    test_hamsi test_haval test_jh test_keccak test_luffa test_md2 test_md4 test_md5 test_panama
    test_radiogatun test_ripemd test_sha0 test_sha1 test_sha2 test_sha2big test_shabal test_shavite
    test_simd test_skein test_tiger test_whirlpool
)

# Add test executables
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

# Add the installation rules for test executables
install(TARGETS ${TESTS} DESTINATION ${INSTALL_BIN})

# Define cleaning rule
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/CMakeLists.txt
)

# ==========================================================================
# Additional custom rules for new files like gost.c (if necessary)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gost.o
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${CMAKE_CURRENT_BINARY_DIR}/gost.o ${CMAKE_SOURCE_DIR}/gost.c
    DEPENDS ${CMAKE_SOURCE_DIR}/gost.c
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_gost.o
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${CMAKE_CURRENT_BINARY_DIR}/test_gost.o ${CMAKE_SOURCE_DIR}/test/test_gost.c
    DEPENDS ${CMAKE_SOURCE_DIR}/test/test_gost.c
)
add_library(gost SHARED ${CMAKE_CURRENT_BINARY_DIR}/gost.o)
target_link_libraries(test_gost gost)
