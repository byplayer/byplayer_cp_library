cmake_minimum_required(VERSION 3.14)
project(unittest)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Set compiler flags before including any external projects
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -stdlib=libc++")

    # Force these flags for all targets including FetchContent
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

include(FetchContent)

# Set GoogleTest to be built as a static library with position independent code
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    # Basic warnings (always available)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpointer-arith -Wcast-qual")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces -Wempty-body")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -pedantic")

    # Version-specific flags
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "5.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-pedantic")
    endif()

    # Performance tuning
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native -march=native")

    # Constexpr limits
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "5.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-depth=2147483647")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8.0")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-steps=214748364")
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # Basic warnings (always available)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces -Wempty-body")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -pedantic")

    # Version-specific flags
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "5.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-pedantic")
    endif()

    # Constexpr limits
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "5.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-depth=2147483647")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-loop-limit=2147483647")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "9.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-ops-limit=2147483647")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG=1)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    add_definitions(-DNDEBUG)
endif()

# Cache GoogleTest for faster rebuilds
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Disconnect FetchContent updates after initial download")

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
    GIT_CONFIG      "advice.detachedHead=false"
)

# Set to OFF to show download progress (useful for CI/CD visibility)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(googletest)


file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(unittest ${TEST_SOURCES})

target_include_directories(unittest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ac-library
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(unittest
    gtest
    gtest_main
    gmock
)

# Explicitly link libc++ for Homebrew LLVM on macOS
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND APPLE)
    target_link_libraries(unittest c++ c++abi)

    # If using Homebrew LLVM, dynamically detect and add the library path
    if(CMAKE_CXX_COMPILER MATCHES "/opt/homebrew" OR CMAKE_CXX_COMPILER MATCHES "/usr/local")
        # Detect Homebrew LLVM path dynamically
        if(NOT DEFINED BREW_LLVM_PREFIX)
            execute_process(
                COMMAND brew --prefix llvm
                OUTPUT_VARIABLE BREW_LLVM_PREFIX
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET
            )
            set(BREW_LLVM_PREFIX "${BREW_LLVM_PREFIX}" CACHE STRING "Path to Homebrew LLVM")
        endif()
        if(BREW_LLVM_PREFIX)
            target_link_directories(unittest PRIVATE ${BREW_LLVM_PREFIX}/lib/c++)
            message(STATUS "Using Homebrew LLVM from: ${BREW_LLVM_PREFIX}")
        endif()
    endif()
endif()

include(GoogleTest)
gtest_discover_tests(unittest
    DISCOVERY_MODE POST_BUILD
)

