#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "abb.h"
#include "pila.h"

/* Definición del struct nodo.
 */

typedef struct nodo_abb{
	struct nodo_abb* h_izq;
	struct nodo_abb* h_der;
	char* clave;
	void* dato;
}nodo_abb_t;

/* Definición del struct lista.
 */
 
struct abb{
	nodo_abb_t* raiz;
	size_t cant;
	abb_comparar_clave_t funcion_comparacion;
	abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
	const abb_t* arbol;
	pila_t* pila_nodos;
};


/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/
 
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(abb == NULL){return NULL;}
	abb->raiz = NULL;
	abb->cant = 0;
	abb->funcion_comparacion = cmp;
	abb->destruir_dato = destruir_dato;
	return abb;
}

//Dada una clave y dato crea un nodo_abb.
//Si no se pudo crear devuelve NULL.
nodo_abb_t* crear_nodo(const char *clave, void *dato){
	nodo_abb_t* nodo_abb = malloc(sizeof(nodo_abb_t));
	
	if(nodo_abb == NULL){return NULL;}
	
	nodo_abb->clave = calloc(strlen(clave) + 1, sizeof(char));

	if(!nodo_abb->clave){
		free(nodo_abb);
		return NULL;
	}
	
	strcpy(nodo_abb->clave,clave);
	
	nodo_abb->h_izq = NULL;
	nodo_abb->h_der = NULL;
	nodo_abb->dato = dato;
	return nodo_abb;
}

// Busca un nodo según la clave y devuelve un puntero al mismo.
// Si no lo encuentra (el nodo no está) devuelve NULL.
nodo_abb_t* buscar_nodo(nodo_abb_t* nodo, abb_comparar_clave_t cmp, const char *clave){
	if (!nodo)
		return NULL;
		
	int resultado = cmp(nodo->clave, clave);
	
	if(resultado == 0) // clave == nodo->clave
		return nodo;
	
	if (resultado > 0)
		return buscar_nodo(nodo->h_izq, cmp, clave); // clave < nodo->clave => va a estar a la izquierda
		
	return buscar_nodo(nodo->h_der, cmp, clave); // clave > nodo->clave => va a estar a la derecha
}

nodo_abb_t* buscar_nodo_padre(nodo_abb_t* nodo, abb_comparar_clave_t cmp, const char *clave, nodo_abb_t** padre){
	if (!nodo)
		return *padre;
		
	*padre = nodo;
	
	int resultado = cmp(nodo->clave, clave);
		
	if (resultado > 0)
		return buscar_nodo_padre(nodo->h_izq, cmp, clave, padre); // clave < nodo->clave
		
	return buscar_nodo_padre(nodo->h_der, cmp, clave, padre); // clave > nodo->clave
}

/*bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_abb_t* nodo = crear_nodo(clave, dato);
	if(nodo == NULL){return NULL;}
	nodo_abb_t* actual = arbol->raiz;
	nodo_abb_t* actual_padre = NULL;
	
	while(actual != NULL){
		int comparacion = arbol->funcion_comparacion(actual->clave, nodo->clave);
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
	}else if(arbol->funcion_comparacion(actual_padre->clave, nodo->clave) > 0){ //padre < nodo.
		actual_padre->h_izq = nodo;
	}else{ //padre > nodo.
		actual_padre->h_der = nodo; 
	}
	arbol->cant++;
	return true;
	
}*/

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_abb_t* nodo_ya_existe = buscar_nodo(arbol->raiz, arbol->funcion_comparacion, clave);
	
	if (nodo_ya_existe){
		if(arbol->destruir_dato){
			arbol->destruir_dato(nodo_ya_existe->dato);
		}
		nodo_ya_existe->dato = dato; // ya estaba entonces piso dato
		return true;
	}
	
	// no está entonces hay que crear un nodo para guardar
	nodo_abb_t* nodo_abb = crear_nodo(clave, dato);
	
	if(nodo_abb == NULL){return false;}
	arbol->cant++;
	
	if (!arbol->raiz){
		arbol->raiz = nodo_abb;
		return true;		
	}
		
	nodo_abb_t* nodo_aux;	
	nodo_abb_t* nodo_padre = buscar_nodo_padre(arbol->raiz, arbol->funcion_comparacion, clave, &nodo_aux);

	// ya se el padre ahora falta saber si soy su hijo derecho o izquierdo
	int resultado = arbol->funcion_comparacion(nodo_padre->clave, clave);
		
	if (resultado > 0){
		nodo_padre->h_izq = nodo_abb;   // clave < nodo_padre->clave => soy su hijo izquierdo											
	}else{
		nodo_padre->h_der = nodo_abb;	// clave > nodo_padre->clave => soy su hijo derecho	
	}									
	
	return true;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_abb_t* nodo_a_buscar = buscar_nodo(arbol->raiz, arbol->funcion_comparacion, clave);
		
	if (!nodo_a_buscar)
		return false;
	
	return true;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t* nodo_a_buscar = buscar_nodo(arbol->raiz, arbol->funcion_comparacion, clave);
		
	if (!nodo_a_buscar)
		return NULL;
	
	return nodo_a_buscar->dato;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cant;	
}


//Destruye los nodos. junto con sus claves y datos, en postorder.
void abb_destruir_nodos(abb_t *arbol, nodo_abb_t *nodo){
	if(!nodo){
		return;
	}
	abb_destruir_nodos(arbol, nodo->h_izq);
	abb_destruir_nodos(arbol, nodo->h_der);
	free(nodo->clave);
	if(arbol->destruir_dato){
		arbol->destruir_dato(nodo->dato);
	}
	free(nodo);
}


void abb_destruir(abb_t *arbol){
	abb_destruir_nodos(arbol, arbol->raiz);
	free(arbol);
}



//Posiciona al iterador en el primer nodo inorder del arbol.
void abb_iter_in_al_principio(abb_iter_t *iter){
	nodo_abb_t* nodo_actual = iter->arbol->raiz;
	while(nodo_actual){
		pila_apilar(iter->pila_nodos, nodo_actual);
		nodo_actual = nodo_actual->h_izq;
	}
}


abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* abb_iter = malloc(sizeof(abb_iter_t));
	if(!abb_iter){return NULL;}
	pila_t* pila = pila_crear();
	if(!pila){
		free(abb_iter);
		return NULL;
	}
	abb_iter->arbol = arbol;
	abb_iter->pila_nodos = pila;
	abb_iter_in_al_principio(abb_iter);
	return abb_iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)){
		return false;
	}
	nodo_abb_t* nodo = pila_desapilar(iter->pila_nodos);
	if(nodo->h_der){
		pila_apilar(iter->pila_nodos, nodo->h_der);
	}
	nodo = nodo->h_izq;
	while(nodo){
		pila_apilar(iter->pila_nodos, nodo);
		nodo = nodo->h_izq;
	}
	return true;
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila_nodos);
}





