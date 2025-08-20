cmake_minimum_required(VERSION 3.10)
project(LotkaVolterraProject LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# --------------------------
# Main application
# --------------------------
set(SOURCES
    main.cpp
    graphic.cpp
    lotka_volterra.cpp
)

add_executable(lotka_volterra_app ${SOURCES})
target_link_libraries(lotka_volterra_app PRIVATE sfml-graphics sfml-window sfml-system)

# Copy the font to the build directory (so the app can find it at runtime)
configure_file(DejaVuSans.ttf DejaVuSans.ttf COPYONLY)

# --------------------------
# Tests
# --------------------------
enable_testing()

set(TEST_SOURCES
    lotka_volterra_tests.cpp
    graphic.cpp
    lotka_volterra.cpp
)

add_executable(lotka_volterra_tests ${TEST_SOURCES})
target_link_libraries(lotka_volterra_tests PRIVATE sfml-graphics sfml-window sfml-system)

# Register the test with CTest
add_test(NAME LotkaVolterraTests COMMAND lotka_volterra_tests)
