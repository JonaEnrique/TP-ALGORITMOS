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

int cargarIndiceDesdeArchivoMaestro(const char* pathArch,tIndice* ind)
{
    tSocio actSocio;
    unsigned nroReg = 0;
    FILE* pf = fopen(pathArch,"rb");
    if(!pf)
        return ERR_ARCH;

    fread(&actSocio,sizeof(tSocio),1,pf);
    while(!feof(pf))
    {
        indInsertar(ind,&actSocio.dni,nroReg++);
        fread(&actSocio,sizeof(tSocio),1,pf);
    }

    fclose(pf);
    return TODO_OK;
}
