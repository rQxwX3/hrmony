cmake_minimum_required(VERSION 3.23...4.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hrmony)

find_library(APPLICATION_SERVICES ApplicationServices)

add_subdirectory(common)
add_subdirectory(app)
add_subdirectory(platform)
add_subdirectory(macos)
add_subdirectory(logger)

add_executable(hrmony main.cpp)

target_link_libraries(hrmony PRIVATE app common logger ${APPLICATION_SERVICES})
