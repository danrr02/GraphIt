#pragma once

#include "SparseGraph.hpp"

template <class T>
const std::shared_ptr<const T> SparseGraph<T>::generateAdjacencyMatrix(
    std::initializer_list<std::initializer_list<double>> g) {
  std::shared_ptr<const T> adjacencyMatrix =
      std::make_shared<const T>(Eigen::MatrixXd(g));
  if (adjacencyMatrix->cols() != adjacencyMatrix->rows()) {
    throw std::runtime_error("Invalid adjacency matrix - not square.");
  }
  std::size_t n = adjacencyMatrix->rows();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i; j < n; ++j) {
      if (i == j && (*adjacencyMatrix)(i, j) != 0) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      } else if ((*adjacencyMatrix)(i, j) != (*adjacencyMatrix)(j, i) ||
                 ((*adjacencyMatrix)(i, j) != 0 &&
                  (*adjacencyMatrix)(i, j) != 1)) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      }
    }
  }
  return adjacencyMatrix;
}

template <>
const std::shared_ptr<const Eigen::MatrixXd>
SparseGraph<Eigen::MatrixXd>::generateAdjacencyMatrix(const Eigen::MatrixXd g) {
  std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix =
      std::make_shared<const Eigen::MatrixXd>(g);
  if (adjacencyMatrix->cols() != adjacencyMatrix->rows()) {
    throw std::runtime_error("Invalid adjacency matrix - not square.");
  }
  std::size_t n = adjacencyMatrix->rows();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i; j < n; ++j) {
      if (i == j && (*adjacencyMatrix)(i, j) != 0) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      } else if ((*adjacencyMatrix)(i, j) != (*adjacencyMatrix)(j, i) ||
                 ((*adjacencyMatrix)(i, j) != 0 &&
                  (*adjacencyMatrix)(i, j) != 1)) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      }
    }
  }
  return adjacencyMatrix;
}

template<>
const std::shared_ptr<const Eigen::SparseMatrix<double>> SparseGraph<Eigen::SparseMatrix<double>>::generateAdjacencyMatrix(const Eigen::SparseMatrix<double> g){
  std::shared_ptr<const Eigen::SparseMatrix<double>> adjacencyMatrix =
      std::make_shared<const Eigen::SparseMatrix<double>>(g);
  if (adjacencyMatrix->cols() != adjacencyMatrix->rows()) {
    throw std::runtime_error("Invalid adjacency matrix - not square.");
  }
  std::size_t n = adjacencyMatrix->rows();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i; j < n; ++j) {
      if (i == j && adjacencyMatrix->coeff(i, j) != 0) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      } else if (adjacencyMatrix->coeff(i, j) != adjacencyMatrix->coeff(j, i) ||
                 (adjacencyMatrix->coeff(i, j) != 0 &&
                  adjacencyMatrix->coeff(i, j) != 1)) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      }
    }
  }
  return adjacencyMatrix;
}

template <>
const std::shared_ptr<const Eigen::MatrixXd>
SparseGraph<Eigen::MatrixXd>::generateDegreeMatrix(
    const std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix) {
  std::size_t n = adjacencyMatrix->rows();
  auto degreeMatrix =
      std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(n, n));
  for (std::size_t i = 0; i < n; ++i) {
    (*degreeMatrix)(i, i) = std::accumulate(adjacencyMatrix->col(i).begin(),
                                            adjacencyMatrix->col(i).end(), 0);
  };
  return degreeMatrix;
}

template <>
const std::shared_ptr<const Eigen::SparseMatrix<double>>
SparseGraph<Eigen::SparseMatrix<double>>::generateDegreeMatrix(
    const std::shared_ptr<const Eigen::SparseMatrix<double>> adjacencyMatrix) {
  std::size_t n = adjacencyMatrix->rows();
  auto degreeMatrix = std::make_shared<Eigen::SparseMatrix<double>>(
      Eigen::SparseMatrix<double>(n, n));
  for (std::size_t i = 0; i < n; ++i) {
    degreeMatrix->insert(i, i) =
        adjacencyMatrix->row(i) * Eigen::VectorXd::Ones(n);
  }
  return degreeMatrix;
}

template <>
const bool SparseGraph<Eigen::MatrixXd>::connectedGraph(
    const std::shared_ptr<const Eigen::MatrixXd> &adjacencyMatrix) {
  std::size_t order = adjacencyMatrix->rows();
  std::vector<bool> visited(order, false);
  std::deque<int> queue = {0};
  visited[0] = true;
  while (!queue.empty()) {
    std::size_t curr = queue.front();
    queue.pop_front();
    for (std::size_t i = 0; i < order; ++i) {
      if ((*adjacencyMatrix)(curr, i) != 0 && !visited[i]) {
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

template <>
const bool SparseGraph<Eigen::SparseMatrix<double>>::connectedGraph(
    const std::shared_ptr<const Eigen::SparseMatrix<double>> &adjacencyMatrix) {
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