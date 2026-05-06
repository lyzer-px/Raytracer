add_library(utils STATIC Serializer.cpp)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils PUBLIC scene camera warning_options)
