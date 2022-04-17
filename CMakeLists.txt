cmake_minimum_required(VERSION 3.20)
project(GracefulTooling)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 20)


add_executable(GracefulTooling src/main.cpp
        src/application.cpp src/application.h src/color_definitions.h)

#unfortunately, the subdirectories are having trouble with the include path stuff, so
#just doing a global include for now. Kinda bleh but will fix later.
include_directories(PRIVATE
        src
        libraries/include
        libraries/include/SFML
        libraries/include/imgui
        libraries/include/imgui-sfml
        libraries/include/graph_lite
    )

#where the libraries we build from source are
add_subdirectory(libraries/source/imgui )
add_subdirectory(libraries/source/imgui-sfml )
#link the libraries we build from source
target_link_libraries(GracefulTooling
        dear-imgui
        dear-imgui-sfml
)

#Setting the location of the (shared) libraries for each platform
if (UNIX)
    set(SFML_LIB_LOCATION "/usr/local/lib")
elseif(WIN32)
    if(MINGW)
        message(FATAL_ERROR "Need to specify SFML_LIB_LOCATION  for MINGW under the WIN32 branch, then comment out this message :)")
        set(SFML_LIB_LOCATION ".....")
    elseif(MSVC)
        message(FATAL_ERROR "Need to specify SFML_LIB_LOCATION and DEAR_IMGUI_LOCATION for MSVC under the WIN32 branch, then comment out this message :)")
        set(SFML_LIB_LOCATION ".....")
    else()
        message(FATAL_ERROR "this is a new platform/compiler toolchain :) a little work to be done.")
    endif()
else()
    message(FATAL_ERROR "this is a new platform/compiler toolchain :) a little work to be done.")
endif()



#Finds each shared library, then links each one

find_library(SFML_Audio NAMES libsfml-audio.dylib HINTS ${SFML_LIB_LOCATION})
find_library(SFML_Graphics NAMES libsfml-graphics.dylib HINTS ${SFML_LIB_LOCATION})
find_library(SFML_Network NAMES libsfml-network.dylib HINTS ${SFML_LIB_LOCATION})
find_library(SFML_System NAMES libsfml-system.dylib HINTS ${SFML_LIB_LOCATION})
find_library(SFML_Window NAMES libsfml-window.dylib HINTS ${SFML_LIB_LOCATION})

find_library(DEAR_Imgui NAMES libdear-imgui.dylib HINTS ${DEAR_IMGUI_LOCATION})

list(APPEND Graceful_Tooling_Libraries
        SFML_Audio SFML_Graphics SFML_Network SFML_System SFML_Window
    )

foreach(Library IN LISTS Graceful_Tooling_Libraries)
    message(STATUS "Linking ${${Library}}")
    if(NOT Library)
        message(FATAL_ERROR "${Library} not found")
    else()
        target_link_libraries(GracefulTooling ${${Library}})
    endif()
endforeach()




#Platform specific odds and ends
if(APPLE)
    target_link_libraries( GracefulTooling
            "-F /Library/Frameworks" #This should be in the default search paths but often is not and lacking it causes problems
            "-framework Cocoa"
            "-framework OpenGL"
            "-framework IOKit"
            "-framework CoreVideo"
    )
    target_compile_definitions(
            GracefulTooling PRIVATE
            GL_SILENCE_DEPRECATION=1
            GRACEFUL_CUSTOM_DPI=2.25
    )
elseif(WIN32)
    if(MINGW)
#        maybe link opengl or other necessary libraries for windows?
    endif()
endif()














