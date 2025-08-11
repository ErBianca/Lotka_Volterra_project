cmake_minimum_required(VERSION 3.10)
project(LotkaVolterraProject)

# Usa C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trova SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# File sorgente principali
set(SOURCES
    main.cpp
    graphic.cpp
    lotka_volterra.cpp
)

# Aggiungi l'eseguibile principale
add_executable(lotka_volterra_app ${SOURCES})

# Linka SFML
target_link_libraries(lotka_volterra_app sfml-graphics sfml-window sfml-system)

# --------------------------
# Se vuoi compilare i test
# --------------------------
set(TEST_SOURCES
    lotka_volterra_tests.cpp
    graphic.cpp
    lotka_volterra.cpp
)

add_executable(lotka_volterra_tests ${TEST_SOURCES})
target_link_libraries(lotka_volterra_tests sfml-graphics sfml-window sfml-system)


# Copia il font nella cartella di build
configure_file(DejaVuSans.ttf DejaVuSans.ttf COPYONLY)