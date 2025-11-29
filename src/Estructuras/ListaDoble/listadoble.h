#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "../Nodo/nododoble.h"
#include "../../Practica_2/alumno.h"
#include "../../Captura/captura.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	int (*comparar)(void *datoA,void *dataB);
	void (*imprimir)(void *datoA);
	void (*liberar)(void *datoA);
}ListaD;

ListaD inicializarListaD(void);
void mostrarListaD(ListaD lista);
void mostrarListaA(ListaD lista);
void insertarEnPosicion(ListaD *lista,void* dato,int pos);
void insertarInicio(ListaD *lista,void* dato);
void borrarAlumno(ListaD *lista, int matricula);
void ordenaTodo3000inador(ListaD *, int);
void insertarOrdenadoInador3000(ListaD *,void* , int );
	
void mostrarApuntadores(ListaD lista);

	//ALUMNO
void insertarAlumno(ListaD *lista, unsigned int matAlum);
void desplegarParametro(ListaD *, int );

	//VERIFICACIONES
int verificarMatricula(ListaD *, unsigned int );

#endif