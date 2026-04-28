add_library(maths STATIC Matrix.cpp Vector.cpp Color.cpp Point.cpp)

target_include_directories(maths PUBLIC include)

target_link_libraries(maths PUBLIC warning_options)
