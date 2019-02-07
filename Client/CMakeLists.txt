cmake_minimum_required(VERSION 3.5.1)
project(CPP-Console-Messenger)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)

include_directories(include)

file(GLOB SOURCES source/*.cpp)

add_executable(CPP-Console-Messenger ${SOURCES})
target_link_libraries(CPP-Console-Messenger ${CMAKE_THREAD_LIBS_INIT})