add_library(app STATIC src/app.cpp)

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(group)

target_link_libraries(app PUBLIC platform macos common combination)
