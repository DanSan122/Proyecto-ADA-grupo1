#pragma once

#include <vector>
#include <tuple>
#include <map>
#include <limits>
#include <utility>

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

class Graph {
public:
    std::vector<int> adyacentes(int nodo);
    int peso(int nodo1, int nodo2);
    std::vector<int> nodos();
    void agregar_nodo(int nodo);
    void agregar_arista(int nodo1, int nodo2, int peso);

private:
    std::map<int, std::vector<std::pair<int, int>>> adj_list;
};

// Funciones estilo C expuestas
extern "C" {
    DLLADA_API void* crearGrafoDijkstra();
    DLLADA_API void liberarGrafoDijkstra(void* grafo);
    DLLADA_API void agregarNodoDijkstra(void* grafo, int nodo);
    DLLADA_API void agregarAristaDijkstra(void* grafo, int nodo1, int nodo2, int peso);
    DLLADA_API void ejecutarDijkstra(void* grafo, int origen, int* out_distancias, int* out_previo, int n);
}
