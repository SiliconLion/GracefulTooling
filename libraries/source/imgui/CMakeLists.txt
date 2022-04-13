cmake_minimum_required(VERSION 3.20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)

add_library(dear-imgui STATIC
        imgui.cpp
        imgui_tables.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
)

#target_include_directories(dear-imgui PRIVATE
#        "${CMAKE_SOURCE_DIR}/libraries/include/imgui"
#)
