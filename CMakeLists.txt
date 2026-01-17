cmake_minimum_required(VERSION 3.20)
project(InfiniteGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 让 CMake 自动找到 vcpkg 提供的依赖
find_package(GLEW REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# stb 是头文件-only，vcpkg 已把 include 目录加好

file(GLOB SOURCES src/*.cpp)   # 把你的源码全扫进来
add_library(InfiniteGUI SHARED ${SOURCES})

target_include_directories(InfiniteGUI PRIVATE include)   # 自己有头文件就加这一行
target_link_libraries(InfiniteGUI PRIVATE GLEW::GLEW nlohmann_json::nlohmann_json opengl32)
