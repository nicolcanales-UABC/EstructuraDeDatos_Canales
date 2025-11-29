#ifndef NODOARBOL_H
#define NODOARBOL_H
#include <stdlib.h>

typedef struct nodoA
{
	struct nodoA *izq;
	struct nodoA *dch;
	void *dato;
}NodoA;

NodoA* crearNodoA(void *dato);

#endif