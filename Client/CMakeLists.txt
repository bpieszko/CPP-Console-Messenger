cmake_minimum_required(VERSION 3.13.3)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)
find_package(Boost 1.68.0 REQUIRED COMPONENTS system filesystem thread)

include_directories(include include/resolvers ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB SOURCES source/*.cpp source/resolvers/*.cpp)

add_executable(Client ${SOURCES})
target_include_directories(Client PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Client ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
