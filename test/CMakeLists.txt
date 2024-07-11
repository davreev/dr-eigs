add_executable(
    dr-eigs-test
    main.cpp
    sparse_eigendecomp_tests.cpp
)

include(deps/utest)

target_link_libraries(
    dr-eigs-test 
    PRIVATE
        dr::dr
        dr::eigs
        utest::utest
)

target_compile_options(
    dr-eigs-test
    PRIVATE 
        -Wall -Wextra -Wpedantic -Werror
)

add_test(
    NAME dr-eigs-test
    COMMAND dr-eigs-test
)
