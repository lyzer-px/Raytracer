add_library(camera STATIC ICamera.cpp
        PerspectiveCamera.cpp
        Film.cpp
        include/PerspectiveCamera.hpp
include/Film.hpp)

target_include_directories(camera PUBLIC include)

target_link_libraries(camera PUBLIC maths utils warning_options)
