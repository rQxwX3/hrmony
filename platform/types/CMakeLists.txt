add_library(platformTypes STATIC src/platformTypes.cpp)

target_include_directories(platformTypes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(platformTypes PUBLIC common)
