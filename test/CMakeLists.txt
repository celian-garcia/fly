if (NOT TARGET ${FLY_TEST_TARGET})

    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED) # Required for GTest

    get_target_property(FLY_LIB_INCLUDE_DIRS ${FLY_LIB_TARGET} INCLUDE_DIRECTORIES)

    add_executable(${FLY_TEST_TARGET}
            test_main.cpp)

    target_link_libraries(${FLY_TEST_TARGET}
            ${FLY_LIB_TARGET}
            ${CMAKE_THREAD_LIBS_INIT}
            ${GTEST_LIBRARIES})

    target_include_directories(${FLY_TEST_TARGET}
            PRIVATE ${FLY_LIB_INCLUDE_DIRS}
            PRIVATE ${GTest_INCLUDE_DIRS})

    # Tests Resources
    include("${CMAKE_CURRENT_SOURCE_DIR}/BuildTestsResources.cmake")

    add_dependencies(${FLY_TEST_TARGET}
            ${FLY_LIB_TARGET})

endif ()