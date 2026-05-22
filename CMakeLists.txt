cmake_minimum_required(VERSION 3.23)

project(traveler LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_library(traveler_lib)
target_sources(traveler_lib PRIVATE src/Grid.c src/Cell.c src/Solver.c)
target_include_directories(traveler_lib PUBLIC include)

add_executable(traveler)
target_sources(traveler PRIVATE src/main.c)
target_link_libraries(traveler PRIVATE traveler_lib)
target_compile_options(traveler PRIVATE -fsanitize=address -g)
target_link_options(traveler PRIVATE -fsanitize=address)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests)
target_sources(tests PRIVATE tests/tests.cpp)
target_link_libraries(tests PRIVATE traveler_lib Catch2::Catch2WithMain)
target_compile_options(tests PRIVATE -fsanitize=address -g)
target_link_options(tests PRIVATE -fsanitize=address)

include(CTest)
include(Catch)

catch_discover_tests(tests)