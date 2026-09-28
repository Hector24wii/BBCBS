cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# 1. Inicializa el SDK de Geode a nivel global (sin pasar argumentos de target)
setup_geode_mod()

# 2. Crea el mod y añade el código fuente (agrega automáticamente los headers y enlaces)
add_geode_mod(
    IPTNewgroundsBypass
    SOURCES
        src/main.cpp
)
