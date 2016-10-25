#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//ESTRUCTURAS:

struct abb;
typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *); // si el resultado es < 0 entonces es mayor el segundo char*
typedef void (*abb_destruir_dato_t) (void *); 

//PRIMITIVAS:


//Crea un abb.
//Recibe por parametro una funcion comparar y destruir_dato.
//Devuelve NULL si no se pudo crear.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);


//Guarda una clave con su dato en el arbol recivido por parametro.
//Devuelve true si se pudo guardar o false en caso contrario.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);


//Devuelve true o false dependiendo si la clave se encuentra o no en el arbol.
bool abb_pertenece(const abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);


#endif // ABB_H
