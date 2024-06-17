#include "fecha.h"

int esFechaValida(tFecha fecha)
{
    int diasEnMes[] = {31, 28 + (fecha.anio % 4 == 0 && (fecha.anio % 100 != 0 || fecha.anio % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //(supongamos que aceptamos años desde 1900 en adelante)
    if (fecha.anio < 1900) {
        return 0;  // Año inválido
    }
    if (fecha.mes < 1 || fecha.mes > 12) {
        return 0;  // Mes inválido
    }
    if (fecha.dia < 1 || fecha.dia > diasEnMes[fecha.mes - 1]) {
        return 0;  // Día inválido
    }
    return 1;
}
