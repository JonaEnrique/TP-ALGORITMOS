#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef struct fecha
{
    int dia;
    int mes;
    int anio;
}tFecha;

int esFechaValida(tFecha);
int diferenciaDias(tFecha fecha1,tFecha fecha2);
int esBisiesto(int anio);

#endif // FECHA_H_INCLUDED
