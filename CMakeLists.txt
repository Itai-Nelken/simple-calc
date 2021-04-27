cmake_minimum_required(VERSION 3.16)

project(simple-calc VERSION 1.0)

#functions.h
add_library(
	calc
	src/calc.h
	src/calc.c
)

add_executable(simple-calc src/main.c)
target_link_libraries(simple-calc PRIVATE calc)

#install target
install(
	TARGETS simple-calc
	DESTINATION /usr/local/bin
)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
