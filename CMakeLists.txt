cmake_minimum_required(VERSION 3.14)
project(byplayer_cp_library VERSION 1.0.0 LANGUAGES CXX)

# Set default C++ standard if not specified
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOC "Build documentation" OFF)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ac-library
)

if(BUILD_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message("Doxygen not found, cannot build documentation")
    endif()
endif()

if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test/unittest)

    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running tests"
        DEPENDS unittest
    )
endif()
# Export compile commands for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)