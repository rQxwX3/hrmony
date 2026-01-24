add_library(app STATIC src/app.cpp)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(combination)
add_subdirectory(config)
add_subdirectory(group)
add_subdirectory(indexmap)
add_subdirectory(keys)

target_link_libraries(app PUBLIC platform macos combination config group indexmap keys)
