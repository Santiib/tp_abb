#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//ESTRUCTURAS:

struct abb;
typedef struct abb abb_t;
struct abb_iter;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *); // si el resultado es < 0 entonces es mayor el segundo char*
typedef void (*abb_destruir_dato_t) (void *); 


/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

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

void *abb_borrar(abb_t *arbol, const char *clave);

void abb_destruir(abb_t *arbol);


/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t* iter);





void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


#endif // ABB_H
