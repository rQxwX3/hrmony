add_library(common INTERFACE)

target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(types)
add_subdirectory(combination)

target_link_libraries(common INTERFACE macos types)
