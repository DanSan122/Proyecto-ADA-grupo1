// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DLLADA_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DLLADA_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef DLLADA_H
#define DLLADA_H

#include <vector>
#include <tuple>
#include <map>
#include <utility>
#include <algorithm>
#include "algDijkstra.h"

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif


DLLADA_API double calculoHaversine(double lat1, double lon1, double lat2, double lon2);
DLLADA_API std::pair<std::map<int, int>, std::map<int, int>> algDijkstra(Graph& G, int origen);
DLLADA_API std::vector<std::tuple<int, int, int>> algKruskal(int n, const std::vector<std::tuple<int, int, int>>& aristas);
DLLADA_API double algPrim(int n, const std::vector<std::vector<double>>& graph, std::vector<std::pair<int, int>>& mstEdges);
DLLADA_API std::pair<std::vector<int>, double> algGreedyTSP(int start, const std::vector<std::vector<double>>& graph);


#endif