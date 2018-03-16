cmake_minimum_required(VERSION 3.8)

project(myproject)

set(EXECUTABLE_NAME "myproject")
MESSAGE(Building ${EXECUTABLE_NAME})

set(SOURCES "" CACHE INTERNAL "")
set(DIRS "" CACHE INTERNAL "")

add_subdirectory(source)
MESSAGE(SOURCES ${SOURCES})

MESSAGE(DIRS ${DIRS})
include_directories(${DIRS})

add_executable(${EXECUTABLE_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

