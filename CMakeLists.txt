cmake_minimum_required(VERSION 3.23)

project(traveler)

add_executable(traveler)

target_include_directories(traveler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(traveler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)