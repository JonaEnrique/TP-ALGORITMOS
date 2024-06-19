#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED
#include "Arbol.h"
#include "utilidades.h"

typedef struct
{
    tArbol arbol;
    size_t tamClave;
    void *regInd;
    Cmp funcionComparacion;
} tIndice;

void indCrear (tIndice* ind, size_t tamClave, Cmp funcionComparacion);
//: inicializa la estructura a índice vacío y almacena en la estructura de índice el tamaño de la clave genérica a utilizar y la función de comparación.
int indInsertar (tIndice* ind, void *clave, unsigned nroReg);
//: inserta en orden el registro reg_ind según la clave
int indEliminar (tIndice* ind, void *clave, unsigned *nroReg);
//: elimina la entrada del índice correspondiente a la clave y devuelve en nro_reg el número de registro asociado
int indBuscar (const tIndice* ind, void *clave, unsigned *nroReg);
//: Busca la clave recibida por parámetro y devuelve en nro_reg el número de registro asociado
int indCargar (tIndice* ind, const char* path);
//: Carga el índice a partir de un archivo binario ordenado (típicamente de extensión ‘.idx’), donde cada registro del archivo tiene la estructura definida, clave-nro_reg
int indGrabar (const tIndice* ind, const char* path);
//: Graba un archivo binario ordenado (típicamente de extensión ‘.idx’) con el contenido del índice con la estructura clave-nro_reg
void indVaciar (tIndice* ind);
//: deja el índice en su estado de vacío.
int indRecorrer (const tIndice* ind, Accion accion, void* param);
//: Recorre el índice en orden y llama a acción para cada registro del mismo.

#endif // INDICE_H_INCLUDED
