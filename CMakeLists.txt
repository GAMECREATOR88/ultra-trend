cmake_minimum_required(VERSION 3.16)

project(ultra_trend VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

add_executable(ultra_trend src/main.cpp)

target_link_libraries(ultra_trend PRIVATE sfml-graphics sfml-window sfml-system)
