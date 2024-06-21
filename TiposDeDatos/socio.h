#ifndef SOCIO_H_INCLUDED
#define SOCIO_H_INCLUDED
#include "fecha.h"
#include <stdio.h>

typedef struct Socio
{
    long dni;
    char apellidos[60];
    char nombres[60];
    tFecha fechaNacimiento;
    char sexo;
    tFecha fechaAfiliacion;
    char categoria[10];
    tFecha fechaUltCuotaPaga;
    char estado;
    tFecha fechaDeBaja;
}tSocio;

int esDniValido(long);
int esSexoValido(char);
int esCategoriaValida(char[10]);
int esEstadoValido(char);
void mostrarArchivosSocios(const char* pathArch);
int compararSocios(const void* regSocio1, const void* regSocio2);

#endif // SOCIO_H_INCLUDED
