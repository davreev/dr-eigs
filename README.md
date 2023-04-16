# dr-eigs

![](https://github.com/davreev/dr-eigs/actions/workflows/test.yml/badge.svg)

Utilities for eigendecomposition of sparse matrices

## Build

Build with CMake

> ⚠️ Currently only tested with Clang and GCC. MSVC is not supported.

```sh
mkdir build
cd build

# If using a single-config generator (e.g. Unix Makefiles, Ninja)
cmake -DCMAKE_BUILD_TYPE=(Debug|Release|RelWithDebInfo) [-DDR_EIGS_EXAMPLE=ON] [-DDR_EIGS_TEST=ON] ..
cmake --build .

# If using a multi-config generator (e.g. Ninja Multi-Config, Xcode)
cmake [-DDR_EIGS_EXAMPLE=ON] [-DDR_EIGS_TEST=ON] ..
cmake --build . --config (Debug|Release|RelWithDebInfo)
```

## Usage

Use `FetchContent` to include in another CMake build

```cmake
include(FetchContent)

FetchContent_Declare(
    dr-eigs
    GIT_REPOSITORY https://github.com/davreev/dr-eigs.git
    GIT_TAG <revision>
)

# Creates target "dr::eigs"
FetchContent_MakeAvailable(dr-eigs)

# Link other targets e.g.
add_executable(my-app main.cpp)
target_link_libraries(my-app PRIVATE dr::eigs)
```
