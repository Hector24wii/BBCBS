cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include($ENV{GEODE_SDK}/cmake/GeodeFile.cmake)

project(IPTNewgroundsBypass)

# 1. Declarar la librería del mod
add_library(IPTNewgroundsBypass SHARED
    src/main.cpp
)

# 2. Inyectar todas las rutas de cabeceras de Geode y Cocos2d-x
target_include_directories(IPTNewgroundsBypass PRIVATE
    "$ENV{GEODE_SDK}/loader/include"
    "$ENV{GEODE_SDK}/cocos2d/cocos2dx"
    "$ENV{GEODE_SDK}/cocos2d/cocos2dx/include"
    "$ENV{GEODE_SDK}/cocos2d/cocos2dx/platform"
    "$ENV{GEODE_SDK}/cocos2d/extensions"
)

# 3. Configuración y empaquetado del mod
setup_geode_mod(IPTNewgroundsBypass)
