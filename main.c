#include <stdio.h>
#include <stdlib.h>
#include "TiposDeDatos\Arbol.h"
#include "TiposDeDatos\fecha.h"
#include "TiposDeDatos\socio.h"
#include "generacionIndice.h"

int main()
{
    FILE* pIdx;
    char pathArchCsv[50];
    tIndice indiceSocios;

    indCrear(&indiceSocios,sizeof(long),compararSocios);
    pIdx = fopen("archivo/socios.idx","rb");

    if(!pIdx)
    {
        printf("Ingrese el PATH del archivo de socios en formato .csv: ");
        scanf("%s",pathArchCsv);
        txtABin(pathArchCsv,"archivo/socios.dat");
        cargarIndiceDesdeArchivoMaestro("archivo/socios.dat", &indiceSocios);
    } else
    {
        indCargar(&indiceSocios,"archivo/socios.idx");
        fclose(pIdx);
    }

    mostrarArchivosSocios("archivo/socios.dat");
    //menu
    //graba y guarda menu


    fclose(pIdx);
    return 0;
}
