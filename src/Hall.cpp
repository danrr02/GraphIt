#include "Hall.hpp"

std::vector<double> Hall1D(Graph& graph){
  if(!graph.isConnected()){std::cout << "Error: Graph not connected." << std::endl;}
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(*graph.getLaplacianMatrix()); 
  auto evecs = es.eigenvectors();
  return std::vector<double>(evecs.col(1).begin(),evecs.col(1).end());
}

std::vector<std::pair<double,double>> Hall2D(Graph& graph){
  if(!graph.isConnected()){std::cout << "Error: Graph not connected." << std::endl;}
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(*graph.getLaplacianMatrix()); 
  auto evecs = es.eigenvectors();
  Eigen::Index n{evecs.rows()};
  std::vector<std::pair<double,double>> res;
  for(Eigen::Index i = 0; i < n; ++i){
    res.push_back({evecs(i,1),evecs(i,2)});
  }
  return res;
}