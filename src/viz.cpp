#include "SparseHall.hpp"
#include "SparseHall_impl.hpp"
#include "SparseGraph.hpp"
#include "SparseGraph_impl.hpp"
#include <SFML/Graphics.hpp>
#include <array>

int main() {
  std::ifstream file("../data/4elt.txt");
  double scale = 30000;
  SparseGraph<SparseMat> graph(*SparseGraph<SparseMat>::generateAdjacencyMatrix(file));
  //std::cout << *graph.getAdjacencyMatrix() << std::endl;
  auto computedPoints = Hall2D<SparseMat>(graph);
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