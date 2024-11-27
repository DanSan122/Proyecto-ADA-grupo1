#include "dll-ada.h"
#include "algKruskal.h"
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstring> // Para memcpy

// Clase Grafo
Grafo::Grafo(int n) : n(n) {}

void Grafo::agregar_arista(int u, int v, int peso) {
    aristas.emplace_back(peso, u, v);
}

std::vector<std::tuple<int, int, int>> Grafo::obtener_aristas() const {
    return aristas;
}

// Clase UnionFind
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

// Algoritmo principal
std::vector<std::tuple<int, int, int>> algKruskal(int n, const std::vector<std::tuple<int, int, int>>& aristas) {
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

// Funciones auxiliares para interoperabilidad C
extern "C" {

    void* crearGrafo(int n) {
        return new Grafo(n);
    }

    void agregarArista(void* grafo, int u, int v, int peso) {
        static_cast<Grafo*>(grafo)->agregar_arista(u, v, peso);
    }

    void liberarGrafo(void* grafo) {
        delete static_cast<Grafo*>(grafo);
    }

    void ejecutarKruskal(int n, const int* input, int num_aristas, int* output) {
        // Convertir input plano a vector de tuplas
        std::vector<std::tuple<int, int, int>> aristas;
        for (int i = 0; i < num_aristas; ++i) {
            int peso = input[i * 3];
            int u = input[i * 3 + 1];
            int v = input[i * 3 + 2];
            aristas.emplace_back(peso, u, v);
        }

        // Ejecutar el algoritmo
        auto resultado = algKruskal(n, aristas);

        // Convertir el resultado a un arreglo plano
        int index = 0;
        for (const auto& arista : resultado) {
            output[index++] = std::get<0>(arista); // Peso
            output[index++] = std::get<1>(arista); // Nodo u
            output[index++] = std::get<2>(arista); // Nodo v
        }
    }
}
