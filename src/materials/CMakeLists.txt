add_library(materials STATIC IMaterial.cpp
        FlatColor.cpp
        include/FlatColor.hpp)

target_include_directories(materials PUBLIC include)

target_link_libraries(materials PUBLIC maths shapes warning_options)
