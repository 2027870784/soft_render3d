set(RENDERER_CORE_SOURCES
    Triangle.cpp
    framebuffer.cpp
    math3d.cpp
    pipeline.cpp
    rasterizer.cpp
)

set(RENDERER_CORE_HEADERS
    Triangle.hpp
    framebuffer.hpp
    math3d.hpp
    mesh.hpp
    pipeline.hpp
    rasterizer.hpp
)

add_library(renderer_core STATIC)

target_sources(renderer_core
    PRIVATE
        ${RENDERER_CORE_SOURCES}
        ${RENDERER_CORE_HEADERS}
)

target_include_directories(renderer_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(renderer_core PUBLIC cxx_std_17)

if(SOFT_RENDER3D_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(renderer_core PRIVATE /W4 /permissive-)
    else()
        target_compile_options(renderer_core PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

add_executable(soft_render3d main.cpp)
target_link_libraries(soft_render3d PRIVATE renderer_core)

if(WIN32)
    target_link_libraries(soft_render3d PRIVATE user32 gdi32)
endif()

set_target_properties(soft_render3d PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES
    ${RENDERER_CORE_SOURCES}
    ${RENDERER_CORE_HEADERS}
    main.cpp
)
