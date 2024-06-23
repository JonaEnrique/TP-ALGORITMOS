#include "Arbol.h"

void crearArbol(tArbol *pa)
{
    *pa = NULL;
}

int insertarArbol(tArbol *pa, const void *pd, unsigned tam, Cmp funcionComparacion)
{
    tNodoArbol* nuevoNodo;
    void* dato;
    int comp;

    while(*pa)
    {
        if((comp = funcionComparacion(pd, (*pa)->info)) > 0)
        {
            pa = &(*pa)->der;
        }
        else if(comp < 0)
        {
            pa = &(*pa)->izq;
        }
        else
            return DUPLICADO;

    }

    nuevoNodo = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    dato = malloc(tam);

    if(!nuevoNodo || !dato)
    {
        free(nuevoNodo);
        free(dato);

        return SIN_MEM;
    }

    memcpy(dato, pd, tam);

    nuevoNodo->info = dato;
    nuevoNodo->tamInfo = tam;
    nuevoNodo->izq = nuevoNodo->der = NULL;

    *pa = nuevoNodo;

    return TODO_OK;
}

int buscarElemArbol(const tArbol *pa, void *pd, unsigned tam,Cmp funcionComparacion)
{
    int comp;

    while(*pa &&  (comp = funcionComparacion(pd, (*pa)->info)) )
    {
        if((comp = funcionComparacion(pd, (*pa)->info)) > 0)
            pa = &(*pa)->der;
        else

            pa = &(*pa)->izq;
    }

    if(!*pa)
        return NO_ENCONTRADO;

    memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tamInfo));

    return TODO_OK;
}

unsigned leerDesdeArchivoBin(void ** d, void * pf, unsigned pos, void * params)
{
    unsigned tam = *((unsigned*)params);
    *d = malloc(tam);
    if(!*d)
        return 0;
    fseek((FILE*)pf, pos*tam, SEEK_SET);
    return fread(*d, tam, 1, (FILE*)pf);
}


int cargarDesdeDatosOrdenadosRec(tArbol * pa, void * ds, Leer leer, int li, int ls, void * params)
{
    int m = (li+ls)/2,
        r;
    if (li>ls)
        return TODO_OK;

    (*pa) = (tNodoArbol*) malloc(sizeof(tNodoArbol));
    if (!*pa || !((*pa)->tamInfo = leer(&(*pa)->info, ds, m, params)))
    {
        free(*pa);
        return SIN_MEM;
    }

    (*pa)->izq = (*pa)->der = NULL;

    if((r=cargarDesdeDatosOrdenadosRec(&(*pa)->izq, ds, leer, li, m-1, params))!=
            TODO_OK)
        return r;
    return cargarDesdeDatosOrdenadosRec(&(*pa)->der, ds, leer, m+1, ls, params);
}


int cargarArchivoBinOrdenadoArbol(tArbol *pa, const char * path, unsigned tamInfo)
{
    int cantReg,
        r;
    FILE * pf;
    if(*pa)
        return SIN_INICIALIZAR;
    if(!(pf= fopen(path, "rb")))
        return ERR_ARCH;
    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf)/tamInfo;
    r = cargarDesdeDatosOrdenadosRec(pa, pf, leerDesdeArchivoBin, 0, cantReg-1, &tamInfo);
    fclose(pf);
    return r;
}

int cargarDesdeDatosOrdenadosArbol(tArbol * p, void * ds, unsigned cantReg, Leer leer, void * params)
{
    if(*p || !ds)
        return 0;
    return cargarDesdeDatosOrdenadosRec(p, ds, leer, 0, cantReg-1, params);
}


int eliminarElemArbol(tArbol *pa, void *pd, unsigned tam,Cmp funcionComparacion)
{
    if(!(pa = buscarNodoArbol(pa,pd,funcionComparacion)))
        return 0; ///NO_EXISTE

    memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tamInfo));

    return eliminarRaizArbol(pa);
}

tNodoArbol ** buscarNodoArbol(const tArbol* pa, const void * d, Cmp funcionComparacion)
{
    int rc;
    while(*pa && (rc=funcionComparacion(d, (*pa)->info)))
    {
        if(rc<0)
            pa = &(*pa)->izq;
        else
            pa = &(*pa)->der;
    }
    if(!*pa)
        return NULL;

    return (tNodoArbol **)pa;
}

unsigned alturaArbolBin(const tArbol* pa)
{
    int hi, hd;
    if(!*pa)
        return 0;
    hi= alturaArbolBin(&(*pa)->izq);
    hd= alturaArbolBin(&(*pa)->der);
    return (hi>hd ? hi : hd) +1;
}

tNodoArbol ** mayorNodoArbol(const tArbol * pa)
{
    if(!*pa)
        return NULL;

    while((*pa)->der)
        pa = &(*pa)->der;

    return (tNodoArbol **) pa;
}


tNodoArbol ** menorNodoArbol(const tArbol * pa)
{
    if(!*pa)
        return NULL;

    while((*pa)->izq)
        pa = &(*pa)->izq;

    return (tNodoArbol **) pa;
}


int eliminarRaizArbol(tArbol *pa)
{
    tNodoArbol **remp, *elim;

    if(!*pa)
        return 0; ///ARBOL_VACIO
    free((*pa)->info);
    if (!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa = NULL;
        return 1; ///OK
    }

    remp = alturaArbolBin(&(*pa)->izq)>alturaArbolBin(&(*pa)->der)?
    mayorNodoArbol(&(*pa)->izq):
    menorNodoArbol(&(*pa)->der);

    elim = *remp;
    (*pa)->info = elim->info;
    (*pa)->tamInfo = elim->tamInfo;

    *remp = elim->izq ? elim->izq : elim->der;

    free(elim);

    return 1; ///OK
}

void recorrerEnOrdenRecArbol(const tArbol * pa, unsigned n, void *params, Accion accion)
{
    if(!*pa)
        return;
    recorrerEnOrdenRecArbol(&(*pa)->izq, n+1, params, accion);
    accion((*pa)->info, (*pa)->tamInfo, n, params);
    recorrerEnOrdenRecArbol(&(*pa)->der, n+1, params, accion);
}

void recorrerEnOrdenArbol(const tArbol * pa, void * params, Accion accion)
{
    recorrerEnOrdenRecArbol(pa, 0, params, accion);
}

void recorrerEnOrdenInversoRecArbol(const tArbol * p, unsigned n, void* params, Accion accion)
{
    if(!*p)
        return;
    recorrerEnOrdenInversoRecArbol(&(*p)->der, n+1, params, accion);
    accion((*p)->info, (*p)->tamInfo, n, params);
    recorrerEnOrdenInversoRecArbol(&(*p)->izq, n+1, params, accion);
}

void recorrerEnOrdenInversoArbol(const tArbol * p, void * params, Accion accion)
{
    recorrerEnOrdenInversoRecArbol(p, 0, params, accion);
}



void vaciarArbol(tArbol* pa)
{
    if(!*pa)
        return;

    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}


