if (NOT TARGET ${FLY_TEST_TARGET})

    find_package(Boost COMPONENTS system filesystem unit_test_framework thread REQUIRED)
    add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_THREAD_DYN_LINK)

    get_target_property(FLY_LIB_INCLUDE_DIRS ${FLY_LIB_TARGET} INCLUDE_DIRECTORIES)

    add_executable(${FLY_TEST_TARGET}
            test_main.cpp)

    target_link_libraries(${FLY_TEST_TARGET}
            ${FLY_LIB_TARGET}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            ${Boost_THREAD_LIBRARY})

    target_include_directories(${FLY_TEST_TARGET}
            PRIVATE ${FLY_LIB_INCLUDE_DIRS}
            PRIVATE ${Boost_INCLUDE_DIRS})

    # Tests Resources
    include("${CMAKE_CURRENT_SOURCE_DIR}/BuildTestsResources.cmake")

    add_dependencies(${FLY_TEST_TARGET}
            ${FLY_LIB_TARGET})

endif ()