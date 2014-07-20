project(enten4)
cmake_minimum_required(VERSION 2.8)

# ------------------------------------------------------------------------------
# Add c++11 features
# Default compiler args
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -Wall -Wextra -Wno-error=sign-compare -std=c++11")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # /Zi - Produces a program database (PDB) that contains type information and symbolic debugging information for use with the debugger.
    # /FS - Allows multiple cl.exe processes to write to the same .pdb file
    # /DEBUG - Enable debug during linking
    # /Od - Disables optimization
#    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /FS /DEBUG /Od /MDd")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /DEBUG /Od /MDd")
    # /Ox - Full optimization
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox -DNDEBUG")
endif()

# include(CheckCXX11Features.cmake)
# include(CheckCXXSourceCompiles)
#
# set(OLD_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
# if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# endif()
# check_cxx_source_compiles(
# "
# #include <memory>
#
# int main() {
#     std::shared_ptr<int>();
# }
# "
# ENTEN4_HAVE_CXX11_STDLIB
# )
#
# if (NOT ENTEN4_HAVE_CXX11_STDLIB)
#     message("-- Not using -stdlib=libc++ (test failed to build)")
#     set(CMAKE_CXX_FLAGS "${OLD_CMAKE_CXX_FLAGS}")
# else ()
#     message("-- Using -stdlib=libc++")
# endif ()
#
# message("${CXX11_FEATURE_LIST}")


# ------------------------------------------------------------------------------

# OpenGL
find_package(OpenGL REQUIRED)

# Add GLM
add_subdirectory(libs/glm)
include_directories(libs/glm)

# Add sdl2
add_subdirectory(libs/sdl2)
include_directories(libs/sdl2/include)

# Take care of GLEW
set(GLEW_SOURCE
    libs/glew/src/glew.c
)

set(GLEW_INCLUDE
    libs/glew/include
)

include_directories(${GLEW_INCLUDE})

add_library(GLEW_110 STATIC
    ${GLEW_SOURCE}
    ${GLEW_INCLUDE}
)

target_link_libraries(GLEW_110
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
)

# Add SOIL
set(SOIL_SRCDIR
	libs/soil/src
)

set(SOIL_SRC
    ${SOIL_SRCDIR}/SOIL.c
	${SOIL_SRCDIR}/image_helper.c
    ${SOIL_SRCDIR}/stb_image_aug.c
    ${SOIL_SRCDIR}/image_DXT.c
)

include_directories(${SOIL_SRCDIR})

add_library(SOIL STATIC
	${SOIL_SRC}
)

target_link_libraries(SOIL
	${OPENGL_LIBRARY}
)

# file(GLOB RESOURCES res)

# Enten4 sources
set(enten4sources
    src/engine.cpp
    src/shaders.cpp
    src/main.cpp
    src/basicshaders.h
    src/basicshapes.h
    src/types.h
    src/mesh.cpp
    src/camera.cpp
)

add_executable(enten4 ${RESOURCES} ${enten4sources})

set(ALL_LIBS
    SDL2-static
    SOIL
    GLEW_110
)

target_link_libraries(enten4 ${ALL_LIBS})
