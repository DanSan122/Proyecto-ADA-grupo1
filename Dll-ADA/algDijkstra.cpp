#include "dll-ada.h"
#include "algDijkstra.h"
#include <algorithm>

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
        std::sort(cola_prioridad.begin(), cola_prioridad.end(), [](std::pair<int, int> left, std::pair<int, int> right) {
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
