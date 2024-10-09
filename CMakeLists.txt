cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SensorProject)

# Establecer la carpeta donde se generarán los binarios (ejecutables y bibliotecas)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir el directorio de los archivos .hpp
include_directories(include)

# Crear librerías compartidas para cada clase (compiladas desde src)
add_library(Sensor SHARED src/Sensor.cpp)
add_library(NoiseReduction SHARED src/NoiseReduction.cpp)
add_library(NoiseCreator SHARED src/NoiseCreator.cpp)

# El ejecutable principal
add_executable(main src/main.cpp)

# Enlazar las bibliotecas compartidas con el ejecutable
target_link_libraries(main Sensor NoiseReduction NoiseCreator)
