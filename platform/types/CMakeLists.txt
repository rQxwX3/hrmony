add_library(platformTypes INTERFACE)

target_include_directories(platformTypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(platformTypes INTERFACE common)
