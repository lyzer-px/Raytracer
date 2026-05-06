add_library(integrators STATIC IIntegrator.cpp
        SimpleIntegrator.cpp
        include/SimpleIntegrator.hpp
        RecursiveIntegrator.cpp
        include/RecursiveIntegrator.hpp)

target_include_directories(integrators PUBLIC include)

target_link_libraries(integrators PUBLIC scene camera warning_options)
