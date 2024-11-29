cmake_minimum_required(VERSION 3.22)
project(test_code)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

FetchContent_GetProperties(raylib)
if(NOT raylib_POPULATED)
    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# exe target
add_executable(test_code main.cpp 
        ui/GUI.cpp 
        ui/GUI.h
        BiomeHelper.cpp
        BiomeHelper.h
        Food.cpp
        Food.h
        Stats.cpp
        Stats.h
        ui/Map.cpp
        ui/Map.h
        NeuralNetwork.cpp
        NeuralNetwork.h
        Organism.cpp
        Organism.h
        Settings.h
        Simulation.cpp
        Simulation.h
        ui/Button.cpp
        ui/Button.h
        ui/UpgradeWindow.cpp
        ui/UpgradeWindow.h
        Genome.cpp
        Genome.h
        ui/TitleScreen.cpp
        ui/TitleScreen.h )

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")