message(STATUS "entering in extlib_utf8.cmake")

include(ExternalProject)
include(CMakeParseArguments)

set(UTF8_URL https://github.com/nemtrif/utfcpp.git)
set(UTF8_TAG v4.0.5)

ExternalProject_Add(extlib_utf8
    PREFIX extlib_utf8

    GIT_REPOSITORY ${UTF8_URL}
    GIT_TAG ${UTF8_TAG}

    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""

    BUILD_COMMAND ""
    BUILD_ALWAYS OFF

    INSTALL_DIR     ${EXTERNALS_PREFIX_PATH}
    # Use the correct source directory variable for the copy command
    #INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${extlib_utf8_SOURCE_DIR}/source ${EXTERNALS_PREFIX_PATH}/include/utf8
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${extlib_utf8_SOURCE_DIR} ${EXTERNALS_PREFIX_PATH}/include/utf8

)

# Add utf8 as an interface library (header-only)
add_library(utf8 INTERFACE)

# Ensure extlib_utf8 is built before using utf8
add_custom_target(install_extlib_utf8 DEPENDS extlib_utf8)
add_dependencies(utf8 install_extlib_utf8)
