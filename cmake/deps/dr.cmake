
if(TARGET dr::dr)
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    dr
    GIT_REPOSITORY https://github.com/davreev/dr.git
    GIT_TAG 843cecaa2f11b413a084af9117496898daf033a2
)

FetchContent_MakeAvailable(dr)
