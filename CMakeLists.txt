# This is the CMake definition file for SimuFaith usage.

cmake_minimum_required(VERSION 2.8)

set(PACKAGE simufaith)

# Set Version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

if(${VERSION_PATCH})
   set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
else(${VERSION_PATCH})
   set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
endif(${VERSION_PATCH})

# Set directories
set(DATADIR ${CMAKE_INSTALL_PREFIX}/share)
set(LOCALEDIR ${CMAKE_INSTALL_PREFIX}/share/locale)
set(LOCALE_DIR share/locale)
set(INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)

set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./CMakeFiles)

project(simufaith)

# Define some options
option(SIMUFAITH_DEBUG "Enable debug symbols" FALSE)
option(SIMUFAITH_COMPILE_TESTS "Build SimuFaith unit tests" TRUE)

# Some compiler options
if(${SIMUFAITH_DEBUG})
   add_definitions(-Wall -g)
else(${SIMUFAITH_DEBUG})
   add_definitions(-Wall)
endif(${SIMUFAITH_DEBUG})


# First, try to find required libraries

FIND_PACKAGE(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIR})

FIND_PACKAGE(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

FIND_PACKAGE(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

FIND_PACKAGE(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIR})

FIND_PACKAGE(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

FIND_PACKAGE(Ogg REQUIRED)
include_directories(${OGG_INCLUDE_DIR})

FIND_PACKAGE(Vorbis REQUIRED)
include_directories(${VORBIS_INCLUDE_DIR})

FIND_PACKAGE(Vorbisfile REQUIRED)
include_directories(${VORBISFILE_INCLUDE_DIR})

FIND_PACKAGE(Kobold REQUIRED)
include_directories(${KOBOLD_INCLUDE_DIR})

FIND_PACKAGE(Kosound REQUIRED)
include_directories(${KOSOUND_INCLUDE_DIR})

FIND_PACKAGE(Goblin REQUIRED)
include_directories(${GOBLIN_INCLUDE_DIR})

FIND_PACKAGE(Farso REQUIRED)
include_directories(${FARSO_INCLUDE_DIR})

FIND_PACKAGE(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# include the ./src as default too, and the generated src too.
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

# Set generated files
set(GOBLIN_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/src/config.h)
configure_file("./src/config.h.in" "./src/config.h")

# Include the sources
include(sources.cmake)

# Make Libraries
add_library(simlib ${SIM_LIB_SOURCES} ${SIM_LIB_HEADERS})
add_library(uilib ${UI_LIB_SOURCES} ${UI_LIB_HEADERS})
add_library(corelib ${CORE_LIB_SOURCES} ${CORE_LIB_HEADERS})

# Make Binaries
add_executable(simufaith WIN32 ${SIMUFAITH_SOURCES} ${SIMUFAITH_HEADERS} )
target_link_libraries(simufaith simlib uilib corelib
                      ${OPENGL_LIBRARY}
                      ${FARSO_LIBRARY}
                      ${GOBLIN_LIBRARY} ${KOSOUND_LIBRARY} ${KOBOLD_LIBRARY}
                      ${OGRE_LIBRARIES} 
                      ${OGRE_RTShaderSystem_LIBRARIES}
                      ${OGRE_Overlay_LIBRARIES} 
                      ${SDL2_IMAGE_LIBRARY} ${SDL2_LIBRARY} 
                      ${FREETYPE_LIBRARY}
                      ${OPENAL_LIBRARY} 
                      ${VORBISFILE_LIBRARY} ${VORBIS_LIBRARY}
                      ${OGG_LIBRARY} m
                      ${LIBINTL_LIBRARIES} pthread)

if(${SIMUFAITH_COMPILE_TESTS})
   add_executable(runtests WIN32 ${TEST_SOURCES} ${TEST_HEADERS} )
   target_link_libraries(runtests  simlib uilib corelib
      ${OPENGL_LIBRARY}
      ${FARSO_LIBRARY}
      ${GOBLIN_LIBRARY}
      ${KOSOUND_LIBRARY}
      ${KOBOLD_LIBRARY}
      ${OGRE_LIBRARIES} 
      ${OGRE_RTShaderSystem_LIBRARIES}
      ${OGRE_Overlay_LIBRARIES} 
      ${SDL2_IMAGE_LIBRARY}
      ${SDL2_LIBRARY} 
      ${FREETYPE_LIBRARY}
      ${OPENAL_LIBRARY} 
      ${VORBISFILE_LIBRARY}
      ${VORBIS_LIBRARY}
      ${OGG_LIBRARY}
      m
      ${LIBINTL_LIBRARIES}
      pthread)
endif(${SIMUFAITH_COMPILE_TESTS})


