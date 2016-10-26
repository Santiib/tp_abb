#include "abb.h"
#include "testing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int comparar(const char *clave1, const char *clave2){
	return strcmp(clave1, clave2);
}

void pruebas_abb_alumno(){
	abb_t* abb = abb_crear(comparar, NULL);
	print_test("arbol fue creado",true);
	
	int n1 = 10;
	int n2 = 20;
	int n3 = 30;	
	int n4 = 40;
		
	char *clave1 = "d";  // d > a , d < z
    char *clave2 = "a";
    char *clave3 = "z";
    char *clave4 = "d";
    
    print_test("clave1 no pertenece(arbol vacio)", !abb_pertenece(abb, clave1));
	
	print_test("guardar (clave1,n1)", abb_guardar(abb, clave1, &n1));
	
	print_test("c1 pertenece", abb_pertenece(abb, clave1));
	print_test("c2 no pertenece", !abb_pertenece(abb, clave2));
	print_test("c3 no pertenece", !abb_pertenece(abb, clave3));
	
	print_test("guardar (c2,n2)", abb_guardar(abb, clave2, &n2));
	
	print_test("c1 pertenece", abb_pertenece(abb, clave1));
	print_test("c2 pertenece", abb_pertenece(abb, clave2));
	print_test("c3 no pertenece", !abb_pertenece(abb, clave3));
	
	print_test("guardar (c3,n3)", abb_guardar(abb, clave3, &n3));
	
	print_test("c1 pertenece", abb_pertenece(abb, clave1));
	print_test("c2 pertenece", abb_pertenece(abb, clave2));
	print_test("c3 pertenece", abb_pertenece(abb, clave3));
	
	
	print_test("guardar pisando (c4,n4)", abb_guardar(abb, clave4, &n4));
	
	int* a = abb_obtener(abb, clave3);
	print_test("obtener clave3", *a == 30);
	
	
	int* b = abb_obtener(abb, "hola");
	print_test("obtener clave inexistente", !b);
	
	print_test("cantidad nodos = 3", abb_cantidad(abb) == 3);
	
	
	//PRUEBAS ITERADOR
	abb_iter_t *iter = abb_iter_in_crear(abb);
	if(iter){
		print_test("iter fue creado",true);
	}
	print_test("iter no esta al final", !abb_iter_in_al_final(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter esta al final", abb_iter_in_al_final(iter));
	print_test("iter avanzar es false", !abb_iter_in_avanzar(iter));
	
	
	
	
	abb_destruir(abb);
	print_test("arbol fue destruido",true);
}
