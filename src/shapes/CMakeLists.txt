add_library(shapes STATIC IShape.cpp Sphere.cpp
        IPrimitive.cpp
        include/IPrimitive.hpp
        GeometricPrimitive.cpp
        include/GeometricPrimitive.hpp
        Plane.cpp
        include/Plane.hpp
        Disk.cpp)

target_include_directories(shapes PUBLIC include)

target_link_libraries(shapes PUBLIC maths materials warning_options)
