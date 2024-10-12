#include "Hall.hpp"
#include <SFML/Graphics.hpp>
#include <array>

int main() {
  int n = 50;
  Graph graph(Graph::randomGraph(n,0.2,2));
  /*
  Graph graph({{0, 1, 0, 1, 1, 1, 0, 0, 0},
               {1, 0, 1, 1, 0, 0, 0, 0, 1},
               {0, 1, 0, 0, 0, 0, 0, 1, 1},
               {1, 1, 0, 0, 0, 0, 1, 1, 0},
               {1, 0, 0, 0, 0, 1, 0, 0, 1},
               {1, 0, 0, 0, 1, 0, 1, 0, 0},
               {0, 0, 0, 1, 0, 1, 0, 1, 0},
               {0, 0, 1, 1, 0, 0, 1, 0, 0},
               {0, 1, 1, 0, 1, 0, 0, 0, 0}});
               */
  std::vector<std::pair<double, double>> computedPoints(Hall2D(graph));
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "GraphIt");
  sf::VertexArray points(sf::PrimitiveType::Points);
  for (auto point : computedPoints) {
    points.append(
        sf::Vector2f(500 + 500 * point.first, 500 + 500 * point.second));
  }

  std::vector<std::vector<sf::Vertex>> lines;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if ((*graph.getAdjacencyMatrix())(i, j) > 0.001) {
        lines.push_back({sf::Vertex(sf::Vector2f(500 + 500 * computedPoints[i].first,
                                   500 + 500 * computedPoints[i].second)),
                      sf::Vertex(sf::Vector2f(500 + 500 * computedPoints[j].first,
                                   500 + 500 * computedPoints[j].second))});
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