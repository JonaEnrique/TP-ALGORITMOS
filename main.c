#include <stdio.h>
#include <stdlib.h>
#include "TiposDeDatos\Arbol.h"
#include "TiposDeDatos\fecha.h"
#include "TiposDeDatos\socio.h"
#include "generacionIndice.h"

void imprimirConForma(void * info, unsigned tam, unsigned n, void * params);
void imprimir(void * info, unsigned tam, unsigned n, void * params);
void mostrarArchivosSociosIdx(const char* pathArch);

int main()
{
    FILE* pIdx;
    char pathArchCsv[50];
    tIndice indiceSocios;

    indCrear(&indiceSocios, sizeof(long), compararSocios);
    pIdx = fopen("archivos/socios.idx","rb");

    if(!pIdx)
    {
        printf("Ingrese el PATH del archivo de socios en formato .csv: ");
        scanf("%s",pathArchCsv);
        txtABin(pathArchCsv,"archivos/socios.dat");
        //---------------------------------------
        puts("archivo binario socios.dat\n");
        mostrarArchivosSocios("archivos/socios.dat");
        //---------------------------------------
        cargarIndiceDesdeArchivoMaestro("archivos/socios.dat", &indiceSocios);
    } else
    {
        fclose(pIdx);

        puts("\nArchivo socios.dat:\n");
        mostrarArchivosSocios("archivos/socios.dat");

        puts("\nArchivo socios.idx antes de indCargar:\n");
        mostrarArchivosSociosIdx("archivos/socios.idx");

        indCargar(&indiceSocios,"archivos/socios.idx");

        puts("\nArchivo socios.idx despues de indCargar:\n");
        mostrarArchivosSociosIdx("archivos/socios.idx");
    }

    printf("\n\n\n\n");
    recorrerEnOrdenInversoArbol(&(indiceSocios.arbol), NULL, imprimirConForma);
    printf("\n\n\n\n");

    indGrabar(&indiceSocios, "archivos/socios.idx");

    puts("\nIndice despues de grabar en archivo:");
    mostrarArchivosSociosIdx("archivos/socios.idx");

    //menu
    //graba y guarda menu

    fclose(pIdx);

    return 0;
}

void imprimirConForma(void * info, unsigned tam, unsigned n, void * params)
{
    long* dni = (long*) info;
    unsigned* tamInfo = (unsigned*)(info + sizeof(long));

    printf("%*s-%3ld %u-\n",n*3,"", *dni, *tamInfo);
}

void imprimir(void * info, unsigned tam, unsigned n, void * params)
{
    tSocio * i = (tSocio*) info;
    printf("-%ld-%s-", i->dni, i->nombres);
}

void mostrarArchivosSociosIdx(const char* pathArch)
{
    void* actSocio = malloc(sizeof(long) + sizeof(unsigned));
    if(!actSocio)return;
    FILE* pf = fopen("archivos/socios.idx","rb");

    if(!pf)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    fread(actSocio,sizeof(long) + sizeof(unsigned),1,pf);
    while(!feof(pf))
    {
        printf("%ld %d\n",
            *(long*)actSocio,
            *(unsigned*)(actSocio + sizeof(long)));
        fread(actSocio,sizeof(long) + sizeof(unsigned),1,pf);
    }

    free(actSocio);
    fclose(pf);
    return;
}

