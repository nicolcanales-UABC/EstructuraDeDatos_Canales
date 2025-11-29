
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Estructuras/Nodo/nodo.h"
#include "../Estructuras/Cola/cola.h"
#include "../Captura/captura.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50


typedef struct
{
	Cola cola;
	int estado;
}Caja;



int* generar_articulos(void);
void imprimirEntero(void*);

int main(void)
{
	Caja cajas[NUMERO_CAJAS];
	
	for(int i=0; i<NUMERO_CAJAS ; i++)
	{
		cajas[i].cola = inicializarCola();
		cajas[i].cola.imprimir = &imprimirEntero;
		cajas[i].estado = HABILITADA;
	}
	int opcion;	
	int *aux_art;
	int j;

	do
	{
		
		for(int i=0; i<NUMERO_CAJAS ; i++)
		{
			printf("\n Caja[%d]: ",i+1);
			imprimirCola(cajas[i].cola);
		}
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n [1] Generar clientes");
		printf("\n [2] Escanear articulos");
		printf("\n [3] Habilitar caja");
		printf("\n [4] Deshabilitar caja");
		printf("\n [5] TERMINAR PROGRAMA");
		inputEntero("\n Selecciona opcion: ",&opcion);
		
		switch(opcion)
		{
			case 1:
			//GENERAR CLIENTES
				for(int i=0; i<NUMERO_CAJAS ; i++)
				{
					//SI ESTA HABILITADA Y SI NO ESTA LLENA
					//GENERAR Y FORMAR CLIENTE
					//printf(" \n caja [%d], estado: %d, cantidad: %d", i+1,cajas[i].estado,cajas[i].cola.cantidad);
					if(cajas[i].estado == HABILITADA) 
					{
						if(!llenaC(cajas[i].cola))
						{
							enqueue( &cajas[i].cola , generar_articulos() );
						}
							
					}
				}
				break;
			case 2:
			//ESCANEAR ARTICULOS
				for(int i=0; i<NUMERO_CAJAS ; i++)
				{
					//SI ESTA HABILITADA Y SI NO ESTA LLENA
					//GENERAR Y FORMAR CLIENTE
					
					if(!vaciaC(cajas[i].cola))
					{
						aux_art = cajas[i].cola.inicio->dato;
						
						if(*aux_art == 1)
						{
							dequeue( &cajas[i].cola);
						}
						else
						{
							*(aux_art) = *(aux_art)-1;
							//printf("\n %d", *aux_art);
						}
					}
					
				}
				break;
			case 3:
			//HABILITAR CAJA
				inputEntero("\n Ingrese numero de fila a habilitar: ",&j);
				j--;
				
				if(cajas[j].estado == HABILITADA)
				{
					printf("\n CAJA YA HABILITADA");
				}
				else
				{
					cajas[j].estado = HABILITADA;
				}
				break;
			case 4:
			//DESHABILITAR CAJA
				inputEntero("\n Ingrese numero de fila a deshabilitar: ",&j);
				j--;
				
				if(cajas[j].estado == DESHABILITADA)
				{
					printf("\n CAJA YA DESHABILITADA");
				}
				else
				{
					cajas[j].estado = DESHABILITADA;
				}
				break;
			case 5:
			//FINALIZAR 
				
				break;
			default:
				
				break;	
				
		}	
	}while(opcion!=5);
	
	printf("\n\n FIN DE PROGRAMA");
	return 0;
}


int* generar_articulos(void)
{		
	int *articulos = malloc(sizeof(int));
	*articulos = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
	return articulos; 
	
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}

