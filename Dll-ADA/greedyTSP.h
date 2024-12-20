#ifndef GREEDY_TSP_H
#define GREEDY_TSP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

    // Estructura para pasar los datos de manera simple
    typedef struct {
        int n;           // N�mero de ciudades
        double* matrix;  // Matriz de distancias plana
        int* path;       // Ruta resultante
        double totalCost; // Costo total del recorrido
    } GreedyTSPInput;

    // Funci�n de integraci�n para JavaScript
    DLLADA_API void ejecutarGreedyTSP(GreedyTSPInput* input);

#ifdef __cplusplus
}
#endif

#endif // GREEDY_TSP_H