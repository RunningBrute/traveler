cmake_minimum_required(VERSION 3.23)

project(traveler)

add_executable(traveler)

target_sources(traveler
  PRIVATE
    src/main.c
)