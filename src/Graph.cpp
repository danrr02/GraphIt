#include "Graph.hpp"

const std::shared_ptr<const Eigen::MatrixXd> Graph::generateAdjacencyMatrix(
    std::initializer_list<std::initializer_list<double>> g) {
  auto adjacencyMatrix =
      std::make_shared<const Eigen::MatrixXd>(Eigen::MatrixXd(g));
  if (adjacencyMatrix->cols() != adjacencyMatrix->rows()) {
    throw std::runtime_error("Invalid adjacency matrix - not square.");
  }
  std::size_t n = adjacencyMatrix->rows();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i; j < n; ++j) {
      if (i == j && (*adjacencyMatrix)(i, j) != 0) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      } else if ((*adjacencyMatrix)(i, j) != (*adjacencyMatrix)(j, i) ||
                 ((*adjacencyMatrix)(i, j) != 0 &&
                  (*adjacencyMatrix)(i, j) != 1)) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      }
    }
  }
  return adjacencyMatrix;
}

const std::shared_ptr<const Eigen::MatrixXd>
Graph::generateAdjacencyMatrix(const Eigen::MatrixXd g) {
  auto adjacencyMatrix = std::make_shared<const Eigen::MatrixXd>(g);
  if (adjacencyMatrix->cols() != adjacencyMatrix->rows()) {
    throw std::runtime_error("Invalid adjacency matrix - not square.");
  }
  std::size_t n = adjacencyMatrix->rows();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i; j < n; ++j) {
      if (i == j && (*adjacencyMatrix)(i, j) != 0) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      } else if ((*adjacencyMatrix)(i, j) != (*adjacencyMatrix)(j, i) ||
                 ((*adjacencyMatrix)(i, j) != 0 &&
                  (*adjacencyMatrix)(i, j) != 1)) {
        throw std::runtime_error(
            "Error: Invalid adjacency matrix - invalid entries.");
      }
    }
  }
  return adjacencyMatrix;
}

const std::shared_ptr<const Eigen::MatrixXd> Graph::generateDegreeMatrix(
    const std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix) {
  std::size_t n = adjacencyMatrix->rows();
  auto degreeMatrix =
      std::make_shared<Eigen::MatrixXd>(Eigen::MatrixXd::Zero(n, n));
  for (std::size_t i = 0; i < n; ++i) {
    (*degreeMatrix)(i, i) = std::accumulate(adjacencyMatrix->col(i).begin(),
                                            adjacencyMatrix->col(i).end(), 0);
  };
  return degreeMatrix;
}

const bool Graph::connectedGraph(
    const std::shared_ptr<const Eigen::MatrixXd> adjacencyMatrix) {
  std::size_t order = adjacencyMatrix->rows();
  std::vector<bool> visited(order, false);
  std::deque<int> queue = {0};
  visited[0] = true;
  while (!queue.empty()) {
    std::size_t curr = queue.front();
    queue.pop_front();
    for (std::size_t i = 0; i < order; ++i) {
      if ((*adjacencyMatrix)(curr, i) != 0 && !visited[i]) {
        visited[i] = true;
        queue.push_back(i);
      }
    }
  }
  for (bool node : visited) {
    if (!node) {
      return false;
    }
  }
  return true;
}

Graph::Graph(const std::initializer_list<std::initializer_list<double>> g) try
    : adjacencyMatrix(Graph::generateAdjacencyMatrix(g)), order(g.size()),
      degreeMatrix(Graph::generateDegreeMatrix(adjacencyMatrix)),
      laplacianMatrix(
          std::make_shared<Eigen::MatrixXd>(*degreeMatrix - *adjacencyMatrix)),
      connected(Graph::connectedGraph(adjacencyMatrix)) {
} catch (const std::runtime_error &e) {
  std::cerr << e.what() << std::endl;
}

Graph::Graph(const Eigen::MatrixXd g) try
    : adjacencyMatrix(Graph::generateAdjacencyMatrix(g)), order(g.size()),
      degreeMatrix(Graph::generateDegreeMatrix(adjacencyMatrix)),
      laplacianMatrix(
          std::make_shared<Eigen::MatrixXd>(*degreeMatrix - *adjacencyMatrix)),
      connected(Graph::connectedGraph(adjacencyMatrix)) {
} catch (const std::runtime_error &e) {
  std::cerr << e.what() << std::endl;
}

const std::shared_ptr<const Eigen::MatrixXd> Graph::getAdjacencyMatrix() const {
  return adjacencyMatrix;
}
const std::shared_ptr<const Eigen::MatrixXd> Graph::getDegreeMatrix() const {
  return degreeMatrix;
}
const std::shared_ptr<const Eigen::MatrixXd> Graph::getLaplacianMatrix() const {
  return laplacianMatrix;
}

const bool Graph::isConnected() const { return connected; }

Graph Graph::randomGraph(std::size_t order, double p) {
  std::random_device rd;
  std::mt19937 gen(rd());
  assert(p >= 0 && 1 <= p);
  std::bernoulli_distribution d(p);
  Eigen::MatrixXd adj = Eigen::MatrixXd::Zero(order, order);
  for (std::size_t i = 0; i < order; ++i) {
    for (std::size_t j = i + 1; j < order; ++j) {
      adj(i, j) = d(gen);
      adj(j, i) = adj(i, j);
    }
  }
  std::cout << adj(1, 0) << std::endl;
  return Graph(adj);
}

const std::size_t Graph::getOrder() const { return order; }

Graph Graph::randomGraph(std::size_t order, double p, int k) {
  std::random_device rd;
  std::mt19937 gen(rd());
  assert(p >= 0 && 1 >= p);
  std::bernoulli_distribution d(p);
  Eigen::MatrixXd adj = Eigen::MatrixXd::Zero(order, order);
  for (std::size_t i = 0; i < order; ++i) {
    for (std::size_t j = i + 1; j < order; ++j) {
      if ((j - i) & k != 0) {
        adj(i, j) = d(gen);
        adj(j, i) = adj(i, j);
      }
    }
  }
  std::cout << adj(1, 0) << std::endl;
  return Graph(adj);
}

Graph Graph::prettyRandomGraph(std::size_t order,double p, int k){
  std::random_device rd;
  std::mt19937 gen(rd());
  assert(p >= 0 && 1 >= p);
  std::bernoulli_distribution d(p);
  Eigen::MatrixXd adj = Eigen::MatrixXd::Zero(order, order);
  for (int i = 0; i < order; ++i) {
    for (int j = i + 1; j < i + k; ++j) {
      adj(i, j%order) = d(gen);
      adj(j%order, i) = adj(i, j%order);
    }
  }
  std::cout << adj(1, 0) << std::endl;
  return Graph(adj);
}