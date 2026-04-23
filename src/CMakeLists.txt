add_executable(raytracer core/main.cpp)

target_link_libraries(raytracer PUBLIC warning_options)

add_subdirectory(maths)

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})