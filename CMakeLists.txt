cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####

add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

## tile loader library ##
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## Math library ##
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

set_target_properties(PRACTICAL_1 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_dependencies(PRACTICAL_1 copy_resources)

## Space invaders ##
file(GLOB_RECURSE SOURCES space_invaders/*.cpp space_invaders/*.h)
add_executable(SPACE_INVADERS ${SOURCES} )
target_include_directories(SPACE_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(SPACE_INVADERS sfml-graphics)

set_target_properties(SPACE_INVADERS
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_dependencies(SPACE_INVADERS copy_resources)

## Tile Engine ##
file(GLOB_RECURSE SOURCES tile_engine/*.cpp tile_engine/*.h)
add_executable(TILE_ENGINE ${SOURCES} )
target_include_directories(TILE_ENGINE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(TILE_ENGINE lib_tile_level_loader lib_maths sfml-graphics)

set_target_properties(TILE_ENGINE
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_dependencies(TILE_ENGINE copy_resources)

## Pacman ##
file(GLOB_RECURSE SOURCES pacman/*.cpp pacman/*.h)
add_executable(PACMAN ${SOURCES} )
target_include_directories(PACMAN SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PACMAN lib_tile_level_loader lib_maths sfml-graphics)

set_target_properties(PACMAN
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_dependencies(PACMAN copy_resources)