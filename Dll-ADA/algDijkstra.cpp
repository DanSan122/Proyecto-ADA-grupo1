#define DLLADA_EXPORTS
#include "dll-ada.h"
#include "algDijkstra.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>

// Métodos de la clase Graph
std::vector<int> Graph::adyacentes(int nodo) {
    std::vector<int> vecinos;
    for (const auto& par : adj_list[nodo]) {
        vecinos.push_back(par.first);
    }
    return vecinos;
}

int Graph::peso(int nodo1, int nodo2) {
    for (const auto& par : adj_list[nodo1]) {
        if (par.first == nodo2) {
            return par.second;
        }
    }
    return std::numeric_limits<int>::max();
}

std::vector<int> Graph::nodos() {
    std::vector<int> nodos;
    for (const auto& par : adj_list) {
        nodos.push_back(par.first);
    }
    return nodos;
}

void Graph::agregar_nodo(int nodo) {
    adj_list[nodo] = std::vector<std::pair<int, int>>();
}

void Graph::agregar_arista(int nodo1, int nodo2, int peso) {
    adj_list[nodo1].push_back({ nodo2, peso });
}

// Algoritmo de Dijkstra
std::pair<std::map<int, int>, std::map<int, int>> algDijkstra(Graph& G, int origen) {
    std::map<int, int> distancias;
    std::map<int, int> previo;
    std::map<int, bool> visitado;
    std::vector<std::pair<int, int>> cola_prioridad;

    for (int nodo : G.nodos()) {
        distancias[nodo] = std::numeric_limits<int>::max();
        previo[nodo] = -1;
        visitado[nodo] = false;
    }
    distancias[origen] = 0;
    cola_prioridad.push_back({ origen, 0 });

    while (!cola_prioridad.empty()) {
        std::sort(cola_prioridad.begin(), cola_prioridad.end(),
            [](std::pair<int, int> left, std::pair<int, int> right) {
                return left.second < right.second;
            });
        int actual = cola_prioridad.front().first;
        cola_prioridad.erase(cola_prioridad.begin());
        visitado[actual] = true;

        for (int vecino : G.adyacentes(actual)) {
            if (!visitado[vecino]) {
                int costo = G.peso(actual, vecino);
                int nueva_distancia = distancias[actual] + costo;

                if (nueva_distancia < distancias[vecino]) {
                    distancias[vecino] = nueva_distancia;
                    previo[vecino] = actual;
                    cola_prioridad.push_back({ vecino, nueva_distancia });
                }
            }
        }
    }
    return { distancias, previo };
}

// Wrapper para interoperabilidad
extern "C" {
    DLLADA_API void* crearGrafoDijkstra() {
        return new Graph();
    }

    DLLADA_API void liberarGrafoDijkstra(void* grafo) {
        delete static_cast<Graph*>(grafo);
    }

    DLLADA_API void agregarNodoDijkstra(void* grafo, int nodo) {
        static_cast<Graph*>(grafo)->agregar_nodo(nodo);
    }

    DLLADA_API void agregarAristaDijkstra(void* grafo, int nodo1, int nodo2, int peso) {
        static_cast<Graph*>(grafo)->agregar_arista(nodo1, nodo2, peso);
    }

    DLLADA_API void ejecutarDijkstra(void* grafo, int origen, int* out_distancias, int* out_previo, int n) {
        Graph* G = static_cast<Graph*>(grafo);

        // Ejecutar el algoritmo
        auto resultado = algDijkstra(*G, origen);

        // Convertir el resultado
        for (int i = 0; i < n; ++i) {
            out_distancias[i] = resultado.first.count(i) ? resultado.first.at(i) : std::numeric_limits<int>::max();
            out_previo[i] = resultado.second.count(i) ? resultado.second.at(i) : -1;
        }
    }
}
