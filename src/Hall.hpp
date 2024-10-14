#pragma once

#include "Graph.hpp"
#include "SparseGraph.hpp"
#include <eigen3/Eigen/Core>
#include <Spectra/SymEigsSolver.h>

template<typename T>
std::vector<double> Hall1D(SparseGraph<T>&);

template<typename T>
std::vector<std::pair<double,double>> Hall2D(SparseGraph<T>&);