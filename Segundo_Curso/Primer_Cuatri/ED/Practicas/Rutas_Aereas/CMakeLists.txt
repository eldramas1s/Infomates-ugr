cmake_minimum_required(VERSION 3.16)
project(practicafinal)

set(CMAKE_CXX_STANDARD 14)
set(BASE_FOLDER rutas_aereas)

include_directories(${BASE_FOLDER}/include)

add_library(image ${BASE_FOLDER}/src/Imagen.cpp  ${BASE_FOLDER}/src/imagenES.cpp
        rutas_aereas/src/Punto.cpp
        rutas_aereas/include/Punto.h
        rutas_aereas/src/Ruta.cpp
        rutas_aereas/include/Ruta.h
        rutas_aereas/src/Almacen.cpp
        rutas_aereas/include/Almacen.h
        rutas_aereas/src/Imagen.cpp
        rutas_aereas/include/Imagen.h
        rutas_aereas/src/Pais.cpp
        rutas_aereas/include/Pais.h
        rutas_aereas/src/Mundo.cpp
        rutas_aereas/include/Mundo.h)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pruebarotacion.cpp)
add_executable(pruebarotacion ${BASE_FOLDER}/src/pruebarotacion.cpp
        rutas_aereas/src/Punto.cpp
        rutas_aereas/include/Punto.h
        rutas_aereas/src/Ruta.cpp
        rutas_aereas/include/Ruta.h
        rutas_aereas/src/Almacen.cpp
        rutas_aereas/include/Almacen.h
        rutas_aereas/src/Imagen.cpp
        rutas_aereas/include/Imagen.h
        rutas_aereas/src/Pais.cpp
        rutas_aereas/include/Pais.h
        rutas_aereas/src/Mundo.cpp
        rutas_aereas/include/Mundo.h)
target_link_libraries(pruebarotacion LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pruebapegado.cpp)
add_executable(pruebapegado ${BASE_FOLDER}/src/pruebapegado.cpp
        rutas_aereas/src/Punto.cpp
        rutas_aereas/include/Punto.h
        rutas_aereas/src/Ruta.cpp
        rutas_aereas/include/Ruta.h
        rutas_aereas/src/Almacen.cpp
        rutas_aereas/include/Almacen.h
        rutas_aereas/src/Imagen.cpp
        rutas_aereas/include/Imagen.h
        rutas_aereas/src/Pais.cpp
        rutas_aereas/include/Pais.h
        rutas_aereas/src/Mundo.cpp
        rutas_aereas/include/Mundo.h)
target_link_libraries(pruebapegado LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/ruta_aerea.cpp)
add_executable(ruta_aerea ${BASE_FOLDER}/src/ruta_aerea.cpp
        rutas_aereas/src/Punto.cpp
        rutas_aereas/include/Punto.h
        rutas_aereas/src/Ruta.cpp
        rutas_aereas/include/Ruta.h
        rutas_aereas/src/Almacen.cpp
        rutas_aereas/include/Almacen.h
        rutas_aereas/src/Imagen.cpp
        rutas_aereas/include/Imagen.h
        rutas_aereas/src/Pais.cpp
        rutas_aereas/include/Pais.h
        rutas_aereas/src/Mundo.cpp
        rutas_aereas/include/Mundo.h
        rutas_aereas/src/ruta_aerea.cpp
)
target_link_libraries(ruta_aerea LINK_PUBLIC image)
endif()

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
