add_library(macosTypes STATIC src/macosTypes.cpp)

target_include_directories(macosTypes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(macosTypes PUBLIC common)
