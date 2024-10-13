#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"

int main(){
  SparseGraph graph(Eigen::SparseMatrix<double>(10,10));
  std::cout << *graph.getAdjacencyMatrix() << "\n";
  //SparseGraph graph2(Eigen::MatrixXd({{0,1},{1,0}}));
  //std::cout << graph2.getAdjacencyMatrix()->coeff(0,0) << "\n";
  //std::cout << *graph2.getAdjacencyMatrix() << "\n";
}