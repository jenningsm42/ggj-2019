cmake_minimum_required(VERSION 3.1)

project(GGJ2019 VERSION 0.1
                DESCRIPTION "Submission for Global Game Jam 2019"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories("src")
file(GLOB source_files "src/*.hpp" "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(TGUI 0.8 REQUIRED)

add_executable(game ${source_files} src/StandardObject.cpp src/StandardObject.hpp)

target_link_libraries(game tgui sfml-system sfml-window sfml-graphics sfml-audio)
