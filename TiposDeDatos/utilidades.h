#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#define ERR             0
#define TODO_OK         1
#define DUPLICADO       2
#define SIN_MEM         3
#define NO_ENCONTRADO   4
#define SIN_INICIALIZAR 5
#define ERR_ARCH        6
#define ERR_ELIM        6

#define MIN(X,Y) ((X) < (Y) ? (X):(Y))

typedef int (*Cmp)(const void *dato1, const void *dato2);
typedef void (*Accion)(void *,unsigned, unsigned, void*);
typedef unsigned (*Leer)(void **, void *, unsigned, void *params);

#endif // UTILIDADES_H_INCLUDED
