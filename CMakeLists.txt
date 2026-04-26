cmake_minimum_required(VERSION 3.20)

project(soft_render3d
    VERSION 0.1.0
    DESCRIPTION "A simple software 3D renderer"
    LANGUAGES CXX
)

option(SOFT_RENDER3D_ENABLE_WARNINGS "Enable extra compiler warnings" ON)

add_subdirectory(renderer)
