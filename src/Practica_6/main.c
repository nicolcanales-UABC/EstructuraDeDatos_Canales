
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Captura/captura.h"
#include "../Estructuras/Arbol/arbol.h"

typedef struct{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int entero;
}Resultado;

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

Resultado busquedaEnNodos(NodoA *padre, NodoA *raiz, void *dato, int (*comparar)(void *, void *));
void eliminarNodo(Resultado *res, Arbol *arbol);
void eliminarNodo2(Resultado *res, Arbol *arbol);


int main(void){
	
	int option, aux;
	Resultado res;
	Arbol arbolA, arbolB;
	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = &liberarInt;
	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = &liberarInt;
	
	do
	{
		printf("\n [1] Insertar en Arbol A \n [2] Insertar en Arbol B");
		printf("\n [3] Comparar Arboles \n [4] Eliminar dato en Arbol A");
		printf("\n [5] Eliminar dato en Arbol B \n [6] Profundidades");
		printf("\n [7] Equilibrar arboles \n [8] Mostrar Arboles");
		printf("\n [9] Terminar programa");
		inputEntero("\n Selecciona opcion: ",&option);
		
		switch(option)
		{
			case 1:
			//INSERTAR EN ARBOL A
				inputEntero("\n Ingrese numero entero: ",&aux);
				insertarArbol(&arbolA, crearEntero(aux));
				imprimirArbol(arbolA);
				break;
			case 2:
			//INSERTAR EN ARBOL B
				inputEntero("\n Ingrese numero entero: ",&aux);
				insertarArbol(&arbolB, crearEntero(aux));
				imprimirArbol(arbolB);
				break;
			case 3:
			//COMPARAR ARBOLES
				compararArbol(arbolA,arbolB);
				break;
			case 4:
			//ELIMINAR DATO EN ARBOL A
				inputEntero("\n Ingrese numero entero: ",&aux);
				res = busquedaEnNodos(NULL, arbolA.raiz,&aux, arbolA.comparar);
				
				if(res.entero != -1)
				{
					eliminarNodo2(&res,&arbolA);
				}
				else
				{
					printf("\n Dato no encontrado");
				}

				break;
			case 5:
			//ELIMINAR DATO EN ARBOL B
				inputEntero("\n Ingrese numero entero: ",&aux);
				res = busquedaEnNodos(NULL, arbolB.raiz,&aux, arbolB.comparar);
				if(res.entero != -1)
				{
					eliminarNodo2(&res,&arbolB);
				}
				else
				{
					printf("\n Dato no encontrado");
				}
				break;
			case 6:
			//PROFUNDIDADES
				aux = altura(arbolA);
				printf("\n ARBOL A: %d", aux);
				aux = altura(arbolB);
				printf("\n ARBOL B: %d", aux);
				break;
			case 7:
			//EQUILIBRAR ARBOLES
				equilibrar(&arbolA);
				equilibrar(&arbolB);
				break;
			case 8:
			//MOSTRAR ARBOLES
				printf("\n ARBOL A: \n");
				imprimirArbol(arbolA);
				printf("\n ARBOL B: \n");
				imprimirArbol(arbolB);
				break;
			case 9:
			//FINALIZAR PROGRAMA
				break;
			default:
				break;
		}
		
	}while(option != 9);
	
	return 0;

}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}


void eliminarNodo2(Resultado *res, Arbol *arbol)
{
	NodoA *dirDato = res->nodo;
	NodoA *padre = res->padre;
	NodoA *aux;
	int posicion = res->entero;

	if(dirDato->izq == NULL && dirDato->dch == NULL)
	{
		if(padre == NULL)
		{
			arbol->raiz = NULL;
		}
		else if(posicion == 1)
		{
			padre->izq = NULL;
		}
		else
		{
			//SIGNIFICA QUE EL NODO ESTA EN DERECHA
			padre->dch = NULL;
		}
		free(dirDato);
		arbol->cantidad = arbol->cantidad - 1;
		return;
	}

	if(dirDato->izq == NULL || dirDato->dch == NULL)
	{
		//SIFNICA QUE TIENE SOLO 1 HIJO
		
		if(dirDato->izq != NULL)
		{
			aux = dirDato->izq;
		}
		else{
			aux = dirDato->dch;
		}
		
		if(padre == NULL)
		{
			arbol->raiz = aux;
		}
		else if(posicion == 1)
		{
			padre->izq = aux;
		}
		else
		{
			padre->dch = aux;
		}
		free(dirDato);
		arbol->cantidad = arbol->cantidad - 1;
		return;
	}
	NodoA *liberar = dirDato;
	aux = dirDato->dch;

	while(aux->izq != NULL)
	{
		liberar = aux;
		aux = aux->izq;
	}
	dirDato->dato = aux->dato;

	if(liberar->izq == aux)
	{
		liberar->izq = aux->dch;
	}
	else{
		liberar->dch = aux->dch;
	}

	free(aux);
	arbol->cantidad = arbol->cantidad - 1;

}

void eliminarNodo(Resultado *res, Arbol *arbol)
{
	//ELIMINAMOS DATO DE ACUERDO A LOS PARAMETROS DE RESULTADO
	NodoA *dirDato = res->nodo;
	NodoA *padre = res->padre;
	NodoA *aux;
	int posicion = res->entero;

	if(dirDato->izq == NULL)
	{
		if(dirDato->dch == NULL)
		{
			if(posicion == 1)
			{
				padre->izq = NULL;
			}
			else
			{
				padre->dch = NULL;
			}	
			free(dirDato);
			return;
		}
		aux = dirDato->dch;
		if(posicion == 1)
		{
			padre->izq = aux;
		}
		else
		{
			padre->dch = aux;
		}
		free(dirDato);
		return;
	}

	if(dirDato->dch == NULL)
	{
		if(posicion == 1)
		{
			//IZQUIERDA
			padre->izq = dirDato->izq;
		}
		else{
			padre->dch = dirDato->izq;
		}
	}
	 
	aux = dirDato->dch;
	if(padre == NULL)
	{
		//SIGNIFICA QUE ESTAMOS ELIMINANDO LA RAIZ
			//CAMBIAMOS DE RAIZ
		arbol->raiz = aux;
	}
	else
	{
		padre->izq = aux;
	}
	
	while(aux->izq != NULL)
	{
		aux = aux->izq;
	}
	aux->izq = dirDato->izq;
	dirDato->dch = NULL;
	dirDato->izq = NULL;
	free(dirDato);
}

//A VER

Resultado busquedaEnNodos(NodoA *padre, NodoA *raiz, void *dato, int (*comparar)(void *, void *)){
	
	Resultado aux;
	//= (Resultado){NULL, NULL, NULL, -1};

	if(!raiz)
	{
		return (Resultado){NULL, NULL, NULL, -1};
	}
	if(comparar(raiz->dato, dato) == 0)
	{
		return (Resultado){padre, raiz, raiz->dato,(padre && padre->izq == raiz) ? IZQUIERDA:DERECHA};
	}
	aux = busquedaEnNodos(raiz, raiz->izq, dato, comparar);
	if(!aux.dato)
		aux = busquedaEnNodos(raiz, raiz->dch, dato, comparar);
	return aux;
}

Resultado buscarEnArbol(Arbol arbol, void *dato){
	Resultado res = busquedaEnNodos(NULL, arbol.raiz, dato, arbol.comparar);
	return res;
}