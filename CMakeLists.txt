cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(IPTNewgroundsBypass VERSION 1.0.0)

# Ahorro de memoria RAM en GitHub Actions
set(CMAKE_DISABLE_PRECOMPILED_HEADERS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

# Validar e incluir el Geode SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Cargar funciones y subproyecto completo de Geode
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Buscar automáticamente todos los archivos .cpp en src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Crear la librería del mod
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Configuración del mod
setup_geode_mod(${PROJECT_NAME})
