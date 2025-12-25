add_library(types STATIC src/types.cpp)

target_include_directories(types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(types PUBLIC common)
