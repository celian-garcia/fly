cmake_minimum_required(VERSION 3.6)

project(FLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -std=gnu++11")
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT}/bin")

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME MyTest COMMAND Test)

