/*
Declaration of the Graph class.
*/

#pragma once

#include <deque>
#include <eigen3/Eigen/Dense>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

class Graph {
  const std::size_t order;
  const std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix;
  const std::shared_ptr<const Eigen::MatrixXd> degreeMatrix;
  const std::shared_ptr<const Eigen::MatrixXd> laplacianMatrix;
  const bool connected;

public:
  Graph(const std::initializer_list<std::initializer_list<double>>);
  Graph(const Eigen::MatrixXd);
  Graph(std::ifstream); // to implement
  const std::shared_ptr<const Eigen::MatrixXd> getAdjacencyMatrix() const;
  const std::shared_ptr<const Eigen::MatrixXd> getDegreeMatrix() const;
  const std::shared_ptr<const Eigen::MatrixXd> getLaplacianMatrix() const;
  const bool isConnected() const;
  const std::size_t getOrder() const;

  static const std::shared_ptr<const Eigen::MatrixXd> generateAdjacencyMatrix(
      std::initializer_list<std::initializer_list<double>>);
  static const std::shared_ptr<const Eigen::MatrixXd>
  generateAdjacencyMatrix(const Eigen::MatrixXd);
  static const std::shared_ptr<const Eigen::MatrixXd>
      generateAdjacencyMatrix(std::ifstream); // to implement
  static const std::shared_ptr<const Eigen::MatrixXd>
  generateDegreeMatrix(const std::shared_ptr<const Eigen::MatrixXd>);
  static const bool
  connectedGraph(const std::shared_ptr<const Eigen::MatrixXd>);
  static Graph randomGraph(std::size_t, double);
  static Graph randomHoledGraph(std::size_t, double, int);
};