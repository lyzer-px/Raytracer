add_executable(raytracer core/main.cpp)

target_link_libraries(raytracer PUBLIC maths warning_options)

add_subdirectory(maths)

add_subdirectory(shapes)

add_subdirectory(materials)

add_subdirectory(lights)

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
