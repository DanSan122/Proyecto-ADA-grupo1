#define DLLADA_EXPORTS
#include "dll-ada.h"
#include "algPrim.h"
#include <vector>
#include <limits>
#include <utility>
#include <cstring> // Para memcpy

// Función principal de Prim
std::vector<std::pair<int, int>> algPrim(int n, const std::vector<std::vector<double>>& graph) {
    std::vector<std::pair<int, int>> mstEdges;
    std::vector<bool> inMST(n, false);
    std::vector<double> minWeight(n, std::numeric_limits<double>::max());
    std::vector<int> parent(n, -1);
    minWeight[0] = 0;

    for (int i = 0; i < n; ++i) {
        double minVal = std::numeric_limits<double>::max();
        int u = -1;

        // Encontrar el nodo no visitado con el menor peso
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && minWeight[v] < minVal) {
                minVal = minWeight[v];
                u = v;
            }
        }

        if (u == -1) break; // Todos los nodos procesados
        inMST[u] = true;

        // Si tiene un padre, agregar la arista al MST
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

    return mstEdges;
}

// Funciones auxiliares para conversión (C++ interno)
std::vector<std::vector<double>> convertir_input(const double* input, int n) {
    std::vector<std::vector<double>> graph(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = input[i * n + j];
        }
    }
    return graph;
}

void convertir_output(const std::vector<std::pair<int, int>>& resultado, int* output) {
    int index = 0;
    for (const auto& edge : resultado) {
        output[index++] = edge.first;
        output[index++] = edge.second;
    }
}

// Funciones expuestas a través de extern "C"
extern "C" {

    DLLADA_API void ejecutarPrim(int n, const double* input, int* output) {
        // Convertir la entrada (plana) a una estructura compatible con C++
        auto graph = convertir_input(input, n);

        // Ejecutar el algoritmo
        auto resultado = algPrim(n, graph);

        // Convertir el resultado (estructura C++) a una salida plana
        convertir_output(resultado, output);
    }

}
