add_executable(raytracer main.cpp)

target_include_directories(raytracer PUBLIC include)

target_link_libraries(raytracer PUBLIC scene integrators warning_options)
