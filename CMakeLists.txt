cmake_minimum_required(VERSION 3.29.3)
project(opengl-tutorial VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(opengl-tutorial main.cpp glad.c)
target_include_directories(opengl-tutorial PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(opengl-tutorial PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(opengl-tutorial glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
