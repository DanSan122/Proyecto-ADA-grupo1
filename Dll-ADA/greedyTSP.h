#pragma once

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

#include <vector>
#include <utility>


DLLADA_API std::pair<std::vector<int>, double> algGreedyTSP(int start, const std::vector<std::vector<double>>& graph);



