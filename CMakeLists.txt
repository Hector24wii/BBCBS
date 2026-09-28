cmake_minimum_required(VERSION 3.13)

# Define el nombre del proyecto
project(IPTNewgroundsBypass)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carga el SDK de Geode completo (macros de CMake + librerías C++ y headers)
find_package(Geode REQUIRED HINTS $ENV{GEODE_SDK})

# Crea la librería con tu código fuente
add_library(${PROJECT_NAME} SHARED 
    src/main.cpp
)

# Configura y empaqueta el mod en formato .geode
setup_geode_mod(${PROJECT_NAME})
