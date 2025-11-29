#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> //ELIPSIS
//#include "nodo.h"
#include "../Arbol/arbol.h"
#include "../../Practica_10/Libro.h"
//#include "cola.h"

typedef struct
{
	void **tabla;
	int tam;
	int cant;
	int (*folding)(void*);
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
}HashTable;

int hash(int clave,int tam);
int eliminarLibroPorISBN(HashTable *hashtable, const char *isbn, void (*liberar)(void*));
int rehash(int indice,int k,int tam);
float factorCarga(HashTable *hashtable);
HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*),int (*folding)(void*));
int insertarClave(HashTable *hashtable,void *dato);
int validarHashTable(HashTable *hashtable);
//MODIFICAR A ARBOL
//Cola buscarClave(HashTable *hashtable,void *dato);

Arbol buscarClave(HashTable *hashtable,void *dato,void (*imprimir)(void*),int (*comparar)(void*,void*));
Arbol buscarRangoTitulo(HashTable *hashtable, char min, char max,void (*imprimir)(void*),int (*comparar)(void*,void*));
Arbol buscarRangoAutor(HashTable *hashtable, char min, char max,void (*imprimir)(void*),int (*comparar)(void*,void*));
Arbol buscarRangoFecha(HashTable *hashtable, int min, int max,void (*imprimir)(void*),int (*comparar)(void*,void*));
Arbol buscarLAUTOR(HashTable* hashtable,void *dato,void (*imprimir)(void*),int (*comparar)(void*,void*));
int eliminarLibro(HashTable *hashtable, void *dato, void (*liberar)(void*));
void remapHashTable(HashTable *hashtable, int new_tam);
int insertarSinResize(HashTable* hashtable, void *dato);
void imprimirHashTabla(HashTable *hashtable);
int folding(char *cadena);
int foldingISBN(void *dato);
int foldingTITULO(void *dato);
int foldingAUTOR(void *dato);
int foldingDATE(void *dato);
int compararISBN(void *a, void *b);
int compararISBN_LC(void *a, void *b);
int compararTITULO(void *a, void *b);
int compararTITULO_LC(void *a, void *b);
int compararAUTOR(void *a, void *b);
int compararAUTOR_LC(void *a, void *b);
int compararDATE(void *a, void *b);
int compararDATE_LC(void *a, void *b);
int compararEntero(void*a,void*b);
char minuscula(char c);

#endif