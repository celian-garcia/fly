cmake_minimum_required(VERSION 3.6)
find_package( OpenCV REQUIRED )

project(FLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=gnu++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Fly library variables
set(FLY_LIB_NAME Fly)
file(GLOB FLY_SOURCES src/*.cpp)
file(GLOB FLY_HEADERS include/*.h)

# Fly demo variables
set(FLY_DEMO_NAME FlyDemo)
set(DEMO_MAIN demo/main.cpp)

# Fly test variables
set(FLY_TEST_NAME FlyTest)
set(FLY_TEST_DIR test)

# Fly library definition
include_directories(include)
add_library (${FLY_LIB_NAME} ${FLY_SOURCES} ${FLY_HEADERS})
target_link_libraries (${FLY_LIB_NAME} ${OpenCV_LIBS})

# Fly demot definition
add_executable (${FLY_DEMO_NAME} ${DEMO_MAIN})
target_link_libraries (${FLY_DEMO_NAME} ${FLY_LIB_NAME})

# Fly test definition
add_subdirectory(${FLY_TEST_DIR})
enable_testing()
add_test(NAME MyTest COMMAND Test)

