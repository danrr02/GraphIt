#pragma once

#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"
#include "SparseHall.hpp"
#include "Spectra/MatOp/SparseSymMatProd.h"
#include "Spectra/SymEigsSolver.h"
#include <eigen3/Eigen/Core>

template <>
std::vector<std::pair<double, double>>
Hall2D<SparseMat>(SparseGraph<SparseMat> &graph) {
  Spectra::SparseSymMatProd<double> op(*graph.getLaplacianMatrix());
  Spectra::SymEigsSolver<Spectra::SparseSymMatProd<double>> eigs(op, 3, 40);
  eigs.init();
  DenseMat evecs;
  int nconv = eigs.compute(Spectra::SortRule::SmallestMagn);
  if (eigs.info() == Spectra::CompInfo::Successful) {
    evecs = eigs.eigenvectors();
  } else {
    std::cout << "Fail";
  }
  std::vector<std::pair<double, double>> output;
  std::size_t n{graph.getOrder()};
  for (std::size_t i = 0; i < n; ++i) {
    output.push_back({evecs(i, 0), evecs(i, 1)});
  }
  return output;
}
