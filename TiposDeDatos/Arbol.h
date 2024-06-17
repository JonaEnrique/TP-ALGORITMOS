#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
}tNodoArbol;

typedef tNodoArbol *tArbol;

void crearArbol(tArbol *pA);
int insertarArbol(tArbol *pA, const void *pd, unsigned tam, Cmp funcionComparacion);
int buscarElemArbol(const tArbol *pA, void *pd, unsigned tam,Cmp funcionComparacion);
int cargarArchivoBinOrdenadoArbol(tArbol *pA, const char * path,unsigned tamInfo);
int eliminarElemArbol(tArbol *pA, void *pd, unsigned tam,Cmp funcionComparacion);
void vaciarArbol(tArbol* pA);
void recorrerEnOrdenArbol(const tArbol *pA, unsigned param1, void *param2,Accion accion);
void escribirIndiceEnArchivo(void *pf,unsigned tam,void *pd);

#endif // ARBOL_H_INCLUDED
