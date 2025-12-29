# Imposta la versione minima di CMake
cmake_minimum_required(VERSION 3.10)

# Imposta il nome del progetto e specifica il linguaggio C
project(libsph VERSION 1.0 LANGUAGES C)

# Definisci il nome della libreria
set(LIBRARY_NAME "libsph")

# Raccogli i sorgenti della libreria ed escludi i file di test e gli eseguibili di supporto
file(GLOB LIBRARY_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/c/*.c")
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX ".*/test_.*\\.c$")
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX ".*/(hsum|speed|utest)\\.c$")
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX ".*/(haval_helper|md_helper)\\.c$")

# Aggiungi gli header dalla directory 'c/' (per IDE)
file(GLOB LIBRARY_HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/c/*.h")
list(FILTER LIBRARY_HEADERS EXCLUDE REGEX ".*/utest\\.h$")

# Crea la libreria condivisa (specifica linguaggio C)
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# Imposta il nome dell'output della libreria senza il prefisso "lib"
set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME "sph")

# Imposta lo standard C e i percorsi di inclusione
set_target_properties(${LIBRARY_NAME} PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES)
target_include_directories(${LIBRARY_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/c")
