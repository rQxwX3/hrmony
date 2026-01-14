add_library(macosTypes INTERFACE)

target_include_directories(macosTypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(macosTypes INTERFACE common)
