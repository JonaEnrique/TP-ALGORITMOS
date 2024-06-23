    #ifndef MENUSOCIO_H_INCLUDED
#define MENUSOCIO_H_INCLUDED

#include "TiposDeDatos/socio.h"
#include "TiposDeDatos/indice.h"

#define MENU_MENSAJE "Menu de Socios\n\n"                           \
                     "Elija una opcion:\n\n"                        \
                     "A - Alta de un socio\n"                       \
                     "B - Baja de un socio\n"                       \
                     "L - Listados ordenada de socios\n"            \
                     "M - Modificar datos de un socio\n"            \
                     "P - Top 10 socios con mayor tiempo de deuda\n"\
                     "S - Salir\n"                                  \
                     "-->"
#define MENU_OPCIONES "ABLMPS"

void menu_Socios(const char* path_Socio, tIndice *ind_Socio, const tFecha *fecha_proceso);


void socio_Alta(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso);
void socio_Baja(const char *path_Socios, tIndice *indSocio, const tFecha *fecha_proceso);
void socio_Lista_Ordenada(const char *path_Socios, tIndice *indSocio);
void socio_Modificar(const char *path_Socios, tIndice *indSocio);
void socio_Top10(const char *path_Socios);
void socio_Nuevo(tSocio *nueSocio, const tFecha *fecha_proceso);
int  socio_Validacion(tSocio *nueSocio); // valido todos los parametros que se necesite
unsigned socio_GrabarNuevo(const char *path_Socios, tSocio *nueSocio);
void socio_Modificacion(tSocio *socio);

#endif // MENUSOCIO_H_INCLUDED
