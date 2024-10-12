#include "Hall.hpp"
#include <SFML/Graphics.hpp>
#include <array>

int main() {
  int n = 200;
  Graph graph(Graph::randomGraph(n));
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
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  sf::VertexArray points(sf::PrimitiveType::Points);
  for (auto point : computedPoints) {
    points.append(
        sf::Vector2f(400 + 400 * point.first, 400 + 400 * point.second));
  }

  std::vector<sf::Vertex> line = {sf::Vertex(sf::Vector2f(400 + 400 * computedPoints[0].first,
                                   400 + 400 * computedPoints[0].second)),
                      sf::Vertex(sf::Vector2f(400 + 400 * computedPoints[1].first,
                                   400 + 400 * computedPoints[1].second))};


  std::vector<std::vector<sf::Vertex>> lines;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if ((*graph.getAdjacencyMatrix())(i, j) > 0.001) {
        lines.push_back({sf::Vertex(sf::Vector2f(400 + 400 * computedPoints[i].first,
                                   400 + 400 * computedPoints[i].second)),
                      sf::Vertex(sf::Vector2f(400 + 400 * computedPoints[j].first,
                                   400 + 400 * computedPoints[j].second))});
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