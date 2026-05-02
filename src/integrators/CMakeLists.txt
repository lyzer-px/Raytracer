add_library(integrators STATIC IIntegrator.cpp)

target_include_directories(integrators PUBLIC include)

target_link_libraries(integrators PUBLIC scene camera warning_options)
