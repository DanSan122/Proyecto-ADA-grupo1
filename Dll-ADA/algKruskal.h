#pragma once

#include <vector>
#include <tuple>
#include <cstdint> // Para tipos estándar como int32_t

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

// Definición de la clase Grafo
class Grafo {
public:
    int n;
    std::vector<std::tuple<int, int, int>> aristas;

    Grafo(int n);
    void agregar_arista(int u, int v, int peso);
    std::vector<std::tuple<int, int, int>> obtener_aristas() const;
};

// Definición de la clase UnionFind
class UnionFind {
public:
    std::vector<int> parent;
    std::vector<int> rank;

    UnionFind(int tamaño);
    int encontrar(int u);
    void unir(int u, int v);
};

// Algoritmo principal de Kruskal
std::vector<std::tuple<int, int, int>> algKruskal(int n, const std::vector<std::tuple<int, int, int>>& aristas);

// Funciones estilo C expuestas
extern "C" {

    DLLADA_API void* crearGrafo(int n);
    DLLADA_API void agregarArista(void* grafo, int u, int v, int peso);
    DLLADA_API void liberarGrafo(void* grafo);

    DLLADA_API void ejecutarKruskal(int n, const int* input, int num_aristas, int* output);

}
