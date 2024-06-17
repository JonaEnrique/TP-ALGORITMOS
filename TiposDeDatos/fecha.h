#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef struct fecha
{
    int dia;
    int mes;
    int anio;
}tFecha;

int esFechaValida(tFecha);

#endif // FECHA_H_INCLUDED
