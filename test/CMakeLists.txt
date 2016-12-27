find_package (Boost COMPONENTS system filesystem unit_test_framework thread REQUIRED)
add_definitions (-DBOOST_TEST_DYN_LINK -DBOOST_THREAD_DYN_LINK)

file(GLOB FLY_TEST_FILES test*.cpp)
include_directories (${FLY_HEADERS} ${Boost_INCLUDE_DIRS})

message(STATUS ${FLY_TEST_NAME})
message(STATUS ${FLY_TEST_FILES})
add_executable (${FLY_TEST_NAME} ${FLY_TEST_FILES})
target_link_libraries (${FLY_TEST_NAME}
        ${FLY_LIB_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_THREAD_LIBRARY})

# Tests Resources
include("${CMAKE_CURRENT_SOURCE_DIR}/BuildTestsResources.cmake")

