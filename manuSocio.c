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
        case 'P': socio_Top10(path_Socios);break;
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
                nroReg = socio_GrabarNuevo(path_Socios, &nueSocio); //obengo el numero de registro correspondiente
                if(TODO_OK == indInsertar(indSocio, &nueSocio.dni, nroReg)) //cargo el nroReg y DNI al indice
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

void socio_Baja(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso){
    tSocio socio;
    unsigned nroReg;

    printf("Ingrese DNI del socio\n"); //pido el DNI
    scanf("%ld", &socio.dni);

    if(TODO_OK == esDniValido(socio.dni)){
        if(TODO_OK == indEliminar(indSocio, &socio.dni, &nroReg)){ //busco el DNI y elimina al socio, recupero el nroReg
            FILE *pf=fopen(path_Socios, "r+b");
            fseek(pf, nroReg*sizeof(tSocio), SEEK_SET); //muevo el puntero hacia el registro que quiero leer
            fread(&socio, sizeof(tSocio), 1, pf);
            if(socio.estado == 'B')
                puts("El socio ya esta dado de baja\n");
            else{
                socio.estado = 'B';
                socio.fechaDeBaja.dia = fecha_proceso->dia;
                socio.fechaDeBaja.mes = fecha_proceso->mes;
                socio.fechaDeBaja.anio = fecha_proceso->anio;
                fseek(pf, nroReg*sizeof(tSocio), SEEK_SET);
                fwrite(&socio, sizeof(tSocio), 1, pf);
                fclose(pf);
                puts("Se dio de baja el socio correctamente\n");
            }
        }
        else
            puts("El dni no es de un socio activo\n");
    }
    else
        puts("El DNI no es valido\n");
}

void socio_Lista_Ordenada(const char *path_Socios, tIndice *indSocio)
{
    tSocio socio;
    unsigned nroReg;

    //indRecorrer y mostrar
}

void socio_Modificar(const char *path_Socios, tIndice *indSocio){
    tSocio socio;
    unsigned nroReg;

    printf("Ingrese DNI del socio\n"); //pido el DNI
    scanf("%ld", &socio.dni);

    if(TODO_OK == esDniValido(socio.dni)){
        if(TODO_OK == indBuscar(indSocio, &socio.dni, &nroReg)){ // compruebo que halla encontrado el DNI
            socio_Modificacion(&socio); //ingresa todos los datos del socio
            if(TODO_OK == socio_Validacion(&socio)){ //valida los datos ingresados
                FILE *pf=fopen(path_Socios, "r+b");
                fseek(pf, nroReg*sizeof(tSocio), SEEK_SET);
                fwrite(&socio, sizeof(tSocio), 1, pf); //re-escribo el socio para modificarlo
                fclose(pf);
                puts("Se modifico el socio correctamente\n");
            }
            else
                puts("Campos invalidos del socio\n");
        }
        else
            puts("El dni no es de un socio activo\n");
    }
    else
        puts("El DNI no es valido\n");
}

void socio_Top10(const char *path_Socios)
{
    tSocio regSocio;
    tSocio *vectorSocios = NULL; //Declaro el vector de socios sin tamaño
    int top = 10;
    int i;
    int contadorSociosEnVector;
    FILE *pf;
    pf = fopen(path_Socios,"rb");
    if(!pf)
    {
        printf("ERROR DE ARCHIVO");
        return;
    }

    // Guardamos todos los socios activos en un vector
    fread(&regSocio,sizeof(tSocio),1,pf);
    while(!feof(pf))
    {
        //Validamos que este activo
        if(regSocio.estado == 'A')
        {
// A medida que vamos leyendo, incrementamos el contador, agrandamos el vector e incertamos el socio en el nuevo espacio
            contadorSociosEnVector++;
            vectorSocios = realloc(vectorSocios,sizeof(tSocio)*(contadorSociosEnVector));
            vectorSocios[contadorSociosEnVector-1] = regSocio;
        }
        fread(&regSocio,sizeof(tSocio),1,pf);
    }
    // Ordenamos el vector por ultima fecha de cuota paga
    qsort(vectorSocios,contadorSociosEnVector,sizeof(tSocio),compararPorFechaCuotaPaga);
    // Mostramos el TOP
    for( i = 0; i < top; i++)
    {
        printf("DNI - APELLIDOS - NOMBRES - FECHA NAC - SEXO - FECHA AF - CATEGORIA - FECHA ULTCUOTA - ESTADO\n");
        printf("%ld %s %s %d/%d/%d %c %d/%d/%d %s %d/%d/%d %c\n",
            vectorSocios[i].dni,
            vectorSocios[i].apellidos,
            vectorSocios[i].nombres,
            vectorSocios[i].fechaNacimiento.dia,
            vectorSocios[i].fechaNacimiento.mes,
            vectorSocios[i].fechaNacimiento.anio,
            vectorSocios[i].sexo,
            vectorSocios[i].fechaAfiliacion.dia,
            vectorSocios[i].fechaAfiliacion.mes,
            vectorSocios[i].fechaAfiliacion.anio,
            vectorSocios[i].categoria,
            vectorSocios[i].fechaUltCuotaPaga.dia,
            vectorSocios[i].fechaUltCuotaPaga.mes,
            vectorSocios[i].fechaUltCuotaPaga.anio,
            vectorSocios[i].estado);
    }

    free(vectorSocios);
    fclose(pf);
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

    //se completa el estado, la fecha de baja, y fecha de pago
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
       esFechaValida(nueSocio->fechaNacimiento) &&
       esFechaValida(nueSocio->fechaUltCuotaPaga))
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

void socio_Modificacion(tSocio *socio){
    fflush(stdin);
    printf("Ingrese los datos del socio: \nNombres:");
    fgets(socio->nombres, 59, stdin);
    fflush(stdin);
    printf("Ingrese los datos del socio: \nApellidos:");
    fgets(socio->apellidos, 59, stdin);
    fflush(stdin);
    printf("Fecha de nacimiento: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &socio->fechaNacimiento.dia, &socio->fechaNacimiento.mes, &socio->fechaNacimiento.anio);
    fflush(stdin);
    printf("Sexo:\n");
    scanf("%c", &socio->sexo);
    fflush(stdin);
    printf("Categoria: MENOR, CADETE, ADULTO, VITALICIO, HONORARIO, JUBILADO\n");
    scanf("%s", socio->categoria);
    fflush(stdin);
    puts("Fecha de ultima cuota paga: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &socio->fechaUltCuotaPaga.dia, &socio->fechaUltCuotaPaga.mes, &socio->fechaUltCuotaPaga.anio);
}
