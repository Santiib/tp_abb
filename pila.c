#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* Rodrigo Aparicio
 * nro de padrón 98967
 * */

#define CANT_A_MODIFICAR 2 //cantidad la cual se multiplicara/dividira la capacidad de la pila en caso de hacer realloc
#define CAPACIDAD 35 //capacidad de una pila al crearse
#define CUAN_MAS_CHICA 4 //numero por el que se dividira la capacidad para decidir si se hara realloc

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad; // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    
    pila->capacidad = CAPACIDAD;  
    pila->datos = malloc(pila->capacidad * sizeof(void*));
    
    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    
     
	pila->cantidad = 0;
	
    return pila;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){
	if (pila->cantidad == pila->capacidad){
		void **datos_nuevo = realloc(pila->datos, sizeof(void*) * pila->capacidad * CANT_A_MODIFICAR);
		if (datos_nuevo == NULL){
			return false;
		}
		pila->datos = datos_nuevo;
		pila->capacidad = pila->capacidad * CANT_A_MODIFICAR;
	}
	 
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	
	return true;	
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){
	if (pila_esta_vacia(pila)){
		return NULL;
	}
	
	return pila->datos[pila->cantidad - 1];
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){
	if (pila_esta_vacia(pila)){
		return NULL;
	}
	
	void* tope = pila_ver_tope(pila);
	
	if (pila->cantidad == (pila->capacidad / CUAN_MAS_CHICA)){
		void **datos_nuevo = realloc(pila->datos, sizeof(void*) * (pila->capacidad / CANT_A_MODIFICAR));
		if (datos_nuevo != NULL){
			pila->datos = datos_nuevo;
			pila->capacidad = pila->capacidad / CANT_A_MODIFICAR;
		}		
	}
	pila->cantidad--;
	
	return tope;
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0);
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);	
}

// ...
