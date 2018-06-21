# Libraries:

link_libraries (gcc)

set (hwlib ${build_environment}/libraries/hwlib)
include_directories (${hwlib}/library)

set (catch ${build_environment}/libraries/Catch2)
include_directories (${catch}/single_include)

# Source Files:

set (sources
    src/libc-stub.cpp
    src/mpu9250_interface.cpp
    src/navigation_engine.cpp
    src/navigation_path.cpp
    src/path.cpp
    src/vector2f.cpp
    src/wrap-hwlib.cpp

)
