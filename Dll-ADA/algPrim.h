#pragma once

#include <vector>
#include <utility>
#include <limits>

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

DLLADA_API double algPrim(int n, const std::vector<std::vector<double>>& graph, std::vector<std::pair<int, int>>& mstEdges);


