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

void crearArbol(tArbol *pa);
int insertarArbol(tArbol *pa, const void *pd, unsigned tam, Cmp funcionComparacion);
int buscarElemArbol(const tArbol *pa, void *pd, unsigned tam,Cmp funcionComparacion);

int cargarArchivoBinOrdenadoArbol(tArbol *pa, const char * path,unsigned tamInfo);
unsigned leerDesdeArchivoBin(void ** d, void * pf, unsigned pos, void * params);
int cargarDesdeDatosOrdenadosRec(tArbol * pa, void * ds, Leer leer, int li, int ls, void * params);
int cargarDesdeDatosOrdenadosArbol(tArbol * p, void * ds, unsigned cantReg, Leer leer, void * params);



int eliminarElemArbol(tArbol *pa, void *pd, unsigned tam,Cmp funcionComparacion);
tNodoArbol ** buscarNodoArbol(const tArbol* pa, const void * d, Cmp funcionComparacion);
unsigned alturaArbolBin(const tArbol* pa);
int eliminarRaizArbol(tArbol *pa);
tNodoArbol ** mayorNodoArbol(const tArbol * pa);
tNodoArbol ** menorNodoArbol(const tArbol * pa);


void vaciarArbol(tArbol* pA);
//void recorrerEnOrdenArbol(const tArbol *pA, unsigned param1, void *param2,Accion accion);
void recorrerEnOrdenRecArbol(const tArbol * pa, unsigned n, void *params, Accion accion);
void recorrerEnOrdenArbol(const tArbol * pa, void * params, Accion accion);
void recorrerEnOrdenInversoRecArbol(const tArbol * p, unsigned n, void* params, Accion accion);
void recorrerEnOrdenInversoArbol(const tArbol * p, void * params, Accion accion);

//void escribirIndiceEnArchivo(void *pf,unsigned tam,void *pd);

#endif // ARBOL_H_INCLUDED
