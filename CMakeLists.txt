cmake_minimum_required(VERSION 3.20)
project(InfiniteGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找系统自带的 GLEW
find_package(GLEW REQUIRED)
find_package(nlohmann_json REQUIRED)   # header-only，系统或 vcpkg 都有

file(GLOB SOURCES src/*.cpp)
add_library(InfiniteGUI SHARED ${SOURCES})

target_include_directories(InfiniteGUI PRIVATE include)
target_link_libraries(InfiniteGUI
    PRIVATE
        GLEW::GLEW
        nlohmann_json::nlohmann_json
        opengl32        # 系统库
)
