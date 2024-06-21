#include "socio.h"
#include <string.h>

int esDniValido(long dni)
{
    if( dni > 100000000 || dni < 10000 )
        return 0; //dni invalido
    return 1; //dni valido
}

int esSexoValido(char sexo)
{
    if( sexo == 'F' || sexo == 'M' || sexo == 'O')
        return 1; //sexo valido
    return 0; //sexo invalido
}

int esCategoriaValida(char categoria[10])
{

    if( !(strcmp(categoria,"MENOR") || strcmp(categoria,"CADETE") || strcmp(categoria,"ADULTO") || strcmp(categoria,"VITALICIO")
       || strcmp(categoria,"HONORARIO") || strcmp(categoria,"JUBILADO")))
        return 1; //categoria valida
    return 0; //categoria invalida
}

int esEstadoValido(char estado)
{
    if( estado == 'A' || estado == 'B')
        return 1; //estado valido
    return 0; //estado invalido
}

int compararSocios(const void* regSocio1, const void* regSocio2)
{
    long dni1, dni2;

    memcpy(&dni1, regSocio1, sizeof(long));
    memcpy(&dni2, regSocio2, sizeof(long));

    return dni1 - dni2;
}

int compararPorFechaCuotaPaga(const void* regSocio1, const void* regSocio2)
{
    tSocio socio1, socio2;
    socio1 = *(tSocio*)regSocio1;
    socio2 = *(tSocio*)regSocio2;
    return diferenciaDias(socio1.fechaUltCuotaPaga,socio2.fechaUltCuotaPaga);
}

void mostrarArchivosSocios(const char* pathArch)
{
    tSocio actSocio;
    FILE* pf = fopen("archivos/socios.dat","rb");
    fread(&actSocio,sizeof(tSocio),1,pf);
    while(!feof(pf))
    {
        printf("%ld %s %s %d/%d/%d %c %d/%d/%d %s %d/%d/%d %c\n",
            actSocio.dni,
            actSocio.apellidos,
            actSocio.nombres,
            actSocio.fechaNacimiento.dia,
            actSocio.fechaNacimiento.mes,
            actSocio.fechaNacimiento.anio,
            actSocio.sexo,
            actSocio.fechaAfiliacion.dia,
            actSocio.fechaAfiliacion.mes,
            actSocio.fechaAfiliacion.anio,
            actSocio.categoria,
            actSocio.fechaUltCuotaPaga.dia,
            actSocio.fechaUltCuotaPaga.mes,
            actSocio.fechaUltCuotaPaga.anio,
            actSocio.estado);
        fread(&actSocio,sizeof(tSocio),1,pf);
    }
    return;
}
