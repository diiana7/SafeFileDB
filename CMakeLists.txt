cmake_minimum_required(VERSION 3.20)

project(SafeFileDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SafeFileDB src/main.cpp src/database.cpp)

target_include_directories(SafeFileDB PRIVATE include)
