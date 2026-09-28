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

# Ahorro de RAM en CI/CD: Desactivar PCH global y optimizaciones pesadas
set(CMAKE_DISABLE_PRECOMPILED_HEADERS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO OFF)

# Validar e incluir el Geode SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Cargar las funciones, dependencias de Cocos2d y macros del SDK de Geode como subproyecto completo
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Buscar automáticamente todos los archivos fuente en src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Crear la librería compartida del mod
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Configuración de propiedades para evitar consumo excesivo de recursos
set_target_properties(${PROJECT_NAME} PROPERTIES 
    DISABLE_PRECOMPILED_HEADERS ON
    UNITY_BUILD OFF
)

# Configurar y empaquetar el mod con Geode
setup_geode_mod(${PROJECT_NAME})
