project(Tempest LANGUAGES CXX)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

add_subdirectory(SDL)

file(GLOB project_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/*.hpp"
)

add_executable (${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE ${project_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)
