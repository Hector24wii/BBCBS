cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# 1. Crear el target de la librería compartida
add_library(IPTNewgroundsBypass SHARED
    src/main.cpp
)

# 2. Inyectar explícitamente las rutas de encabezados del SDK para Clang
target_include_directories(IPTNewgroundsBypass PRIVATE
    "$ENV{GEODE_SDK}/include"
    "$ENV{GEODE_SDK}/include/Geode"
)

# 3. Vincular las configuraciones y empaquetado de Geode
setup_geode_mod(IPTNewgroundsBypass)
