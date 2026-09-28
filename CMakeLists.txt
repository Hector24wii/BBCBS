cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descargar las cabeceras y binarios precompilados del SDK (Cocos2d, Geode.hpp, etc.)
execute_process(COMMAND geode sdk install-binaries)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# Declarar la librería compartida
add_library(IPTNewgroundsBypass SHARED
    src/main.cpp
)

# Configurar y vincular el mod a Geode
setup_geode_mod(IPTNewgroundsBypass)
