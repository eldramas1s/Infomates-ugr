cmake_minimum_required(VERSION 3.26)
project(Practica_Set_Map)

set(CMAKE_CXX_STANDARD 14)

include_directories(Dictionary/include)

add_executable(Practica_Set_Map
        Dictionary/src/main.cpp
        Dictionary/src/Dictionary.cpp
        Dictionary/include/Dictionary.h
        Dictionary/src/Dictionary_multi.cpp
        Dictionary/include/Dictionary_multi.h
        Guia_tlf/src/Guia_tlf.cpp
        Guia_tlf/include/Guia_tlf.h
)
