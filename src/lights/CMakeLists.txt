add_library(lights STATIC ILight.cpp
        AmbientLight.cpp
        DirectionalLight.cpp
        include/DirectionalLight.hpp
        PointLight.cpp
        include/PointLight.hpp
        AreaLight.cpp
        include/AreaLight.hpp)

target_include_directories(lights PUBLIC include)

target_link_libraries(lights PUBLIC maths utils warning_options)
