find_package( OpenCV REQUIRED )
add_library (Fly
    fly.cpp
    fly.h
    main.cpp)

target_link_libraries (Fly
        ${OpenCV_LIBS})

add_executable (demo main.cpp)
target_link_libraries (demo Fly)
