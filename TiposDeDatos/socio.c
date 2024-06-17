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
    if( estado == 'A' || estado == 'I')
        return 1; //estado valido
    return 0; //estado invalido
}

//funcion comparacion
