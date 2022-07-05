cmake_minimum_required(VERSION 2.8.12)

project(game CXX C)

set(CMAKE_C_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/builds/cmake)

# src
set (game_src
	src/Tools.cpp
	src/Bitmap.cpp
    src/TN.cpp)

add_library(game_bin ${game_src})

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

IF(LINUX)
	target_link_libraries(game_bin -m64 -lSDL2 -lSDL2main -lopengl32)
ENDIF(LINUX)

IF(MINGW)
	target_link_libraries(game_bin -m64 -lSDL2 -lSDL2main -lopengl32 -lws2_32)
ENDIF(MINGW)

# Apple most likely won't work
IF(APPLE)
	target_link_libraries(game_bin -m64 -lSDL2 -lSDL2main -lopengl32)
ENDIF(APPLE)

add_executable(game src/Game.cpp)
target_link_libraries(game game_bin)