#include "Arbol.h"

void crearArbol(tArbol *pA)
{
    return;
}

int insertarArbol(tArbol *pA, const void *pd, unsigned tam, Cmp funcionComparacion)
{
    return;
}
int buscarElemArbol(const tArbol *pA, void *pd, unsigned tam,Cmp funcionComparacion)
{
    return;
}
int cargarArchivoBinOrdenadoArbol(tArbol *pA, const char * path,unsigned tamInfo)
{
    return;
}
int eliminarElemArbol(tArbol *pA, void *pd, unsigned tam,Cmp funcionComparacion)
{
    return;
}

void vaciarArbol(tArbol* pA)
{
    if(!*pA)
        return;

    vaciarArbol(&(*pA)->izq);
    vaciarArbol(&(*pA)->der);
    free((*pA)->info);
    free(*pA);
    *pA = NULL;
}

void recorrerEnOrdenArbol(const tArbol *pA, unsigned param1, void *param2,Accion accion)
{
    return;
}
