add_library(groupTypes STATIC src/groupTypes.cpp)

target_include_directories(groupTypes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(groupTypes PUBLIC common)
