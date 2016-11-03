#include "abb.h"
#include "testing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int comparar(const char *clave1, const char *clave2){
	return strcmp(clave1, clave2);
}

void pruebas_basicas(){
	puts("PRUEBAS BÁSICAS");
	abb_t* abb = abb_crear(comparar, NULL);
	print_test("arbol fue creado", abb);
	
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
		print_test("iter fue creado",iter);
	}
	print_test("iter no esta al final", !abb_iter_in_al_final(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter avanzar es true", abb_iter_in_avanzar(iter));
	print_test("iter esta al final", abb_iter_in_al_final(iter));
	print_test("iter avanzar es false", !abb_iter_in_avanzar(iter));
	
	
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

void prueba_abb_borrar(){
	puts("PRUEBAS ABB_BORRAR");
	abb_t* arbol = abb_crear(comparar,NULL);

	char *clave1 = "perro", *valor1 = "guau";
	char *clave2 = "gato", *valor2 = "miau";
	char *clave3 = "vaca", *valor3 = "mu";

	print_test("Prueba abb insertar clave1", abb_guardar(arbol, clave1, valor1));
	print_test("Prueba abb insertar clave2", abb_guardar(arbol, clave2, valor2));
	print_test("Prueba abb insertar clave3", abb_guardar(arbol, clave3, valor3));

	print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);

	print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(arbol, clave3));
	print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(arbol, clave3));
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

	print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(arbol, clave1));
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
	print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(arbol, clave1));
	print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(arbol, clave1));
	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

	print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));
	print_test("Prueba abb borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);
	print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(arbol, clave3));
	print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(arbol, clave2));
	print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(arbol, clave2));
	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
}

void prueba_volumen(size_t largo, bool debug){
	puts("PRUEBAS VOLUMEN");
	abb_t* arbol = abb_crear(comparar, NULL);

	const size_t largo_clave = 2;

	char letras[18] = "abcdefghijklmnopqr";
	char** claves = malloc(sizeof(char*) * largo);

	size_t* datos[largo];
	size_t num;
	/* Inserta 'largo' parejas en el arbol */
	bool ok = true;

	size_t i;
	for(i = 0; i < largo ; i++){
		datos[i] = malloc(sizeof(size_t));
		num = rand () % largo;
		*datos[i] = num;
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand()+9) % 18];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], datos[i]);
		if (!ok) break;
	}

	if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
	
    /* Verifica que devuelva los valores correctos */
    for (i = 0; i < abb_cantidad(arbol); i++) {
        ok = abb_pertenece(arbol, claves[i]);
        if (!ok){
			puts("rompe pertenece");
			puts(claves[i]);
			//break;
		}
        ok = abb_obtener(arbol, claves[i]) == datos[i];
        if (!ok){
			 size_t *datod = abb_obtener(arbol, claves[i]);
			 puts("rompe obtener");
			 printf("%zu\n", *datod);
			 printf("%zu\n", *datos[i]);
			 //break;
		 }
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
       
    /* Borro 50 elementos */
    ok = true;
    for (size_t b = 0; b < 50; b++){
		size_t valor = *(size_t*)abb_obtener(arbol, claves[b]);
		ok = *(size_t*)abb_borrar(arbol, claves[b]) == valor;
		free(datos[b]);
		if (!ok) break;		
	}    
    
    if (debug) print_test("Prueba abb borrar 50 elementos", ok);    
    
    for (size_t a = 0; a < largo; a++){
		free(claves[a]);
	}
	free(claves);
	abb_destruir(arbol);	
}

void prueba_abb_iterar_volumen(size_t largo){
	puts("PRUEBA ITERAR VOLUMEN");
	abb_t* arbol = abb_crear(comparar, NULL);

	const size_t largo_clave = 10;

	char letras[18] = "abcdefghijklmnopqr";
	char** claves = malloc(sizeof(char*) * largo);

	size_t* datos[largo];
	size_t num;
	/* Inserta 'largo' parejas en el arbol */
	bool ok = true;

	size_t i;
	for(i = 0; i < largo ; i++){
		datos[i] = malloc(sizeof(size_t));
		num = rand () % largo;
		*datos[i] = num;
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand()+9) % 18];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], datos[i]);
		if (!ok) break;
	}

	printf("CANTIDAD ELEMENTOS %zu \n", abb_cantidad(arbol));

	// Prueba de iteración sobre las claves almacenadas.
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

	ok = true;
	const char *clave;
	size_t *valor;

	for (i = 0; i < abb_cantidad(arbol); i++) {
		if ( abb_iter_in_al_final(iter) ) {
			ok = false;
			break;
		}
		clave = abb_iter_in_ver_actual(iter);
		if ( clave == NULL ) {
			ok = false;
			break;
		}
		valor = abb_obtener(arbol, clave);
		if ( valor == NULL ) {
			ok = false;
			break;
		}
		*valor = largo;
		abb_iter_in_avanzar(iter);
	}
	
	print_test("Prueba abb iteración en volumen", ok);
	printf("%zu \n", i);
	printf("%zu \n", largo); // Coinciden
	print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == abb_cantidad(arbol));
	if (i != abb_cantidad(arbol)) printf("Largo recorrido: %zu\n", i);
	print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter)); // DEBERIA DAR TRUE
	int r = 0;
	while(!abb_iter_in_al_final(iter)){
		abb_iter_in_avanzar(iter);
		r++;
	}	
	printf("%d \n", r); // Elementos que se recorrieron después de los que tiene el abb
	printf("CANTIDAD ELEMENTOS %zu \n", abb_cantidad(arbol));
	print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

	
	for(i = 0; i < largo ; i++) free(claves[i]);
	for(i = 0; i < largo ; i++) free(datos[i]);
	free(claves);

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
}

