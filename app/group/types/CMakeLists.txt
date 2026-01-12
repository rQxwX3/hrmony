add_library(action STATIC src/action.cpp)

target_include_directories(action PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(action PUBLIC common)
