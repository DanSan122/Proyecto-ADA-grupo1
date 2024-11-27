#include "greedyTSP.h"
#include <vector>
#include <limits>
#include <cmath>
#include <cstring>

// Implementación del algoritmo TSP Greedy
static std::vector<int> algGreedyTSP_internal(const std::vector<std::vector<double>>& distanceMatrix, double& totalCost) {
    int n = distanceMatrix.size();
    if (n == 0) {
        totalCost = 0.0;
        return {};
    }

    std::vector<bool> visited(n, false); // Ciudades visitadas
    std::vector<int> path;               // Recorrido final
    totalCost = 0.0;                     // Costo total del recorrido

    // Paso 1: Inicializar con la ciudad 0 y la ciudad más alejada
    int start = 0;
    visited[start] = true;
    path.push_back(start);

    int farthestCity = -1;
    double maxDistance = -1.0;
    for (int i = 0; i < n; ++i) {
        if (i != start && distanceMatrix[start][i] > maxDistance) {
            maxDistance = distanceMatrix[start][i];
            farthestCity = i;
        }
    }

    visited[farthestCity] = true;
    path.push_back(farthestCity);
    totalCost += distanceMatrix[start][farthestCity];

    // Paso 2: Iterar mientras haya ciudades no visitadas
    while (path.size() < n) {
        int nextCity = -1;
        double maxInsertionCost = -1.0;
        int insertionIndex = -1;

        // Buscar la ciudad no visitada más lejana y su posición óptima
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;

            for (size_t j = 0; j < path.size(); ++j) {
                int currentCity = path[j];
                int nextCityInPath = path[(j + 1) % path.size()];

                double insertionCost =
                    distanceMatrix[currentCity][i] +
                    distanceMatrix[i][nextCityInPath] -
                    distanceMatrix[currentCity][nextCityInPath];

                if (insertionCost > maxInsertionCost) {
                    maxInsertionCost = insertionCost;
                    nextCity = i;
                    insertionIndex = j + 1;
                }
            }
        }

        // Insertar la ciudad en la posición óptima
        totalCost += maxInsertionCost;
        path.insert(path.begin() + insertionIndex, nextCity);
        visited[nextCity] = true;
    }

    return path;
}

// Función de integración para JavaScript
DLLADA_API void ejecutarGreedyTSP(GreedyTSPInput* input) {
    // Reconstruir la matriz de distancias desde el arreglo plano
    std::vector<std::vector<double>> distanceMatrix(input->n, std::vector<double>(input->n));
    for (int i = 0; i < input->n; ++i) {
        for (int j = 0; j < input->n; ++j) {
            distanceMatrix[i][j] = input->matrix[i * input->n + j];
        }
    }

    // Ejecutar el algoritmo
    double totalCost;
    std::vector<int> path = algGreedyTSP_internal(distanceMatrix, totalCost);

    // Copiar el resultado a las estructuras de salida
    std::memcpy(input->path, path.data(), path.size() * sizeof(int));
    input->totalCost = totalCost;
}