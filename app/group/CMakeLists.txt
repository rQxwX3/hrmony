add_library(group STATIC src/group.cpp)

target_include_directories(group PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(types)

target_link_libraries(group PUBLIC action)
