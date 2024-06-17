#include "fecha.h"

int esFechaValida(tFecha fecha)
{
    int diasEnMes[] = {31, 28 + (fecha.anio % 4 == 0 && (fecha.anio % 100 != 0 || fecha.anio % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //(supongamos que aceptamos a�os desde 1900 en adelante)
    if (fecha.anio < 1900) {
        return 0;  // A�o inv�lido
    }
    if (fecha.mes < 1 || fecha.mes > 12) {
        return 0;  // Mes inv�lido
    }
    if (fecha.dia < 1 || fecha.dia > diasEnMes[fecha.mes - 1]) {
        return 0;  // D�a inv�lido
    }
    return 1;
}
