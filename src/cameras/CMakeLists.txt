add_library(camera STATIC ICamera.cpp)

target_include_directories(camera PUBLIC include)

target_link_libraries(camera PUBLIC maths warning_options)
