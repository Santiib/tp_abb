 Árbol Binario de Búsqueda
Para el lunes 24 de octubre tienen que implementar un árbol binario de búsqueda, con las siguientes definiciones y primitivas:

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);
bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);

La función destruir_dato se recibe en el constructor, para usarla en abb_destruir y en abb_insertar en el caso de que tenga que reemplazar el dato de una clave ya existente.

Por otro lado deben implementar dos iteradores inorder.
El iterador interno funciona usando la función de callback "visitar" que recibe la clave, el valor y un puntero extra, y devuelve true si se debe seguir iterando, false en caso contrario:

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

Y un iterador externo:

typedef struct abb_iter abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
bool abb_iter_in_avanzar(abb_iter_t *iter);
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);

Además de llevarlo impreso para dárselo a su ayudante, deben mandar la versión digital de los archivos .c, .h, y Makefile (incluyendo las pruebas) en un archivo ZIP a la casilla de mail con el asunto "ABB - Padron1 -  Apellido1 - Padron2 - Apellido2".
