cmake_minimum_required(VERSION 3.23)
project(aoc2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(01)
include_directories(02)

add_executable(calories
        01/calories.cpp)

add_executable(rps
        02/rockpaperscissors.cpp)

add_executable(rucksack
        03/rucksack.cpp)
