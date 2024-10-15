#include "Hall.hpp"
#include "Hall_impl.hpp"
#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"


int main(){
  std::cout << "Hello World!" << std::endl;
  std::ifstream file("../data/nice.txt");
  SparseGraph<SparseMat> graph(*SparseGraph<SparseMat>::generateAdjacencyMatrix(file));
  //std::cout << *graph.getAdjacencyMatrix() << std::endl;
  auto result1 = Hall2D<SparseMat>(graph);
  for(auto res: result1){std::cout << res.first << "," << res.second << std::endl;} 
  //for(auto res: result1){std::cout << res << std::endl;}
}