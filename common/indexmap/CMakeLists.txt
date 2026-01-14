add_library(indexmap INTERFACE)

target_include_directories(indexmap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(indexmap INTERFACE common)
