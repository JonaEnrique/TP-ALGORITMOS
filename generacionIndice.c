#include "generacionIndice.h"

int txtABin(const char* pathTxt,const char* pathBin)
{
    tSocio actSocio;
    char registro[256]; //Asumiendo un límite de 256 caracteres por línea
    FILE *pTxt,*pBin;
    pTxt=fopen(pathTxt,"rt");
    pBin=fopen(pathBin,"wb");

    if(!pBin || !pTxt)
    {
        fclose(pTxt);
        fclose(pBin);
        return ERR_ARCH;
    }

    while(fgets(registro,sizeof(registro),pTxt))
    {
        trozarCamposLongVariable(&actSocio,registro);
        fwrite(&actSocio,sizeof(tSocio),1,pBin);
    }

    fclose(pTxt);
    fclose(pBin);
    return TODO_OK;
}

void trozarCamposLongVariable(tSocio* actSocio,char* registro)
{
    char* aux = strchr(registro,'\n');
    *aux = '\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%d/%d/%d",&actSocio->fechaDeBaja.dia,&actSocio->fechaDeBaja.mes,&actSocio->fechaDeBaja.anio);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%c",&actSocio->estado);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%d/%d/%d",&actSocio->fechaUltCuotaPaga.dia,&actSocio->fechaUltCuotaPaga.mes,&actSocio->fechaUltCuotaPaga.anio);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%s",actSocio->categoria);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%d/%d/%d",&actSocio->fechaAfiliacion.dia,&actSocio->fechaAfiliacion.mes,&actSocio->fechaAfiliacion.anio);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%c",&actSocio->sexo);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%d/%d/%d",&actSocio->fechaNacimiento.dia,&actSocio->fechaNacimiento.mes,&actSocio->fechaNacimiento.anio);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%s",actSocio->nombres);
    *aux='\0';

    aux = strrchr(registro,',');
    sscanf(aux+1,"%s",actSocio->apellidos);
    *aux='\0';

    sscanf(registro,"%ld",&actSocio->dni);
}

int construirIndice(const char* pathBin)
{
    unsigned n=0;
    FILE *pIdx,*pBin;
    tSocio regSocio;
    void* regInd;
    regInd = malloc(sizeof(long)+sizeof(unsigned));
    if(!regInd)
        return SIN_MEM;

    //crea archivo de indices a partir del archivo de datos de socios
    pBin = fopen(pathBin,"rb");
    pIdx = fopen("archivos/socios.idx","wb");
    if(!pIdx || !pBin)
    {
        fclose(pBin);
        fclose(pIdx);
        return ERR_ARCH;
    }

    while(fread(&regSocio,sizeof(tSocio),1,pBin))
    {
        memcpy(regInd,&regSocio.dni,sizeof(long));
        memcpy(regInd+sizeof(long),&n,sizeof(unsigned));
        n++;
        fwrite(regInd,sizeof(long)+sizeof(unsigned),1,pIdx);
    }
    //Ordenar usando Qsort
    //qsort(pIdx,n,sizeof(long)+sizeof(unsigned),compararUnsigned);
    free(regInd);
    return TODO_OK;
}

int compararUnsigned(const void* a,const void* b)
{
    unsigned *c,*d;
    c=(unsigned*)a+sizeof(long);
    d=(unsigned*)b+sizeof(long);
    return *c-*d;
}
