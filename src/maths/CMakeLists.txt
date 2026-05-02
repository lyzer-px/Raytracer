add_library(maths STATIC Color.cpp
        Matrix.cpp
        Normal.cpp
        Point.cpp
        Ray.cpp
        Transform.cpp
        TransformationMatrices.cpp
        Vector.cpp
        include/Vector3.hpp)

target_include_directories(maths PUBLIC include)

target_link_libraries(maths PUBLIC warning_options)
