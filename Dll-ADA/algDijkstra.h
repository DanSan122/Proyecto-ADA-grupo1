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

class DLLADA_API Graph {
public:
    std::vector<int> adyacentes(int nodo);
    int peso(int nodo1, int nodo2);
    std::vector<int> nodos();
    void agregar_nodo(int nodo);
    void agregar_arista(int nodo1, int nodo2, int peso);

private:
    std::map<int, std::vector<std::pair<int, int>>> adj_list;
};

DLLADA_API std::pair<std::map<int, int>, std::map<int, int>> algDijkstra(Graph& G, int origen);

