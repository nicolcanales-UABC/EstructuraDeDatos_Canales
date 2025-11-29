#ifndef PILA_H
#define PILA_H

#include "../Nodo/nodo.h"
#include <stdio.h>

typedef struct
{
	Nodo *cima;
	int capacidad;
	int cantidad;
	void (*imprimir)(void*); //SE ASIGNA LA FUNCION PARA IMPRIMIR LOS DATOS
	void (*liberar)(void*); //SE ASIGNA LA FUNCION PARA LIBERAR DATOS,SI SE NECESITA
}Pila;


int llena(Pila pila);
int vacia(Pila pila);
void* peek(Pila *pila);
void push(Pila *pila,void *dato);
void* pop(Pila *pila);
void imprimirPila(Pila pila);
void imprimirPilaInvertida(Pila pila);
void eliminarPila(Pila *pila);
void inicializarPila(Pila *pila);
void push_nodo(Pila *pila, Nodo *nuevo);
void* peek_nodo(Pila pila);
int prioridad(char operador);

Nodo* pop_nodo(Pila *pila);

#endif