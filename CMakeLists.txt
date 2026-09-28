cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# 1. Declarar el target de la librería
add_library(IPTNewgroundsBypass SHARED
    src/main.cpp
)

# 2. Apuntar a la carpeta correcta de encabezados del SDK
target_include_directories(IPTNewgroundsBypass PRIVATE
    "$ENV{GEODE_SDK}/loader/include"
)

# 3. Empaquetar y configurar el mod
setup_geode_mod(IPTNewgroundsBypass)
