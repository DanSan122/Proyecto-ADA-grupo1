#ifndef DINAMICA_TSP_H
#define DINAMICA_TSP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DLLADA_EXPORTS
#define DLLADA_API __declspec(dllexport)
#else
#define DLLADA_API __declspec(dllimport)
#endif

    // Definimos una estructura para pasar los datos de manera simple
    typedef struct {
        int n;           // Número de ciudades
        int* matrix;     // Matriz de distancias plana
        int* path;       // Ruta resultante
        int totalCost;   // Costo total del recorrido
    } TSPInput;

    // Función de integración para JavaScript
    DLLADA_API void ejecutarDinamicaTSP(TSPInput* input);

#ifdef __cplusplus
}
#endif

#endif // DINAMICA_TSP_H