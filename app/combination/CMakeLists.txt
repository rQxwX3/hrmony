add_library(combination STATIC src/combination.cpp)

target_include_directories(combination PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(combination PUBLIC app)
