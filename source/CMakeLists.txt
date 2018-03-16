set(DIRS ${DIRS} ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(SOURCES ${SOURCES}
${CMAKE_CURRENT_SOURCE_DIR}/ghost.cpp
${CMAKE_CURRENT_SOURCE_DIR}/ghost.h
CACHE INTERNAL ""
)

add_subdirectory(stb)
add_subdirectory(imgui)
IF (WIN32)
	add_subdirectory(windows)
ELSE()
  message( FATAL_ERROR "Unhandled platform" )
ENDIF()