bool foo(const char* a, void* b, void* c){
	*(int*)c += *(int*)b;
	printf("Sumatoria: %d \n", *(int*)c);
	if (*(int*)c < 35)
		return true;
	return false;
}
		
void prueba_iterador_internoI(){
	puts("PRUEBAS ITERADOR INTERNO");
	abb_t* abb = abb_crear(comparar, NULL);

	int n1 = 10;
	int n2 = 10;
	int n3 = 10;	
	int n4 = 10;
		
	char *clave1 = "d";
    char *clave2 = "a";
    char *clave3 = "z";
    char *clave4 = "g";
    
    abb_guardar(abb, clave1, &n1);
    abb_guardar(abb, clave2, &n2);
    abb_guardar(abb, clave3, &n3);
    abb_guardar(abb, clave4, &n4);
    	
	int* sumatoria = malloc(sizeof(int) * 100);
	*sumatoria = 0;
	
	abb_in_order(abb, foo, sumatoria);
		
	free(sumatoria);
	abb_destruir(abb);		
}

void prueba_iterador_internoII(size_t largo, bool debug){
	abb_t* arbol = abb_crear(comparar, free);

	const size_t largo_clave = 5;

	char letras[18] = "abcdefghijklmnopqr";
	char** claves = malloc(sizeof(char*) * largo);

	size_t* datos[largo];
	
	/* Inserta 'largo' parejas en el arbol */
	bool ok = true;

	size_t i;
	for(i = 0; i < largo ; i++){
		datos[i] = malloc(sizeof(size_t));
		*datos[i] = 1;
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand()+9) % 18];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], datos[i]);
		if (!ok) break;
	}	
	
	int* sumatoria = malloc(sizeof(int) * 1000);
	*sumatoria = 0;
	
	abb_in_order(arbol, foo, sumatoria);
		
	free(sumatoria);
	for (size_t a = 0; a < largo; a++){
		free(claves[a]);
	}
	free(claves);
	abb_destruir(arbol);	
}

void pruebas_guardar(){
	abb_t *arbol = abb_crear(comparar, free);
	print_test("se creo", arbol);
	
	char *c1 = "hola";
	char *c2 = "hola";
	char *c3 = "hola";
	
	
	
	char *str1 = malloc(2*sizeof(char));
	char *str2 = malloc(2*sizeof(char));
	char *str3 = malloc(2*sizeof(char));
	char *str4 = malloc(2*sizeof(char));
	char *str5 = malloc(2*sizeof(char));
	char *str6 = malloc(2*sizeof(char));
	char *str7 = malloc(2*sizeof(char));
	char *str8 = malloc(2*sizeof(char));
	char *str9 = malloc(2*sizeof(char));
	char *stra = malloc(2*sizeof(char));
	//char *strb = malloc(2*sizeof(char));
	//char *strc = malloc(2*sizeof(char));
	
	char s1[1] = {"1"};
	str1[0] = *s1;
	str1[1] = '\0';
	
	char s2[1] = {"2"};
	str2[0] = *s2;
	str2[1] = '\0';
	
	char s3[1] = {"3"};
	str3[0] = *s3;
	str3[1] = '\0';
	
	char s4[1] = {"4"};
	str4[0] = *s4;
	str4[1] = '\0';
	
	char s5[1] = {"5"};
	str5[0] = *s5;
	str5[1] = '\0';
	
	char s6[1] = {"6"};
	str6[0] = *s6;
	str6[1] = '\0';
	
	char s7[1] = {"7"};
	str7[0] = *s7;
	str7[1] = '\0';
	
	char s8[1] = {"8"};
	str8[0] = *s8;
	str8[1] = '\0';
	
	char s9[1] = {"9"};
	str9[0] = *s9;
	str9[1] = '\0';
	
	char sa[1] = {"a"};
	stra[0] = *sa;
	stra[1] = '\0';
	
	abb_guardar(arbol, c1, str1);
	char *res = abb_obtener(arbol, c1);
	puts(res);
	
	abb_guardar(arbol, c2, str2);
	res = abb_obtener(arbol, c2);
	puts(res);
	
	puts("guarda uno");
	abb_guardar(arbol, c3, str3);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	puts("guarda dos");
	abb_guardar(arbol, c3, str4);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	puts("guarda tres");
	abb_guardar(arbol, c3, str5);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, str6);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, str7);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, str8);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, str9);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, stra);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, stra);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, stra);
	res = abb_obtener(arbol, c3);
	puts(res);
	
	abb_guardar(arbol, c3, stra);
	res = abb_obtener(arbol, c3);
	puts(res);
	

	abb_destruir(arbol);
}

/*
	const size_t largo_clave = 10;

	char letras[18] = "abcdefghijklmnopqr";
	char** claves = malloc(sizeof(char*) * largo);

	size_t* datos[largo];
	size_t num;
	// Inserta 'largo' parejas en el arbol 
	bool ok = true;

	size_t i;
	for(i = 0; i < largo ; i++){
		datos[i] = malloc(sizeof(size_t));
		num = rand () % largo;
		*datos[i] = num;
		char* str = malloc(sizeof(char) * largo_clave);
		size_t j;
		for(j = 0; j < largo_clave - 1; j++){
			str[j] = letras[(rand()+9) % 18];
		}
		str[j] = '\0';
		claves[i] = str;
		ok = abb_guardar(arbol, claves[i], datos[i]);
		if (!ok) break;
	}*/

void pruebas_abb_alumno(){
	pruebas_basicas();
	prueba_abb_borrar();
	//prueba_volumen(1000, true); // tam debe ser > 50
	prueba_abb_iterar_volumen(1000);
	prueba_iterador_internoI();
	prueba_iterador_internoII(50, true);
	//pruebas_guardar();
}

