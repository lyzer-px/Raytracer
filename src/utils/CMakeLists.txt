add_library(utils STATIC json.cpp)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils PUBLIC warning_options)
