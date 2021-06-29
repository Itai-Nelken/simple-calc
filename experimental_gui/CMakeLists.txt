cmake_minimum_required(VERSION 3.16)
project(calc VERSION 0.1)
option(DEBUG "print debug info")
if(DEBUG OR CMAKE_BUILD_TYPE STREQUAL Debug)
        add_compile_definitions(DEBUG)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER} -Wall)

add_executable(calc src/main.c)
target_link_libraries(calc ${GTK3_LIBRARIES})

#create prefix.sh and unset_prefix.sh

install(TARGETS calc
        DESTINATION /usr/local/bin
)
install(DIRECTORY DESTINATION "/usr/local/share/calc")
install(FILES res/calc.ui
        DESTINATION /usr/local/share/calc/
)

if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
