#include <stdio.h>
#include <stdlib.h>
#include "TiposDeDatos\Arbol.h"
#include "TiposDeDatos\fecha.h"
#include "TiposDeDatos\socio.h"
#include "generacionIndice.h"

int main()
{
    void* reg=malloc(sizeof(unsigned)+sizeof(long));
    txtABin("archivos/socios.csv","archivos/socios.dat");
    construirIndice("archivos/socios.dat");
    FILE* pfind=fopen("archivos/socios.idx","rb");
    fread(reg,sizeof(unsigned)+sizeof(long),1,pfind);
    while(!feof(pfind))
    {
        printf("%ld %u",*(long*)reg);
        fread(reg,sizeof(unsigned)+sizeof(long),1,pfind);
    }
    free(reg);
    return 0;
}
