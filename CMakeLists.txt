cmake_minimum_required(VERSION 3.7)
project(Lem_in)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c libft.h lemin.h)
add_executable(Lem_in ${SOURCE_FILES})
target_link_libraries(Lem_in ${CMAKE_SOURCE_DIR}/libft.a)