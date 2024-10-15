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

template<typename T>
DenseMat HDE(SparseGraph<T>& graph,int m){
  std::size_t order = graph.getOrder();
  auto adj = graph.getAdjacencyMatrix();
  std::vector<int> d(order,order);
  DenseMat X(m,order);
  int p = 0;
  for(int i = 0; i < m; ++i){
    int max = 0;
    //BFS
    std::deque<int> queue  = {p};
    //std::vector<int> distance(order);
    while(!queue.empty()){
      int curr = queue.front();
      queue.pop_front();
      for(int j = 0; j < order; ++j){
        if(adj->coeff(curr,j) != 0 && X(i,j) == 0 && j != p){
          queue.push_back(j);
          X(i,j) = X(i,curr)+1;
        }
      }
    }

    for(int j = 0; j < order; j++){
      //X(i,j) = distance[j];
      d[j] = (X(i,j) < d[j])? (int)X(i,j) : d[j];
      if(d[j]  > max){p = j;}
    }
    //p = std::max_element(d.begin(),d.end())-d.begin();
  }
  return X;
}

void orthonormalise(DenseMat& X){
  std::size_t m = X.rows();
  Eigen::VectorXd v = Eigen::VectorXd::Ones(X.cols());
  v.normalize();
  auto u = v.transpose();
  for(int i = 0; i < m; ++i){
    X.row(i) = X.row(i)-(X.row(i).dot(u))*u;
    for(int j = 0; j < i; ++j){
      X.row(i) = X.row(i)-(X.row(i).dot(X.row(j)))*X.row(j);
    }
    if(X.row(i).norm()<0.001){X.row(i) = Eigen::VectorXd::Zero(X.cols());}
    else{X.row(i).normalize();}
  }
}

template<typename T>
std::vector<std::pair<double, double>> HDEHall2D(SparseGraph<T>& graph)
  {
  DenseMat subspace = HDE(graph,50);
  orthonormalise(subspace);
  std::cout << "Here" << std::endl;
  DenseMat N = (subspace)*(*graph.getLaplacianMatrix());
  subspace = subspace.transpose().eval();
  DenseMat M = N*subspace;
  Spectra::DenseSymMatProd<double> op(M);
  Spectra::SymEigsSolver<Spectra::DenseSymMatProd<double>> eigs(op, 2, 12);
  eigs.init();
  DenseMat evecs;
  int nconv = eigs.compute(Spectra::SortRule::SmallestMagn);
  if (eigs.info() == Spectra::CompInfo::Successful) {
    evecs = subspace*eigs.eigenvectors();
    std::cout << evecs.rows() << std::endl;
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