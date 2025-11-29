#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Captura/captura.h"
#include "../Estructuras/Heap/heap.h"

typedef struct{
	char *nombre;
	int noPaginas;
}Archivo;

int compararEntero(void*,void*);
void imprimirEntero(void*);
void estadoHeap(Heap heap, const char *tiempo);
void agregarArchivo(Heap *heap);
void imprimirArchivo(void *);
void procesarArchivo(Heap *heap);
void eliminarArchivo(Heap *heap);
void archivoCLS(Heap *heap);
void imprimirA5(Heap heap);
int compararArchivo(void*a,void*b);

int main(void)
{
	Heap heap = inicializarHeap( &imprimirArchivo,&compararArchivo);
	int option;

	do{

		imprimirA5(heap);

		printf("\n [0] CAMBIAR PRIORIDAD \n [1] MOSTRAR COLA DE IMPRESION");
		printf("\n [2] AGREGAR ARCHIVO \n [3] PROCESAR / IMPRIMIR ARCHIVO");
		printf("\n [4] ELIMINAR ARCHIVO \n [5] ELIMINAR TODOS LOS ARCHIVOS");
		printf("\n [6] TERMINAR PROGRAMA");
		inputEntero("\n Selecciona opcion: ",&option);

		switch(option)
		{
			case 0:
			//CAMBIAR PRIORIDAD
				estadoHeap(heap,"ANTES");
				printf("\n HEAP CAMBIADO A: ");
				if(heap.tipo == MIN){
					heap.tipo = MAX;
					printf("MAXIMO\n");
				}
				else{
					heap.tipo = MIN;
					printf("MIXNIMO\n");
				}
				heapify(&heap);
				estadoHeap(heap,"DESPUES");
				break;
			case 1:
			//MOSTRAR COLA DE IMPRESION
				printf("\n COLA DE IMPRESION: ");
				imprimirHeap(heap);
				break;
			case 2:
			//AGREGAR ARCHIVO
				estadoHeap(heap,"ANTES");
				agregarArchivo(&heap);
				estadoHeap(heap,"DESPUES");
				break;
			case 3:
			//PROCESAR / IMPRIMIR ARCHIVO
				estadoHeap(heap,"ANTES");
				procesarArchivo(&heap);
				estadoHeap(heap,"DESPUES");
				break;
			case 4:
			//ELIMINAR ARCHIVO A SELECCION
				estadoHeap(heap,"ANTES");
				eliminarArchivo(&heap);
				estadoHeap(heap,"DESPUES");
				break;
			case 5:
			//ELIMINAR TODOS LOS ARCHIVOS
				estadoHeap(heap,"ANTES");
				archivoCLS(&heap);
				estadoHeap(heap,"DESPUES");
				break;
			default:
			//INVALID OPTION
				break;
		}
	}while(option != 6);

	
	
	while( heap.cantidad )
	{
		void *x = quitarHeap(&heap);
		imprimirEntero(x);
	}
	
	printf("\n\n\n");
	
	return 0;
}

void imprimirA5(Heap heap)
{
	printf("\n\n");
	printf("\n -----------------------------------\n");
	if(heap.cantidad == 0)
		return;
	
	int aux;
	
	if(heap.cantidad < 5)
	{
		aux = heap.cantidad;
	}
	else
	{
		aux = 5;
	}

	for(int i = 0; i<aux;i++)
	{
		heap.imprimir(heap.arr[i]->dato);
	}
	printf("\n -----------------------------------\n");
	printf("\n\n");
}

void archivoCLS(Heap *heap)
{
	if(heap->cantidad == 0)
		return;
	Archivo *aux;
	for(int i = 0; i<heap->cantidad;i++)
	{
		aux = heap->arr[i]->dato;
		free(aux->nombre);
		free(aux);
		free(heap->arr[i]);
	}
	heap->cantidad = 0;
	heap->arbol.cantidad = 0;
	heap->arbol.raiz = NULL;
}

void eliminarArchivo(Heap *heap)
{
	if(heap->cantidad == 0)
		return;
	Archivo *a;
	int aux;
	printf("\nARCHIVOS DISPONIBLES: ");
	for(int i = 0; i<heap->cantidad;i++)
	{
		a = heap->arr[i]->dato;
		printf("[%d] %s: %d", (i+1),a->nombre,a->noPaginas);
	}
	inputEntero("\n Selecciona archivo a eliminar (numero): ",&aux);
	aux--;
	a = heap->arr[aux]->dato;
	free(a->nombre);
	free(a);
	free(heap->arr[aux]);

	heap->arr[aux] = heap->arr[heap->cantidad - 1];
	heap->cantidad--;

	if(heap->cantidad  > 0)
	{
		heap->arr = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
		heapify(heap);
	}
	else
	{
		free(heap->arr);
		heap->arr = NULL;
	}
	

}

void procesarArchivo(Heap *heap){
	//ELIMINAMOS EL ARCHIVO DE MAYOR PRIORIDAD
	if(heap->cantidad == 0)
		return;
	Archivo *a = (Archivo*)quitarHeap(heap);
	free(a->nombre);
	free(a);
}

void estadoHeap(Heap heap, const char *tiempo)
{
	printf("\n             %s", tiempo);
	printf("\n -----------------------------------");
	printf("\n HEAP: ");
	if(heap.cantidad == 0)
	{
		printf(" Vacio \n");
	}
	else
	{
		imprimirHeap(heap);
		printf("\n\n ");
		imprimirArbol(heap.arbol);
	}

}

void agregarArchivo(Heap *heap)
{
	Archivo *archivo = (Archivo*)calloc(1,sizeof(Archivo));
	int cantPaginas;
	char cad[100];

	inputCadena("\n Ingrese nombre del archivo: ", cad, 100);
	archivo->nombre = cadenaDinamica(cad);
	do{
		inputEntero("\n Ingrese cantidad de paginas: ",&cantPaginas);
	}while(cantPaginas <= 0);
	
	archivo->noPaginas = cantPaginas;
	insertarHeap(heap,archivo);
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf(" [ %d ]",*aa);
}
void imprimirArchivo(void *arch){
	Archivo *a = (Archivo *)arch;
	printf(" [ %s: %d ]",a->nombre,a->noPaginas);
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}
int compararArchivo(void*a,void*b)
{
	Archivo *aa = (Archivo*)a;
	Archivo *bb = (Archivo*)b;
	if(aa->noPaginas==bb->noPaginas)return 0;
	else if(aa->noPaginas<bb->noPaginas)return -1;
	else return 1;
}