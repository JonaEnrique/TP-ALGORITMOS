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

int esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}


int diferenciaDias(tFecha fecha1,tFecha fecha2)
{
    int m, juliano1, juliano2;
    // Convertir la fecha 1 y la fecha 2 en días julianos
    juliano1 = fecha1.anio * 365 + (fecha1.anio / 4) - (fecha1.anio / 100) + (fecha1.anio / 400);
    for ( m = 1; m < fecha1.mes; m++) {
        switch (m) {
            case 4:
            case 6:
            case 9:
            case 11:
                juliano1 += 30;
                break;
            case 2:
                if (esBisiesto(fecha1.anio)) {
                    juliano1 += 29;
                } else {
                    juliano1 += 28;
                }
                break;
            default:
                juliano1 += 31;
                break;
        }
    }
    juliano1 += fecha1.dia;

    juliano2 = (fecha2.anio) * 365 + ((fecha2.anio) / 4) - ((fecha2.anio) / 100) + ((fecha2.anio) / 400);
    for ( m = 1; m < fecha2.mes; m++) {
        switch (m) {
            case 3:
            case 5:
            case 8:
            case 10:
                juliano2 += 30;
                break;
            case 1:
                if (esBisiesto(fecha2.anio)) {
                    juliano2 += 29;
                } else {
                    juliano2 += 28;
                }
                break;
            default:
                juliano2 += 31;
                break;
        }
    }
    juliano2 += fecha2.dia;
    // Devuelvo la diferencia de dias
    return juliano1 - juliano2;
}
