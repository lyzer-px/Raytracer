add_library(scene STATIC Scene.cpp)

target_include_directories(scene PUBLIC include)

target_link_libraries(scene PUBLIC shapes lights warning_options)
