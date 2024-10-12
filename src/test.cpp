#include "Hall.hpp"

int main(){
  std::cout << "Hello World!" << std::endl;
  //Graph graph({{0,1,0,1},{1,0,1,1},{0,1,0,1},{1,1,1,0}});
  //std::cout << *graph.getAdjacencyMatrix() << std::endl;
  //std::cout << *graph.getDegreeMatrix() << std::endl;
  //std::cout << *graph.getLaplacianMatrix() << std::endl;
  //std::vector<std::pair<double,double>> result = Hall2D(graph);
  //for(auto res: result){std::cout << res.first << "," << res.second << std::endl;} 
  
  Graph graph1 = Graph::randomGraph(5,1,3);
  std::cout << graph1.isConnected()  << "____" << std::endl;
  std::cout << *graph1.getAdjacencyMatrix() << std::endl;
  std::cout << *graph1.getDegreeMatrix() << std::endl;
  std::cout << *graph1.getLaplacianMatrix() << std::endl;
  auto result1 = Hall2D(graph1);
  for(auto res: result1){std::cout << res.first << "," << res.second << std::endl;} 
  //for(auto res: result1){std::cout << res << std::endl;}
  
}