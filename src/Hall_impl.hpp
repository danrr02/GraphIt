#pragma once

#include "Hall.hpp"

template <typename T> std::vector<double> Hall1D(SparseGraph<T> &graph) {
  if (!graph.isConnected()) {
    std::cout << "Error: Graph not connected." << std::endl;
  }
  Eigen::SelfAdjointEigenSolver<T> es(*graph.getLaplacianMatrix());
  auto evecs = es.eigenvectors();
  return std::vector<double>(evecs.col(1).begin(), evecs.col(1).end());
}

template <typename T>
std::vector<std::pair<double, double>> Hall2D(SparseGraph<T> &graph) {
  if (!graph.isConnected()) {
    std::cout << "Error: Graph not connected." << std::endl;
  }
  Eigen::SelfAdjointEigenSolver<T> es(*graph.getLaplacianMatrix());
  auto evecs = es.eigenvectors();
  Eigen::Index n{evecs.rows()};
  std::vector<std::pair<double, double>> res;
  for (Eigen::Index i = 0; i < n; ++i) {
    res.push_back({evecs(i, 1), evecs(i, 2)});
  }
  return res;
}