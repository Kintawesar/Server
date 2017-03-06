project(server)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Woverloaded-virtual -Wunreachable-code -pedantic -lrt -pthread")


set(Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)

find_package (Boost COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


