add_library(maths STATIC Color.cpp
        Matrix.cpp
        Normal.cpp
        Point.cpp
        Ray.cpp
        Transform.cpp
        Vector.cpp
        maths.cpp
        Matrix4x4.cpp
        include/Vector3.hpp
        Bounds2.cpp
        Bounds3.cpp)

target_include_directories(maths PUBLIC include)

target_link_libraries(maths PUBLIC warning_options)
