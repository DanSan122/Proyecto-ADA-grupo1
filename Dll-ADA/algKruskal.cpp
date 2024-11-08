#include "dll-ada.h"
#include "algKruskal.h"
#include <algorithm>

Grafo::Grafo(int n) : n(n) {}

void Grafo::agregar_arista(int u, int v, int peso) {
    aristas.emplace_back(peso, u, v);
}

std::vector<std::tuple<int, int, int>> Grafo::obtener_aristas() const {
    return aristas;
}

UnionFind::UnionFind(int tamaño) {
    parent.resize(tamaño);
    rank.resize(tamaño, 0);
    for (int i = 0; i < tamaño; ++i) {
        parent[i] = i;
    }
}

int UnionFind::encontrar(int u) {
    if (parent[u] != u) {
        parent[u] = encontrar(parent[u]);
    }
    return parent[u];
}

void UnionFind::unir(int u, int v) {
    int raiz_u = encontrar(u);
    int raiz_v = encontrar(v);
    if (raiz_u != raiz_v) {
        if (rank[raiz_u] > rank[raiz_v]) {
            parent[raiz_v] = raiz_u;
        }
        else if (rank[raiz_u] < rank[raiz_v]) {
            parent[raiz_u] = raiz_v;
        }
        else {
            parent[raiz_v] = raiz_u;
            rank[raiz_u]++;
        }
    }
}

DLLADA_API std::vector<std::tuple<int, int, int>> algKruskal(int n, const std::vector<std::tuple<int, int, int>>& aristas) {
    std::vector<std::tuple<int, int, int>> MST;
    Grafo G(n);
    UnionFind uf(n);

    for (const auto& arista : aristas) {
        G.agregar_arista(std::get<1>(arista), std::get<2>(arista), std::get<0>(arista));
    }

    auto aristas_ordenadas = G.obtener_aristas();
    std::sort(aristas_ordenadas.begin(), aristas_ordenadas.end());

    for (const auto& arista : aristas_ordenadas) {
        int peso = std::get<0>(arista);
        int u = std::get<1>(arista);
        int v = std::get<2>(arista);
        if (uf.encontrar(u) != uf.encontrar(v)) {
            uf.unir(u, v);
            MST.emplace_back(u, v, peso);
        }
    }

    return MST;
}