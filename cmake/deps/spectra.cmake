if(TARGET Spectra::Spectra)
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    spectra
    URL https://github.com/yixuan/spectra/archive/refs/tags/v1.0.1.zip
)

FetchContent_GetProperties(spectra)
if(NOT ${spectra_POPULATED})
    FetchContent_Populate(spectra)
endif()

add_library(spectra INTERFACE)
add_library(Spectra::Spectra ALIAS spectra)

target_include_directories(
    spectra
    SYSTEM # Suppresses warnings from third party headers
    INTERFACE
        "${spectra_SOURCE_DIR}/include"
)

target_link_libraries(
    spectra
    INTERFACE
        Eigen3::Eigen
)
