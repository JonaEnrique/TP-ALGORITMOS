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
//: inicializa la estructura a �ndice vac�o y almacena en la estructura de �ndice el tama�o de la clave gen�rica a utilizar y la funci�n de comparaci�n.
int indInsertar (tIndice* ind, void *clave, unsigned nroReg);
//: inserta en orden el registro reg_ind seg�n la clave
int indEliminar (tIndice* ind, void *clave, unsigned *nroReg);
//: elimina la entrada del �ndice correspondiente a la clave y devuelve en nro_reg el n�mero de registro asociado
int indBuscar (const tIndice* ind, void *clave, unsigned *nroReg);
//: Busca la clave recibida por par�metro y devuelve en nro_reg el n�mero de registro asociado
int indCargar (tIndice* ind, const char* path);
//: Carga el �ndice a partir de un archivo binario ordenado (t�picamente de extensi�n �.idx�), donde cada registro del archivo tiene la estructura definida, clave-nro_reg
int indGrabar (const tIndice* ind, const char* path);
//: Graba un archivo binario ordenado (t�picamente de extensi�n �.idx�) con el contenido del �ndice con la estructura clave-nro_reg
void indVaciar (tIndice* ind);
//: deja el �ndice en su estado de vac�o.
int indRecorrer (const tIndice* ind, Accion accion, void* param);
//: Recorre el �ndice en orden y llama a acci�n para cada registro del mismo.

#endif // INDICE_H_INCLUDED
