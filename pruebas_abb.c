#include "abb.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int comparar(const char *clave1, const char *clave2){
	return strcmp(clave1, clave2);
}


void pruebas_abb_alumno(){
	
	abb_t* abb = abb_crear(comparar, NULL);
	print_test("arbol fue creado",true);
	
	int n1 = 1, n2 = 2, n3 = 3;
	const char c1[2] = "c1", c2[2] = "c2", c3[2] = "c3";
	
	
	print_test("c1 no pertenece(arbol vacio)", !abb_pertenece(abb, c2));
	
	print_test("guardar (c1,n1)", abb_guardar(abb, c1, &n1));
	
	print_test("c1 pertenece", abb_pertenece(abb, c1));
	print_test("c2 no pertenece", !abb_pertenece(abb, c2));
	print_test("c3 no pertenece", !abb_pertenece(abb, c3));
	
	print_test("guardar (c2,n2)", abb_guardar(abb, c2, &n2));
	
	print_test("c1 pertenece", abb_pertenece(abb, c1));
	print_test("c2 pertenece", abb_pertenece(abb, c2));
	print_test("c3 no pertenece", !abb_pertenece(abb, c3));
	
	print_test("guardar (c3,n3)", abb_guardar(abb, c3, &n3));
	
	print_test("c1 pertenece", abb_pertenece(abb, c1));
	print_test("c2 pertenece", abb_pertenece(abb, c2));
	print_test("c3 pertenece", abb_pertenece(abb, c3));
	
}
