cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(PROJECT_NAME LPC-Vocoder)
# Folders files
set(CPP_DIR_1 LPC-Vocoder/src)
set(CPP_DIR_3 LPC-Vocoder)
set(HEADER_DIR_1 LPC-Vocoder/src)

project(${PROJECT_NAME} CXX)

include_directories(iksLib ${HEADER_DIR_1} LPC-Vocoder/target)
add_subdirectory(iksLib)

#link_directories(iks)

file(GLOB SRC2_FILES
        ${CPP_DIR_3}/*.cpp
        ${CPP_DIR_3}/*.h
        )

file(GLOB_RECURSE  SRC_FILES
        ${CPP_DIR_1}/*.cpp
        ${HEADER_DIR_1}/*.h
        )

############################# MS01 #############################
# Add executable to build.
add_executable(Milestone1
   ${SRC_FILES} ${SRC2_FILES} "./LPC-Vocoder/target/example.cpp"
)

# Link with other dependencies.
target_link_libraries(Milestone1 iksLib)

############################# MS02 #############################

# Add new executable here.
#add_executable(Milestone2
#   ${SRC_FILES} ${SRC2_FILES} "./LPC-Vocoder/target/myMilestone2.cpp"
#)

# Link with other dependencies.
#target_link_libraries(Milestone2 iksLib)