if(TARGET dr::dr)
    return()
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # Show download progress

FetchContent_Declare(
    dr
    GIT_REPOSITORY git@github.com:davreev/dr.git
    GIT_TAG 0212879039fc1b4c7f821396754db1fed8356f66 # 0.1.0
)

FetchContent_MakeAvailable(dr)
