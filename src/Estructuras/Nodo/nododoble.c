#include "nododoble.h"


NodoD* crearNodo(void *dato)
{
	NodoD *nuevo = (NodoD*) calloc(1,sizeof(NodoD));
	nuevo->dato = dato;
	return nuevo;
}