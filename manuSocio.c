#include "menuSocio.h"

void menu_Socios(const char* path_Socios, tIndice *ind_Socio, const tFecha *fecha_proceso){

    char opc;
    do{
        printf("%s", MENU_MENSAJE); //menu de opciones
        scanf("%c", &opc);
        while(strchr(MENU_OPCIONES, opc)==NULL){ //validacion de la opcion del usuario
            puts("Ingrese otra opcion\n");
            scanf("%c", &opc);
        }
        //entra al menu
        switch(opc){
        case 'A': socio_Alta(path_Socios, ind_Socio);break;
        case 'B': socio_Baja(path_Socios, ind_Socio, fecha_proceso);break;
        case 'L': socio_Lista_Ordenada(path_Socios, ind_Socio);break;
        case 'M': socio_Modificar(path_Socios, ind_Socio);break;
        case 'P': socio_Top10(path_Socios, ind_Socio, fecha_proceso);break;
        }
    }while(opc!='S');
}
void socio_Alta(const char *path_Socios, tIndice *indSocio){
    tSocio nueSocio;
}
void socio_Baja(const char *path_Socios, tIndice *indSocio, tFecha *fecha_proceso);
void socio_Lista_Ordenada(const char *path_Socios, tIndice *indSocio);
void socio_Modificar(const char *path_Socios, tIndice *indSocio);
void socio_Top10(const char *path_Socios, tIndice *indSocio, tFecha *fecha_proceso);
void socio_Nuevo(tSocio *nueSocio){
    fflush(stdin);
    printf("Ingrese los datos del socio: \nNombres:");
    fgets(nueSocio->nombres, 59, stdin);
    fflush(stdin);
    printf("Ingrese los datos del socio: \nApellidos:");
    fgets(nueSocio->apellidos, 59, stdin);
    fflush(stdin);
    printf("Fecha de nacimiento: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &nueSocio->fechaNacimiento.dia, &nueSocio->fechaNacimiento.mes, &nueSocio->fechaNacimiento.anio);
    fflush(stdin);
    printf("Sexo:\n");
    scanf("%c", &alumno->sexo);
    fflush(stdin);
    printf("fecha de afiliacion: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &nueSocio->fechaAfiliacion.dia, &nueSocio->fechaAfiliacion.mes, &nueSocio->fechaAfiliacion.anio);
    fflush(stdin);
    printf("Categoria: MENOR, CADETE, ADULTO, VITALICIO, HONORARIO, JUBILADO\n");
    scanf("%s", nueSocio->categoria);
    fflush(stdin);
    printf("Fecha de ultima cuota paga: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &nueSocio->fechaUltCuotaPaga.dia, &nueSocio->fechaUltCuotaPaga.mes, &nueSocio->fechaUltCuotaPaga.anio);
    fflush(stdin);
    //se completa el estado y la fecha de baja
    nueSocio->estado='A';
    nueSocio->fechaDeBaja.dia=0;
    nueSocio->fechaDeBaja.mes=0;
    nueSocio->fechaDeBaja.anio=0;
}
