cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

setup_geode_mod(
    NAME IPTNewgroundsBypass
    BUILD_DIR build
)

add_geode_mod(
    IPTNewgroundsBypass
    SOURCES
        src/main.cpp
)
