#ifndef GENERACIONINDICE_H_INCLUDED
#define GENERACIONINDICE_H_INCLUDED
#include "TiposDeDatos/utilidades.h"
#include "TiposDeDatos/socio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int txtABin(const char* pathTxt,const char* pathBin);
void trozarCamposLongVariable(tSocio* actSocio,char* registro);
int construirIndice(const char* pathBin);
int compararUnsigned(const void* a,const void* b);

#endif // GENERACIONINDICE_H_INCLUDED
