add_executable(raytracer core/main.cpp)

target_link_libraries(raytracer PUBLIC maths warning_options)

add_subdirectory(maths)

add_subdirectory(shapes)

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
