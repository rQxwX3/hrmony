add_library(input STATIC src/process.cpp src/validate.cpp src/transform.cpp src/dispatch.cpp)

target_include_directories(input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(input PUBLIC common)
