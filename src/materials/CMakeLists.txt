add_library(materials STATIC IMaterial.cpp
        Lambertian.cpp
        include/Lambertian.hpp
        Metal.cpp
        include/Metal.hpp
        Dielectric.cpp
        include/Dielectric.hpp
        Emissive.cpp
        include/Emissive.hpp)

target_include_directories(materials PUBLIC include)

target_link_libraries(materials PUBLIC maths utils shapes warning_options)
