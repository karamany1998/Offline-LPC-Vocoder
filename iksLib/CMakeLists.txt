cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(PROJECT_NAME iksLib)
# Folders files
set(CPP_DIR_1 ./)
set(HEADER_DIR_1 ./)

project(${PROJECT_NAME} C)

file(GLOB SRC_FILES
    ${CPP_DIR_1}/*.c
    ${HEADER_DIR_1}/*.h
)

# Add library to build.
add_library(${PROJECT_NAME} STATIC
   ${SRC_FILES}
)
