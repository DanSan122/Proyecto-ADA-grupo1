#pragma once
#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <tuple>

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

class Grafo {
public:
    int n;
    std::vector<std::tuple<int, int, int>> aristas;

    Grafo(int n);
    void agregar_arista(int u, int v, int peso);
    std::vector<std::tuple<int, int, int>> obtener_aristas() const;
};

class UnionFind {
public:
    std::vector<int> parent;
    std::vector<int> rank;

    UnionFind(int tamaño);
    int encontrar(int u);
    void unir(int u, int v);
};

extern "C" DLLADA_API std::vector<std::tuple<int, int, int>> algKruskal(int n, const std::vector<std::tuple<int, int, int>>& aristas);

#endif // KRUSKAL_H
