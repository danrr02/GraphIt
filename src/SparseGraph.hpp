/*
Declaration of the Graph class.
*/

#pragma once

#include <deque>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

typedef Eigen::MatrixXd DenseMat;
typedef Eigen::SparseMatrix<double> SparseMat;

template <typename T> class SparseGraph {

  // pointer to adjacency matrix
  const std::shared_ptr<const T> adjacencyMatrix;

  // pointer to degree matrix
  const std::shared_ptr<const T> degreeMatrix;

  // pointer to laplacian matrix
  const std::shared_ptr<const T> laplacianMatrix;

  const bool connected;

  const std::size_t order;

public:
  // constuctor from matrix
  SparseGraph(const T);


  // construct from a file
  SparseGraph<T>(std::ifstream &);


  // getters for member fields
  std::shared_ptr<const T> getAdjacencyMatrix() const;

  std::shared_ptr<const T> getDegreeMatrix() const;

  std::shared_ptr<const T> getLaplacianMatrix() const;

  const bool isConnected() const;

  const std::size_t getOrder() const;


  // utility functions used by constructors
  static const std::shared_ptr<const DenseMat> generateAdjacencyMatrix(
      std::initializer_list<std::initializer_list<double>>);

  static const std::shared_ptr<const T> generateAdjacencyMatrix(const T);

  static const std::shared_ptr<const SparseMat>
  generateAdjacencyMatrix(std::ifstream &);

  static const std::shared_ptr<const DenseMat>
  generateDegreeMatrix(const std::shared_ptr<const DenseMat>);

  static const std::shared_ptr<const SparseMat>
  generateDegreeMatrix(const std::shared_ptr<const SparseMat>);

  static const bool connectedGraph(const std::shared_ptr<const T> &);
};

