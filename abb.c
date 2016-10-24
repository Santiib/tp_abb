#include <stdlib.h>
#include <stdbool.h>
#include "abb.h"


typedef struct nodo_abb{
	struct nodo_abb* h_izq;
	struct nodo_abb* h_der;
	char* clave;
	void* dato;
}nodo_abb_t;


struct abb{
	nodo_abb_t* raiz;
	size_t cant;
	abb_comparar_clave_t comparar_clave;
	abb_destruir_dato_t destruir_dato;
};


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(abb == NULL){return NULL;}
	abb->raiz = NULL;
	abb->cant = 0;
	abb->comparar_clave = cmp;
	abb->destruir_dato = destruir_dato;
	return abb;
}


//Dada una clave y dato crea un nodo_abb.
//Si no se pudo crear devuelve NULL.
nodo_abb_t* crear_nodo(const char *clave, void *dato){
	nodo_abb_t* nodo_abb = malloc(sizeof(nodo_abb_t));
	if(nodo_abb == NULL){return NULL};
	nodo_abb->h_izq = NULL;
	nodo_abb->h_der = NULL;
	nodo_abb->clave = clave;
	nodo_abb->dato = dato;
	return nodo_abb;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(clave == NULL){return false;}
	nodo_abb_t* nodo = crear_nodo(clave, dato);
	if(nodo == NULL){return NULL;}
	nodo_abb_t* actual = arbol->raiz;
	nodo_abb_t* actual_padre = NULL;
	
	while(actual != NULL){
		int comparacion = arbol->comparar_clave(actual->clave, nodo->clave);
		actual_padre = actual;
		if(comparacion == 0){ //actual == nodo.
			actual->dato = nodo->dato;
			free(nodo);
			return true;
		}else if(comparacion > 0){ //actual > nodo.
			actual = actual->h_izq;
		}else{ //actual < nodo.
			actual = actual->h_der;
		}
	}
	
	if(actual_padre == NULL){
		arbol->raiz = nodo;
	}else if(arbol->comparar_clave(actual_padre->clave, nodo->clave) > 0){ //padre < nodo.
		actual_padre->h_izq = nodo;
	}else{ //padre > nodo.
		actual_padre->h_der = nodo;
	}
	arbol->cant++;
	return true;
	
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_abb_t* actual = arbol->raiz;
	while(actual != NULL){
		int comparacion = arbol->comparar_clave(actual->clave, clave);
		if(comparacion == 0){
			return true;
		}else if(comparacion > 0){ //actual > clave.
			actual = actual->h_izq;
		}else{ //actual < clave.
			actual = actual->h_der;
		}
	}
	return false;
}






