add_library(lights STATIC ILight.cpp
        AmbientLight.cpp)

target_include_directories(lights PUBLIC include)

target_link_libraries(lights PUBLIC maths warning_options)
