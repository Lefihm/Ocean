function(globbert OUTPUT_VAR DIR)

    # Parse optional arguments
    set(options RECURSE VERBOSE)
    set(one_value_args GLOBAL_VAR GROUP_PREFIX)

    cmake_parse_arguments(ARG "${options}" "${one_value_args}" "" ${ARGN})

    # Glob the files recursively or in single directory
    if(ARG_RECURSE)

        file(GLOB_RECURSE GLOBBED_HEADERS "${DIR}/*.hpp" "${DIR}/*.h")
        file(GLOB_RECURSE GLOBBED_SOURCES "${DIR}/*.cpp" "${DIR}/*.c")

    else()

        file(GLOB GLOBBED_HEADERS "${DIR}/*.hpp" "${DIR}/*.h")
        file(GLOB GLOBBED_SOURCES "${DIR}/*.cpp" "${DIR}/*.c")

    endif()

    # Set the output variable
    set(GLOBBED_FILES ${GLOBBED_HEADERS} ${GLOBBED_SOURCES})
    set(${OUTPUT_VAR} ${GLOBBED_FILES} PARENT_SCOPE)

    # Verbose output for debugging
    if(ARG_VERBOSE)

        message(STATUS "globert files in \"${DIR}:\"")

        foreach(SOURCE IN LISTS GLOBBED_FILES)

            message(STATUS "\t\t${SOURCE}")

        endforeach()

        message(STATUS)

    endif()

    # Append the files to the global variable if given
    if(ARG_GLOBAL_VAR AND NOT ARG_GLOBAL_VAR STREQUAL "")

        set(${ARG_GLOBAL_VAR} "${${ARG_GLOBAL_VAR}};${GLOBBED_FILES}" PARENT_SCOPE)

    endif()

    # Optional group name prefix
    if(ARG_GROUP_PREFIX)

        set(PREFIX "${ARG_GROUP_PREFIX}\\")

    else()

        set(PREFIX "")

    endif()

    # Group header files
    foreach(FILE_PATH IN LISTS GLOBBED_HEADERS)

        file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE_PATH}")

        get_filename_component(GROUP_PATH "${REL_PATH}" PATH)
        string(REPLACE "/" "\\" GROUP_NAME "${GROUP_PATH}")

        source_group("${PREFIX}\\Header Files\\${GROUP_NAME}" FILES "${FILE_PATH}")

    endforeach()

    # Group source files
    foreach(FILE_PATH IN LISTS GLOBBED_SOURCES)

        file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${FILE_PATH}")

        get_filename_component(GROUP_PATH "${REL_PATH}" PATH)
        string(REPLACE "/" "\\" GROUP_NAME "${GROUP_PATH}")

        source_group("${PREFIX}\\Source Files\\${GROUP_NAME}" FILES "${FILE_PATH}")

    endforeach()

endfunction()
