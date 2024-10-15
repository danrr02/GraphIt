//#include "SparseHall.hpp"
#include "SparseHall_impl.hpp"
//#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"
#include <SFML/Graphics.hpp>
#include <array>

auto comp = [](const std::pair<double,double>& a, const std::pair<double,double>& b){
  return (std::pow(a.first,2)+std::pow(a.second,2))<(std::pow(b.first,2)+std::pow(b.second,2));
};


double _scale(std::vector<std::pair<double,double>> &points){
  std::pair<double,double> a = *std::max_element(points.begin(),points.end(),comp);
  return 1/std::pow((std::pow(a.first,2)+std::pow(a.second,2)),0.5);
}


int main() {
  std::ifstream file("../data/4elt.txt");
  SparseGraph<SparseMat> graph(file);
  //std::cout << *graph.getAdjacencyMatrix() << std::endl;
  auto computedPoints =   HDEHall2D(graph);
  int scale = 500*(int)_scale(computedPoints);
  std::cout << scale << std::endl;
  std::size_t n = graph.getOrder();
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "GraphIt");
  sf::VertexArray points(sf::PrimitiveType::Points);
  for (auto point : computedPoints) {
    points.append(
        sf::Vector2f(500 + scale * point.first, 500 + scale * point.second));
  }

  std::vector<std::vector<sf::Vertex>> lines;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (graph.getAdjacencyMatrix()->coeff(i, j) > 0.001) {
        lines.push_back({sf::Vertex(sf::Vector2f(500 + scale * computedPoints[i].first,
                                   500 + scale * computedPoints[i].second)),
                      sf::Vertex(sf::Vector2f(500 + scale * computedPoints[j].first,
                                   500 + scale * computedPoints[j].second))});
      }
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(points);
    for(auto line: lines){window.draw(&line[0],2,sf::Lines);}
    window.display();
  }

  return 0;
}