
#ifndef ARBOL_H
#define ARBOL_H

#include "../Nodo/nodoarbol.h"
#include <stdio.h>
#include "string.h"
#include "../../Practica_10/Libro.h"

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
#define IZQUIERDA 1
#define DERECHA 0

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;


void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);
void imprimirOrden(Arbol arbol,int opcion);
void compararArbol(Arbol arbolA, Arbol arbolB);
void eliminarArbol(Arbol *arbol);
void liberarInt(void *dato);
void equilibrar(Arbol *arbol);
int altura(Arbol arbol);
void insertarBalanceado(Arbol *arbol, void **datos, int ini, int fin);
void extraccionDatos(NodoA *raiz,void **datos,int *indice);

int libroExisteEnArbol(Arbol *arbol, const char *isbn);
NodoA* buscarPorISBN(NodoA* nodo, const char* isbn);

void imprimirOrdenDos(Arbol arbol);
void ordenDos(NodoA *raiz,void (*imprimir)(void*));
int buscarEnArbol2(Arbol *arbol, void *dato,int (*comparar)(void*,void*));



#endif