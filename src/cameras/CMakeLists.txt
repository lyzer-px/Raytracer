add_library(camera STATIC ICamera.cpp
        include/PerspectiveCamera.cpp
        include/PerspectiveCamera.hpp)

target_include_directories(camera PUBLIC include)

target_link_libraries(camera PUBLIC maths warning_options)
