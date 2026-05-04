add_library(scene STATIC Scene.cpp ConfigParser.cpp)

target_include_directories(scene PUBLIC include)

target_link_libraries(scene PUBLIC shapes utils lights warning_options)
