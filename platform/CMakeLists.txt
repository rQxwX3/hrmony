add_library(platform STATIC src/platform.cpp) 

add_subdirectory(types)

target_include_directories(platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(platform PUBLIC app)
