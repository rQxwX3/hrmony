cmake_minimum_required(VERSION 3.23...4.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hrmony)

add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_SOURCE_DIR}/common)

add_subdirectory(app)
add_subdirectory(platform)
add_subdirectory(macos)

add_executable(hrmony main.cpp)

target_link_libraries(hrmony PRIVATE app common)
