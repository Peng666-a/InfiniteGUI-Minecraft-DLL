cmake_minimum_required(VERSION 3.20)
project(InfiniteGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找 vcpkg 提供的依赖
find_package(GLEW CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# stb 头文件-only，vcpkg 已把 include 路径加好

# 把 src 下所有 cpp 编进 DLL
file(GLOB SOURCES src/*.cpp)
add_library(InfiniteGUI SHARED ${SOURCES})

target_include_directories(InfiniteGUI PRIVATE include)
target_link_libraries(InfiniteGUI
    PRIVATE
        GLEW::glew              # 注意是 ::glew 不是 ::GLEW
        nlohmann_json::nlohmann_json
        opengl32                # 系统库
)
