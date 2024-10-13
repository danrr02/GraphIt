#pragma once

#include "SparseGraph.hpp"

template <>
const std::shared_ptr<const DenseMat>
SparseGraph<DenseMat>::generateDegreeMatrix(
    const std::shared_ptr<const DenseMat> adjacencyMatrix) {
  std::size_t n = adjacencyMatrix->rows();
  auto degreeMatrix =
      std::make_shared<DenseMat>(DenseMat::Zero(n, n));
  for (std::size_t i = 0; i < n; ++i) {
    (*degreeMatrix)(i, i) = std::accumulate(adjacencyMatrix->col(i).begin(),
                                            adjacencyMatrix->col(i).end(), 0);
  };
  return degreeMatrix;
}

template <>
const std::shared_ptr<const SparseMat>
SparseGraph<SparseMat>::generateDegreeMatrix(
    const std::shared_ptr<const SparseMat> adjacencyMatrix) {
  std::size_t n = adjacencyMatrix->rows();
  auto degreeMatrix = std::make_shared<SparseMat>(
      SparseMat(n, n));
  for (std::size_t i = 0; i < n; ++i) {
    degreeMatrix->insert(i, i) =
        adjacencyMatrix->row(i) * Eigen::VectorXd::Ones(n);
  }
  return degreeMatrix;
}

template <typename T>
const bool SparseGraph<T>::connectedGraph(
    const std::shared_ptr<const T> &adjacencyMatrix) {
  std::size_t order = adjacencyMatrix->rows();
  std::vector<bool> visited(order, false);
  std::deque<int> queue = {0};
  visited[0] = true;
  while (!queue.empty()) {
    std::size_t curr = queue.front();
    queue.pop_front();
    for (std::size_t i = 0; i < order; ++i) {
      if (adjacencyMatrix->coeff(curr, i) != 0 && !visited[i]) {
        visited[i] = true;
        queue.push_back(i);
      }
    }
  }
  for (bool node : visited) {
    if (!node) {
      return false;
    }
  }
  return true;
}

template <typename T>
SparseGraph<T>::SparseGraph(const T g) try
    : adjacencyMatrix(SparseGraph<T>::generateAdjacencyMatrix(g)),
      order(g.rows()),
      degreeMatrix(SparseGraph<T>::generateDegreeMatrix(adjacencyMatrix)),
      laplacianMatrix(std::make_shared<T>(*degreeMatrix - *adjacencyMatrix)),
      connected(SparseGraph<T>::connectedGraph(adjacencyMatrix)) {
} catch (const std::runtime_error &e) {
  std::cerr << e.what() << std::endl;
}

template <typename T>
std::shared_ptr<const T> SparseGraph<T>::getAdjacencyMatrix() const{
  return adjacencyMatrix;
}

template <typename T>
std::shared_ptr<const T> SparseGraph<T>::getDegreeMatrix() const{
  return degreeMatrix;
}

template <typename T>
std::shared_ptr<const T> SparseGraph<T>::getLaplacianMatrix() const {
  return laplacianMatrix;
}