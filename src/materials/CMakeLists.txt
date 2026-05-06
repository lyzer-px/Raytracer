add_library(materials STATIC IMaterial.cpp
        Lambertian.cpp
        include/Lambertian.hpp
        Metal.cpp
        include/Metal.hpp
        Dielectric.cpp
        include/Dielectric.hpp)

target_include_directories(materials PUBLIC include)

target_link_libraries(materials PUBLIC maths shapes warning_options)
