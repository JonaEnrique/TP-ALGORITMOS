#include "indice.h"

void escribirIndiceEnArchivo(void *pf,unsigned tam,unsigned n, void *pd);

void indCrear (tIndice* ind, size_t tamClave, Cmp funcionComparacion)
{
    crearArbol(&(ind->arbol));
    ind->tamClave=tamClave;
    ind->regInd=malloc(ind->tamClave+sizeof(unsigned));
    if(ind->regInd==NULL)
    {
        printf("SIN MEMORIA PARA CREAR EL REGIND\n");
        return;
    }
    ind->funcionComparacion=funcionComparacion;

}

int indInsertar (tIndice* ind, void *clave, unsigned nroReg)
{
    //se copia la clave en el regInd del indice
    memcpy(ind->regInd,clave,ind->tamClave);
    //se copia el nro de registro a continuacion de la clave en el regInd del indice
    memcpy(ind->regInd+ind->tamClave,&nroReg,sizeof(unsigned));
    return insertarArbol(&(ind->arbol),ind->regInd,ind->tamClave+sizeof(unsigned),ind->funcionComparacion);
}

int indEliminar (tIndice* ind, void *clave, unsigned *nroReg)
{
    //se copia la clave en el regInd del indice
    memcpy(ind->regInd,clave,ind->tamClave);
    //busca con la clave en el regInd y elimina, a su vez carga el nroReg en el regInd a continuacion de la clave
    if(eliminarElemArbol(&(ind->arbol),ind->regInd,ind->tamClave+sizeof(unsigned),ind->funcionComparacion) != TODO_OK )
        return ERR_ELIM;
    //copia en el puntero recibido por parametro el nroReg devuelto por eliminarElemArbol
    memcpy(nroReg,ind->regInd+ind->tamClave,sizeof(unsigned));
    return TODO_OK;
}

int indBuscar (const tIndice* ind, void *clave, unsigned *nroReg)
{
   //se copia la clave en el regInd del indice
    memcpy(ind->regInd,clave,ind->tamClave);
    if( buscarElemArbol(&(ind->arbol),ind->regInd,ind->tamClave,ind->funcionComparacion) != TODO_OK )
        return NO_ENCONTRADO;
    memcpy(nroReg,ind->regInd+ind->tamClave,sizeof(unsigned));
    return TODO_OK;
}

int indCargar (tIndice* ind, const char* path)
{
    return cargarArchivoBinOrdenadoArbol(&(ind->arbol),path,ind->tamClave+sizeof(unsigned));
}

int indGrabar (const tIndice* ind, const char* path)
{
    FILE *pf;
    pf = fopen(path,"wb");

    if(!pf)
        return ERR_ARCH;
    //recorrerEnOrdenArbol(&(ind->arbol),ind->tamClave+sizeof(unsigned),&pf,escribirIndiceEnArchivo);
    recorrerEnOrdenArbol(&(ind->arbol), &pf /* FILE**  */, escribirIndiceEnArchivo);


    fclose(pf);
    return TODO_OK;
}

void indVaciar (tIndice* ind)
{
    vaciarArbol(&(ind->arbol));
    free(ind->regInd);
    ind->funcionComparacion=NULL;
}

int indRecorrer (const tIndice* ind,Accion accion, void *param)
{
    recorrerEnOrdenArbol(&(ind->arbol),param,accion);
    return TODO_OK;
}

void escribirIndiceEnArchivo(void *pd,unsigned tam,unsigned n, void *ppf)
{
    /*
    FILE **ppf = (FILE **)pf;
    fwrite(pd,tam,1,*ppf);
    */

    FILE **ppFile = (FILE **)ppf;

    fwrite(pd, tam, 1, *ppFile);
}
