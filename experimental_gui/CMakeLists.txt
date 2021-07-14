cmake_minimum_required(VERSION 3.16)
project(calc VERSION 0.1)
option(DEBUG "print debug info")
option(USE_UI_FILE "use the ui file instead of integrating it to the executable")
if(DEBUG OR CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_definitions(DEBUG)
endif()
if(USE_UI_FILE)
    add_compile_definitions(USE_UI_FILE)
endif()

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
set(GRESOURCE_C   resources.c)
set(GRESOURCE_XML resources.xml)

add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
        ${GRESOURCE_XML}
        --generate-source
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML}
    DEPENDS
        res/calc.ui
)

add_custom_target(
    resources
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER} -Wall)

add_executable(calc src/main.c ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
    PROPERTIES GENERATED TRUE
)
target_link_libraries(calc ${GTK3_LIBRARIES})
add_dependencies(calc resources)

#create prefix.sh and unset_prefix.sh

install(TARGETS calc
        DESTINATION /usr/local/bin
)
if(USE_UI_FILE)
install(DIRECTORY DESTINATION "/usr/local/share/calc")
install(FILES res/calc.ui
        DESTINATION /usr/local/share/calc/
)
endif()

if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
