cmake_minimum_required(VERSION 3.2)
SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

## Dependencies ## ====================================================================
find_package( OpenCV REQUIRED )
## ============ ## ====================================================================

project(FLY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

enable_testing()

## Target names ## ===================================
# Fly library
set(FLY_LIB_TARGET Fly)

# Fly demo
set(FLY_DEMO_TARGET FlyDemo)

# Fly test
set(FLY_TEST_TARGET FlyTest)
## =========== ## ===================================


## Fly library Target definition ## ====================================================================
add_library (${FLY_LIB_TARGET}
        include/cloud.hpp include/fly.hpp src/cloud.cpp src/fly.cpp)

target_link_libraries (${FLY_LIB_TARGET}
        ${OpenCV_LIBS})

target_include_directories(${FLY_LIB_TARGET}
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${OpenCV_INCLUDE_DIRS})
## ============ ## ====================================================================

## Add subdirectories ## ============================
add_subdirectory(demo)
add_subdirectory(test)
## =========== ## ===================================

