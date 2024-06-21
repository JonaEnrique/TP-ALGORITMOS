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
        case 'A': socio_Alta(path_Socios, ind_Socio, fecha_proceso);break;
        case 'B': socio_Baja(path_Socios, ind_Socio, fecha_proceso);break;
        case 'L': socio_Lista_Ordenada(path_Socios, ind_Socio);break;
        case 'M': socio_Modificar(path_Socios, ind_Socio);break;
        case 'P': socio_Top10(path_Socios, ind_Socio, fecha_proceso);break;
        }
    }while(opc!='S');
}
void socio_Alta(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso){
    tSocio nueSocio;
    unsigned nroReg;

    printf("Ingrese DNI del socio\n"); //pido el DNI
    scanf("%ld", &nueSocio.dni);

    if(TODO_OK == esDniValido(nueSocio.dni)){
        if(TODO_OK != indBuscar(indSocio, &nueSocio.dni, &nroReg)){ //Se busca el DNI en el indice
            socio_Nuevo(&nueSocio, fecha_proceso); //nuevo socio por teclado
            if(TODO_OK == socio_Validacion(&nueSocio)){
                nroReg = socio_GrabarNuevo(path_Socios, &nueSocio);
                if(TODO_OK == indInsertar(indSocio, &nueSocio.dni, nroReg))
                    puts("Se agrego correctamente al nuevo socio\n");
                else
                    puts("Error al grabar en el indice");
            }
            else
                puts("Datos invalidos del socio\n");
        }
        else
            printf("El socio con DNI:%ld ya esta registrado", nueSocio.dni);
    }
    else
        puts("El dni no es valido\n");
}
void socio_Baja(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso)
{
    return;
}
void socio_Lista_Ordenada(const char *path_Socios, tIndice *indSocio)
{
    return;
}
void socio_Modificar(const char *path_Socios, tIndice *indSocio)
{
    return;
}
void socio_Top10(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso)
{
    return;
}
void socio_Nuevo(tSocio *nueSocio, const tFecha *fecha_proceso){
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
    scanf("%c", &nueSocio->sexo);
    fflush(stdin);
    printf("Categoria: MENOR, CADETE, ADULTO, VITALICIO, HONORARIO, JUBILADO\n");
    scanf("%s", nueSocio->categoria);

    //se completa el estado y la fecha de baja
    nueSocio->estado='A';

    nueSocio->fechaDeBaja.dia=0;
    nueSocio->fechaDeBaja.mes=0;
    nueSocio->fechaDeBaja.anio=0;

    nueSocio->fechaAfiliacion.dia=fecha_proceso->dia;
    nueSocio->fechaAfiliacion.mes=fecha_proceso->mes;
    nueSocio->fechaAfiliacion.anio=fecha_proceso->anio;

    nueSocio->fechaUltCuotaPaga.dia=fecha_proceso->dia;
    nueSocio->fechaUltCuotaPaga.mes=fecha_proceso->mes;
    nueSocio->fechaUltCuotaPaga.anio=fecha_proceso->anio;
}

int  socio_Validacion(tSocio *nueSocio){
    if(esDniValido(nueSocio->dni) &&
       esCategoriaValida(nueSocio->categoria) &&
       esSexoValido(nueSocio->sexo) &&
       esEstadoValido(nueSocio->estado) &&
       esFechaValida(nueSocio->fechaNacimiento))
        return TODO_OK;
    return 0;
}
unsigned socio_GrabarNuevo(const char *path_Socios, tSocio *nueSocio){
    unsigned nroReg;
    FILE *pf=fopen(path_Socios, "r+b");
    fseek(pf, 0L, SEEK_END); // muevo el puntero al final del archivo


    //cuento los bytes que hay en todo el archivo
    nroReg=ftell(pf)/sizeof(tSocio); //obtengo el nuero de registro para el nuevo socio
    fwrite(&nueSocio, sizeof(tSocio), 1, pf);
    fclose(pf);

    return nroReg;
}
