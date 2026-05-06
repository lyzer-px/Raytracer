add_library(scene STATIC Scene.cpp SceneBuilder.cpp)

target_include_directories(scene PUBLIC include)

target_link_libraries(scene PUBLIC shapes camera design_pattern utils lights warning_options)
