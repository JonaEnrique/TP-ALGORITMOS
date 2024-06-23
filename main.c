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
        puts("Indice antes de cargar a memoria:");
        mostrarArchivosSociosIdx("archivos/socios.idx");
        indCargar(&indiceSocios,"archivos/socios.idx");
        puts("\nArchivo socios.dat:");
        mostrarArchivosSocios("archivo/socios.dat");
        //fclose(pIdx);
    }

//    printf("\n\n\n\n");
//    recorrerEnOrdenInversoArbol(&(indiceSocios.arbol), NULL, imprimirConForma);
//    printf("\n\n\n\n");

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
    unsigned* i = (unsigned*) info;
    printf("%*s-%3u-\n",n*3,"", *i);
}

void imprimir(void * info, unsigned tam, unsigned n, void * params)
{
    tSocio * i = (tSocio*) info;
    printf("-%ld-%s-", i->dni, i->nombres);
}

void mostrarArchivosSociosIdx(const char* pathArch)
{
    void* actSocio = malloc(sizeof(long) + sizeof(unsigned));
    FILE* pf = fopen("archivos/socios.idx","rb");
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

