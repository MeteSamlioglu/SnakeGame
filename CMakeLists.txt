cmake_minimum_required(VERSION 2.8)

project(snake)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/Snake.cpp
            ${PROJECT_SOURCE_DIR}/Game.cpp
            ${PROJECT_SOURCE_DIR}/Move.cpp
            ${PROJECT_SOURCE_DIR}/SnakeObject.cpp
            ${PROJECT_SOURCE_DIR}/main.cpp)
set(PROJECT_HEADERS
            ${PROJECT_SOURCE_DIR}/Coordinates.hpp
            ${PROJECT_SOURCE_DIR}/Directions.hpp
 	    ${PROJECT_SOURCE_DIR}/Snake.hpp
            ${PROJECT_SOURCE_DIR}/SnakeObject.hpp
            ${PROJECT_SOURCE_DIR}/Game.hpp
            ${PROJECT_SOURCE_DIR}/Move.hpp
            )

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Add pthread flag
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)