if(TARGET Spectra::Spectra)
    return()
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # Show download progress

FetchContent_Declare(
    spectra
    GIT_REPOSITORY https://github.com/yixuan/spectra.git
    GIT_TAG 1690f6a0fb040865fd22dc2ba3bdeedf1a46c01f
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(spectra)
if(NOT ${spectra_POPULATED})
    FetchContent_Populate(spectra)

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
endif()
