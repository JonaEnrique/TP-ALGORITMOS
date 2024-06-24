#include <stdio.h>
#include <stdlib.h>
#include "TiposDeDatos\Arbol.h"
#include "TiposDeDatos\fecha.h"
#include "TiposDeDatos\socio.h"
#include "menuSocio.h"
#include "generacionIndice.h"

int main()
{
    FILE* pIdx;
    char pathArchCsv[50];
    tIndice indiceSocios;
    tFecha fechaDeProceso;

    indCrear(&indiceSocios, sizeof(long), compararSocios);
    pIdx = fopen("archivos/socios.idx","rb");

    if(!pIdx)
    {
        printf("Ingrese el PATH del archivo de socios en formato .csv: ");
        scanf("%s",pathArchCsv);
        txtABin(pathArchCsv,"archivos/socios.dat");
        cargarIndiceDesdeArchivoMaestro("archivos/socios.dat", &indiceSocios);
    } else
    {
        fclose(pIdx);
        indCargar(&indiceSocios,"archivos/socios.idx");
    }

    printf("Ingrese fecha de hoy (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &fechaDeProceso.dia, &fechaDeProceso.mes, &fechaDeProceso.anio);

    menu_Socios("archivos/socios.dat", &indiceSocios, &fechaDeProceso);

    indGrabar(&indiceSocios, "archivos/socios.idx");

    indVaciar(&indiceSocios);

    return 0;
}



