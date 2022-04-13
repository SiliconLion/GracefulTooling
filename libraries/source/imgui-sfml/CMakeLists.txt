cmake_minimum_required(VERSION 3.20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)

add_library(dear-imgui-sfml STATIC)

#target_include_directories(dear-imgui PUBLIC
#        "${CMAKE_SOURCE_DIR}/libraries/include/imgui-sfml"
#        )

target_sources(dear-imgui-sfml PRIVATE
        imgui-SFML.cpp
        )

