add_library(utils STATIC json.cpp Serializer.cpp)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils PUBLIC scene cameras warning_options)
