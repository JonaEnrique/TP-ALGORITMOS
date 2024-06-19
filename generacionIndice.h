#ifndef GENERACIONINDICE_H_INCLUDED
#define GENERACIONINDICE_H_INCLUDED
#include "TiposDeDatos/utilidades.h"
#include "TiposDeDatos/socio.h"
#include "TiposDeDatos/indice.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int txtABin(const char* pathTxt,const char* pathBin);
void trozarCamposLongVariable(tSocio* actSocio,char* registro);
int cargarIndiceDesdeArchivoMaestro(const char* pathArch,tIndice* ind);
//: Carga el indide desde el archivo maestro desordenado


#endif // GENERACIONINDICE_H_INCLUDED
