#pragma once

#include <Spectra/MatOp/SparseSymShiftSolve.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/SymEigsShiftSolver.h>
#include <Spectra/SymGEigsShiftSolver.h>

#include <dr/linalg_types.hpp>
#include <dr/math_traits.hpp>
#include <dr/sparse_linalg_types.hpp>

namespace dr
{

template <typename Real>
struct SparseSymEigendecomp
{
    static_assert(is_real<Real>);

    /// Partially solves the symmetric eigenvalue problem Ax=λx by computing the first n eigenpairs
    /// sorted by eigenvalue.
    ///
    /// NOTE: This uses a shift-and-invert mode meaning that the given sort rule applies to the
    /// value of 1/(λ-σ) rather than λ directly. For example, shifting by zero and sorting by
    /// largest magnitude will return eigenpairs with the *smallest* absolute eigenvalues.
    template <typename Index>
    bool solve_shift_inv(
        SparseMat<Real, Index> const& A,
        Index const count,
        Real const sigma = Real{0.0},
        Spectra::SortRule const sort_rule = Spectra::SortRule::LargestMagn)
    {
        static_assert(is_integer<Index>);

        using Op = Spectra::SparseSymShiftSolve<Real, Eigen::Lower, Eigen::ColMajor, Index>;
        using Solver = Spectra::SymEigsShiftSolver<Op>;

        Index const n = A.rows();
        Index const conv = count * 2;

        Op op{A};
        Solver solver{op, count, (conv > n) ? n : conv, sigma};
        solver.init();
        solver.compute(sort_rule);

        // Cache results
        eigenvecs_ = solver.eigenvectors();
        eigenvals_ = solver.eigenvalues();
        info_ = solver.info();

        return info_ == Spectra::CompInfo::Successful;
    }

    /// Partially solves the generalized symmetric eigenvalue problem Ax=λBx by computing the first
    /// n eigenpairs sorted by eigenvalue.
    ///
    /// NOTE: This uses a shift-and-invert mode meaning that the given sort rule applies to the
    /// value of 1/(λ-σ) rather than λ directly. For example, shifting by zero and sorting by
    /// largest magnitude will return eigenpairs with the *smallest* absolute eigenvalues.
    template <typename Index>
    bool solve_shift_inv(
        SparseMat<Real, Index> const& A,
        SparseMat<Real, Index> const& B,
        Index const count,
        Real const sigma = Real{0.0},
        Spectra::SortRule const sort_rule = Spectra::SortRule::LargestMagn)
    {
        static_assert(is_integer<Index>);

        using Op = Spectra::SymShiftInvert<
            Real,
            Eigen::Sparse,
            Eigen::Sparse,
            Eigen::Lower,
            Eigen::Lower,
            Eigen::ColMajor,
            Eigen::ColMajor,
            Index,
            Index>;

        using OpB = Spectra::SparseSymMatProd<Real, Eigen::Lower, Eigen::ColMajor, Index>;
        using Solver = Spectra::SymGEigsShiftSolver<Op, OpB, Spectra::GEigsMode::ShiftInvert>;

        Index const n = A.rows();
        Index const conv = count * 2;

        Op op{A, B};
        OpB op_b{B};
        Solver solver(op, op_b, count, (conv > n) ? n : conv, sigma);
        solver.init();
        solver.compute(sort_rule);

        // Cache results
        eigenvecs_ = solver.eigenvectors();
        eigenvals_ = solver.eigenvalues();
        info_ = solver.info();

        return info_ == Spectra::CompInfo::Successful;
    }

    Mat<Real> const& eigenvecs() const { return eigenvecs_; }

    Vec<Real> const& eigenvals() const { return eigenvals_; }

    Spectra::CompInfo const& info() const { return info_; }

  private:
    Mat<Real> eigenvecs_;
    Vec<Real> eigenvals_;
    Spectra::CompInfo info_{Spectra::CompInfo::NotComputed};
};

} // namespace dr