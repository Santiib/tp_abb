#ifndef ABB_H
#define ABB_H
#include <stdbool.h>
#include <stdlib.h>

//Estructuras:

struct abb;
typedef struct abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *); 

//Primitivas:


//
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);


//
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);


//
bool abb_pertenece(const abb_t *arbol, const char *clave);


#endif // ABB_H
