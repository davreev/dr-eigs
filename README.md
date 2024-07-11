# dr-eigs

![](https://github.com/davreev/dr-eigs/actions/workflows/test.yml/badge.svg)

Utilities for eigendecomposition of sparse matrices via [Spectra](https://github.com/yixuan/spectra)

## Build

Use CMake to build

> ⚠️ Currently only tested with Clang and GCC. MSVC is not supported.

```sh
mkdir build
cmake -S . -B ./build -G <generator> [-DDR_EIGS_TEST=ON]
cmake --build ./build [--config <config>]
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
