add_library(materials STATIC IMaterial.cpp)

target_include_directories(materials PUBLIC include)

target_link_libraries(materials PUBLIC maths shapes warning_options)
