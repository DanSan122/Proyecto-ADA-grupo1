#include "dll-ada.h"
#include "greedyTSP.h"
#include <vector>
#include <limits>
#include <cmath>

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif


DLLADA_API std::pair<std::vector<int>, double> algGreedyTSP(int start, const std::vector<std::vector<double>>& graph);


DLLADA_API std::pair<std::vector<int>, double> algGreedyTSP(int start, const std::vector<std::vector<double>>& graph) {
    int n = graph.size(); 
    std::vector<bool> visited(n, false);
    std::vector<int> path; 
    double totalCost = 0.0; 

    int current = start; 
    visited[current] = true;
    path.push_back(current);

    for (int i = 1; i < n; ++i) {
        double minCost = std::numeric_limits<double>::max();
        int nextNode = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[current][j] < minCost) {
                minCost = graph[current][j];
                nextNode = j;
            }
        }

        if (nextNode != -1) {
            visited[nextNode] = true;
            path.push_back(nextNode);
            totalCost += minCost;
            current = nextNode;
        }
    }

    totalCost += graph[current][start];
    path.push_back(start);

    return { path, totalCost };
}
