add_library(accelerators STATIC
        BvhAggregate.cpp)

target_include_directories(accelerators PUBLIC include)

target_link_libraries(accelerators PUBLIC shapes warning_options)
