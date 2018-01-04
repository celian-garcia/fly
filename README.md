# Fly
C++ library of 3D reconstruction.

# Dependencies
- OpenCV
- Boost

# Install
```text
mkdir build
cd build
cmake ..
make
sudo make install
```

Which will result with something like that
```text
-- Install configuration: ""
-- Installing: /usr/local/lib/libFly.so.0.1
-- Installing: /usr/local/lib/libFly.so
-- Installing: /usr/local/include/fly/fly.hpp
-- Installing: /usr/local/include/fly/CloudContainer.hpp
-- Installing: /usr/local/share/pkgconfig/fly.pc
```

With a pc file (/usr/local/share/pkgconfig/fly.pc) like this one :
```text
prefix=/usr/local
exec_prefix=/usr/local
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: fly
Description: C++ library of 3D reconstruction.
Version: 0.1

Requires: opencv
Libs: -L${libdir} -lfly
Cflags: -I${includedir}

```

# Use it in your CMakeLists.txt
Once you have installed the library, you can use it like this in cmake.

```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(Fly REQUIRED fly)
target_link_libraries(MyTarget ${Fly_LIBRARIES})
target_include_directories(MyTarget PRIVATE|PUBLIC ${Fly_INCLUDE_DIRS})
```

`MyTarget` being a target you've already defined.