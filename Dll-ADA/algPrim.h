#pragma once

#include <vector>
#include <utility>
#include <cstdint> // Para tipos estándar como int32_t

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

// Función principal de Prim (solo para uso interno en C++)
std::vector<std::pair<int, int>> algPrim(int n, const std::vector<std::vector<double>>& graph);

// Funciones estilo C expuestas
extern "C" {
    // Ejecutar el algoritmo Prim desde un entorno externo
    DLLADA_API void ejecutarPrim(int n, const double* input, int* output);
}
