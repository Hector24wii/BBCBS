cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# 1. Creamos la librería compartida C++ primero
add_library(IPTNewgroundsBypass SHARED
    src/main.cpp
)

# 2. Enlazamos los componentes del SDK de Geode al target ya existente
setup_geode_mod(IPTNewgroundsBypass)
