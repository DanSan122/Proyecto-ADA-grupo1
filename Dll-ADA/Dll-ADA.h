#ifndef DLLADA_H
#define DLLADA_H

#include "algDijkstra.h"
#include "algPrim.h"
#include "algKruskal.h"
#include "greedyTSP.h"
#include "dinamicaTSP.h"

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

extern "C" {

	// Cálculo de la distancia Haversine
	DLLADA_API double calculoHaversine(double lat1, double lon1, double lat2, double lon2);

	// Algoritmo de Dijkstra
	DLLADA_API void ejecutarDijkstra(void* grafo, int origen, int* out_distancias, int* out_previo, int n);

	// Algoritmo de Kruskal
	DLLADA_API void ejecutarKruskal(int n, const int* input, int num_aristas, int* output);

	// Algoritmo de Prim
	DLLADA_API void ejecutarPrim(int n, const double* input, int* output);

	// Algoritmo TSP Greedy
	DLLADA_API void ejecutarGreedyTSP(GreedyTSPInput* input);

	// Algoritmo TSP con programación dinámica
	DLLADA_API void ejecutarDinamicaTSP(TSPInput* input);

}

#endif // DLLADA_H
