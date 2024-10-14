#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"

int main(){
  //SparseGraph graph(Generate::randomGraph<DenseMat>(1000,0.05));
  //SparseGraph graph2(Generate::randomGraph<SparseMat>(1000,0.05));
  std::ifstream file("../data/nice.txt");
  //std::cout << *SparseGraph<SparseMat>::generateAdjacencyMatrix(file);
  SparseGraph<SparseMat> graph(*SparseGraph<SparseMat>::generateAdjacencyMatrix(file));
  //SparseGraph graph(mat);
} 