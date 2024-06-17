#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#define TODO_OK 1
#define SIN_MEM 2
#define ERR_ELIM 3
#define NO_ENCONTRADO 4
#define ERR_ARCH 5

typedef int (*Cmp)(const void *dato1, const void *dato2);
typedef void (*Accion)(void *,unsigned, void*);

#endif // UTILIDADES_H_INCLUDED
