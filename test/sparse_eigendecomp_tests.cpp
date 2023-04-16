#include <utest.h>

#include <dr/basic_types.hpp>
#include <dr/sparse_eigendecomp.hpp>

UTEST(sparse_eigendecomp, solve_shift_inv)
{
    using namespace dr;

    Triplet<f64> const coeffs[]{
        {0, 0, 1.0},
        {1, 1, 0.5},
        {2, 2, 2.0},
        {3, 3, 0.25},
        {4, 4, 4.0},
    };

    SparseMat<f64> A{5, 5};
    A.setFromTriplets(std::begin(coeffs), std::end(coeffs));

    SparseSymEigendecomp<f64> eigs{};
    constexpr f64 eps = 1.0e-8;

    eigs.solve_shift_inv(A, 3, 0.0, Spectra::SortRule::LargestMagn);
    ASSERT_TRUE(eigs.info() == Spectra::CompInfo::Successful);

    {
        auto const& evals = eigs.eigenvals();
        ASSERT_NEAR(evals[0], 1.0, eps);
        ASSERT_NEAR(evals[1], 0.5, eps);
        ASSERT_NEAR(evals[2], 0.25, eps);
    }

    eigs.solve_shift_inv(A, 3, 0.0, Spectra::SortRule::SmallestMagn);
    ASSERT_TRUE(eigs.info() == Spectra::CompInfo::Successful);

    {
        auto const& evals = eigs.eigenvals();
        ASSERT_NEAR(evals[0], 4.0, eps);
        ASSERT_NEAR(evals[1], 2.0, eps);
        ASSERT_NEAR(evals[2], 1.0, eps);
    }
}
