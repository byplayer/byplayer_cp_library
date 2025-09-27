cmake_minimum_required(VERSION 3.14)
project(unittest)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ac-library
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(unittest ${TEST_SOURCES})

target_link_libraries(unittest
    gtest
    gtest_main
    gmock
)

include(GoogleTest)
gtest_discover_tests(unittest
    DISCOVERY_MODE PRE_TEST
)

add_custom_target(run_unittest
    COMMAND unittest
    DEPENDS unittest
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running unit tests"
)
