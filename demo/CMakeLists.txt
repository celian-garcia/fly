if (NOT TARGET ${FLY_DEMO_TARGET})

    add_executable(${FLY_DEMO_TARGET}
            main.cpp)

    target_link_libraries(${FLY_DEMO_TARGET}
            ${FLY_LIB_TARGET})

    get_target_property(FLY_LIB_INCLUDE_DIRS ${FLY_LIB_TARGET} INCLUDE_DIRECTORIES)

    target_include_directories(${FLY_DEMO_TARGET}
            PRIVATE ${FLY_LIB_INCLUDE_DIRS})

    add_dependencies(${FLY_DEMO_TARGET}
            ${FLY_LIB_TARGET})

endif ()