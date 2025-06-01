cmake_minimum_required(VERSION 3.14)
project(
    dr-eigs
    VERSION 0.2.0
    LANGUAGES CXX
)

#
# Global config
#

set(CMAKE_CXX_STANDARD 17)

list(
    PREPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake/"
)

# Show FetchContent download progress
set(FETCHCONTENT_QUIET FALSE)

#
# Targets
#

add_library(dr-eigs INTERFACE)
add_library(dr::eigs ALIAS dr-eigs)

target_include_directories(
    dr-eigs
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include"
)

include(deps/dr)
include(deps/spectra)

target_link_libraries(
    dr-eigs
    INTERFACE
        dr::dr
        Spectra::Spectra
)

target_compile_options(
    dr-eigs
    INTERFACE
        -Wall -Wextra -Wpedantic -Werror
)

#
# Optional targets
#

option(DR_EIGS_TEST "Generate test target" OFF)
if(DR_EIGS_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
