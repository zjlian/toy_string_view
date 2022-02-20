cmake_minimum_required(VERSION 3.15.0)
project(toy-string-view VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(${PROJECT_NAME} INTERFACE)
add_library(toy::string_view ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE include/)

add_executable(test test.cpp)
target_link_libraries(test toy::string_view)