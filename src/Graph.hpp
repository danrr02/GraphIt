/*
Declaration of the Graph class.
*/

#pragma once

#include <deque>
#include <eigen3/Eigen/Dense>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>
#include <fstream>

class Graph {
  //Orer of the graph
  const std::size_t order;

  //pointer to adjacency matrix
  const std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix;

  //pointer to degree matrix
  const std::shared_ptr<const Eigen::MatrixXd> degreeMatrix;

  //pointer to laplacian matrix
  const std::shared_ptr<const Eigen::MatrixXd> laplacianMatrix;

  const bool connected;

public:
  //construct from initializer lists - for graphs defined by hand
  Graph(const std::initializer_list<std::initializer_list<double>>);

  //constuctor from matrix
  Graph(const Eigen::MatrixXd);

  Graph(std::ifstream);//to implement
  
  //getters for member fields
  const std::shared_ptr<const Eigen::MatrixXd> getAdjacencyMatrix() const;
  const std::shared_ptr<const Eigen::MatrixXd> getDegreeMatrix() const;
  const std::shared_ptr<const Eigen::MatrixXd> getLaplacianMatrix() const;
  const bool isConnected() const;
  const std::size_t getOrder() const;

  //utility functions used by constructors
  static const std::shared_ptr<const Eigen::MatrixXd> generateAdjacencyMatrix(std::initializer_list<std::initializer_list<double>>);
  static const std::shared_ptr<const Eigen::MatrixXd> generateAdjacencyMatrix(const Eigen::MatrixXd);
  static const std::shared_ptr<const Eigen::MatrixXd> generateAdjacencyMatrix(std::ifstream); //to implement
  static const std::shared_ptr<const Eigen::MatrixXd> generateDegreeMatrix(const std::shared_ptr<const Eigen::MatrixXd>);
  static const bool connectedGraph(const std::shared_ptr<const Eigen::MatrixXd>);

  //generate random graph
  static Graph randomGraph(std::size_t);
};