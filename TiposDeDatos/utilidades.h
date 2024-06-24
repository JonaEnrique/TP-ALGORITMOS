#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#define ERR             0
#define TODO_OK         1
#define DUPLICADO       2
#define SIN_MEM         3
#define NO_ENCONTRADO   4
#define SIN_INICIALIZAR 5
#define ERR_ARCH        6
#define ERR_ELIM        6

#define MIN(X,Y) ((X) < (Y) ? (X):(Y))

typedef int (*Cmp)(const void *dato1, const void *dato2);
typedef void (*Accion)(void *,unsigned, unsigned, void*);
typedef unsigned (*Leer)(void **, void *, unsigned, void *params);

/*
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

*/

#endif // UTILIDADES_H_INCLUDED
