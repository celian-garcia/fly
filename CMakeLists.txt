cmake_minimum_required(VERSION 3.2)
SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

## Dependencies ## ====================================================================
find_package(OpenCV REQUIRED)
## ============ ## ====================================================================

project(fly VERSION 0.0.1 DESCRIPTION "C++ library of 3D reconstruction.")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(GNUInstallDirs)

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
add_library(${FLY_LIB_TARGET} SHARED
        include/CloudContainer.hpp include/fly.hpp src/CloudContainer.cpp src/fly.cpp)

target_link_libraries(${FLY_LIB_TARGET}
        ${OpenCV_LIBS})

target_include_directories(${FLY_LIB_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${OpenCV_INCLUDE_DIRS})

install(TARGETS ${FLY_LIB_TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES include/fly.hpp include/CloudContainer.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fly)

set_target_properties(${FLY_LIB_TARGET} PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER include/fly.hpp)
## ============ ## ====================================================================

## Add subdirectories ## ============================
add_subdirectory(demo)
add_subdirectory(test)
enable_testing()
add_test(NAME FlyTestRunner COMMAND ${FLY_TEST_TARGET})
## =========== ## ===================================

## Custom target to run install from Clion ## ============================
add_custom_target(install_${FLY_LIB_TARGET}
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
        DEPENDS ${FLY_LIB_TARGET}
        COMMENT "Installing ${FLY_LIB_TARGET}")
## =========== ## ===================================

## pkg_config configuration file ## ============================
CONFIGURE_FILE(fly.pc.in fly.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/fly.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
## =========== ## ===================================

