add_library(shapes STATIC IShape.cpp Sphere.cpp)

target_include_directories(shapes PUBLIC include)

target_link_libraries(shapes PUBLIC maths warning_options)
