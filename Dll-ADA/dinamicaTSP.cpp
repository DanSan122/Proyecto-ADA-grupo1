#define DLLADA_EXPORTS
#include "dll-ada.h"
#include "dinamicaTSP.h"
#include <vector>
#include <climits>
#include <cmath>
#include <cstring>

// Estructura para manejar los subconjuntos de ciudades
struct SubSet {
    int data;
    SubSet* next;
};

// Función para crear un subconjunto de ciudades
static SubSet* Create_element_SubSet(int i) {
    SubSet* temp = new SubSet;
    temp->data = i;
    temp->next = nullptr;
    return temp;
}

// Función para verificar si el bit j de i está activado (1)
static int isHit(int i, int j) {
    while (j > 0) {
        i = i / 2;
        --j;
    }
    return (i % 2 == 1) ? 1 : 0;
}

// Función para crear todos los subconjuntos de ciudades
static void Create_SubSet(int n, std::vector<SubSet*>& subsets) {
    subsets.resize(pow(2, n - 1));
    for (int i = 0; i < pow(2, n - 1); ++i) {
        SubSet* Head = nullptr;
        SubSet* Tail = nullptr;
        for (int j = 0; j < n; ++j) {
            if (isHit(i, j)) {
                SubSet* temp = Create_element_SubSet(j + 1);
                if (Head == nullptr)
                    Head = Tail = temp;
                else {
                    Tail->next = temp;
                    Tail = temp;
                }
            }
        }
        subsets[i] = Head;
    }
}

// Implementación del algoritmo TSP con programación dinámica
static std::vector<int> DP_tsp_internal(const std::vector<std::vector<int>>& distancias, int& totalCost) {
    int n = distancias.size();
    int subsetCount = pow(2, n - 1);
    std::vector<std::vector<int>> A(subsetCount, std::vector<int>(n, INT_MAX));
    std::vector<std::vector<int>> Sol(subsetCount, std::vector<int>(n, -1));

    std::vector<SubSet*> subsets;
    Create_SubSet(n, subsets);

    for (int i = 0; i < subsetCount; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0) {
                A[i][j] = distancias[0][j];
            }
            else {
                SubSet* temp = subsets[i];
                int minval = INT_MAX;
                while (temp != nullptr) {
                    int x = distancias[temp->data][j] + A[i - (int)pow(2, temp->data - 1)][temp->data];
                    if (x < minval) {
                        minval = x;
                        Sol[i][j] = temp->data;
                    }
                    temp = temp->next;
                }
                A[i][j] = minval;
            }
        }
    }

    // Reconstrucción de la solución
    int currentSubset = subsetCount - 1;
    int currentCity = 0;
    std::vector<int> path = { 0 };

    while (currentSubset > 0) {
        int nextCity = Sol[currentSubset][currentCity];
        path.push_back(nextCity);
        currentSubset -= pow(2, nextCity - 1);
        currentCity = nextCity;
    }
    path.push_back(0);

    totalCost = A[subsetCount - 1][0];
    return path;
}

// Función de integración para JavaScript
DLLADA_API void ejecutarDinamicaTSP(TSPInput* input) {
    // Reconstruir la matriz de distancias desde el arreglo plano
    std::vector<std::vector<int>> distancias(input->n, std::vector<int>(input->n));
    for (int i = 0; i < input->n; ++i) {
        for (int j = 0; j < input->n; ++j) {
            distancias[i][j] = input->matrix[i * input->n + j];
        }
    }

    // Ejecutar el algoritmo
    int totalCost;
    std::vector<int> path = DP_tsp_internal(distancias, totalCost);

    // Copiar el resultado a las estructuras de salida
    std::memcpy(input->path, path.data(), path.size() * sizeof(int));
    input->totalCost = totalCost;
}