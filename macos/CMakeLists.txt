add_library(macos STATIC src/macos.cpp)

target_include_directories(macos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(utility)
add_subdirectory(types)

target_link_libraries(macos PUBLIC common platform utility combination)
