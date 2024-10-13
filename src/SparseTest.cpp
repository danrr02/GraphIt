#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"

int main(){
  SparseGraph graph(Generate::randomGraph<DenseMat>(1000,0.05));
  //SparseGraph graph2(Generate::randomGraph<SparseMat>(1000,0.05));
}