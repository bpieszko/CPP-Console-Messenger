cmake_minimum_required(VERSION 3.13.3)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)
find_package(Boost 1.68.0 REQUIRED COMPONENTS system filesystem thread)

include_directories(include ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB SOURCES source/*.cpp)

add_executable(Server ${SOURCES})
target_include_directories(Server PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})