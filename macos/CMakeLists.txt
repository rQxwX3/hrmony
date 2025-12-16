add_library(macos STATIC src/macos.cpp)

target_include_directories(macos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(macos PUBLIC common platform)
