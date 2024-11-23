#include "algPrim.h"
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>

double algPrim(int n, const std::vector<std::vector<double>>& graph, std::vector<std::pair<int, int>>& mstEdges) {
    
    std::vector<bool> inMST(n, false); // Si el nodo está incluido en el MST
    std::vector<double> minWeight(n, std::numeric_limits<double>::max()); // Peso mínimo para cada nodo
    std::vector<int> parent(n, -1); // Nodo padre para reconstruir el MST
    minWeight[0] = 0; // El nodo inicial tiene peso 0
    double totalWeight = 0;

    // Prim's algorithm
    for (int i = 0; i < n; ++i) {
        // Encontrar el nodo con el peso mínimo no incluido en el MST
        double minVal = std::numeric_limits<double>::max();
        int u = -1;

        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && minWeight[v] < minVal) {
                minVal = minWeight[v];
                u = v;
            }
        }

        // Incluir el nodo en el MST
        if (u == -1) break; // Si no se encuentra un nodo, el grafo no está conectado
        inMST[u] = true;
        totalWeight += minVal;

        // Agregar el borde al MST si no es el nodo inicial
        if (parent[u] != -1) {
            mstEdges.push_back({ parent[u], u });
        }

        // Actualizar los pesos mínimos para los nodos adyacentes
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && graph[u][v] < minWeight[v]) {
                minWeight[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    return totalWeight;
}
