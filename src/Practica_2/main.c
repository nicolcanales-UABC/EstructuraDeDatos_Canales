#include <stdio.h>

#include "../Estructuras/ListaDoble/listadoble.h"
#include "../captura/captura.h"

#define LONGITUD 100

int main(void)
{
	
	int option, estado;
	unsigned int matAlum;
	
		//INICIALIZAR LISTA
	ListaD lista;
	lista = inicializarListaD();

	do
	{
			//DESPLEGAMOS MENÚ
		printf("\n [1] - Registrar Alumno");
		printf("\n [2] - Desplegar Alumnos");
		printf("\n [3] - Reordenar");
		printf("\n [4] - Buscar Alumno");
		printf("\n [5] - Borrar Alumno");
		printf("\n [6] - FINALIZAR PROGRAMA");
		inputEntero("\n Por favor realice su seleccion: ",&option);
		
		switch(option)
		{
			case 1:
			//REGISTRAR ALUMNO
				estado = 0;
				
				if(lista.cant != 0)
				{
					do
					{
						inputUnsigned("\n Ingrese matricula del alumno: ",&matAlum);
						estado = verificarMatricula(&lista, matAlum);
						
					}while(estado == 1);
				}
				else
				{
					inputUnsigned("\n Ingrese matricula del alumno: ",&matAlum);
				}
				insertarAlumno(&lista,matAlum);
				break;
			case 2:
			//DESPLEGAR ALUMNOS: [1] - ASCENDENTE / [2] - DESCENDENTE
					//AÑADIR ORDEN DESCENDENTE
					
				printf("\n [1] Ascendente");
				printf("\n [2] Descendente");
				inputEntero(" ",&estado);
				
				if(estado == 1)
				{
					mostrarListaD(lista);
				}
				else if(estado == 2)
				{
					mostrarListaA(lista);
				}
				else
				{
					printf("\n Seleccion incorrecta");
				}
				
				
				break;
			case 3:
			//REORDENAR
				printf("\n Seleccionar para ordenar en base a: ");
				printf("\n [1] Nombre");
				printf("\n [2] Matricula");
				printf("\n [3] Semestres");
				printf("\n [4] Promedio \n");
				inputEntero(" ",&estado);
				ordenaTodo3000inador(&lista, estado);
				//mostrarApuntadores(lista);
				
				mostrarListaD(lista);
				break;
			case 4:
			//BUSCAR ALUMNO: PARAMETROS (MAT, NOM, SEM, PROM)
				printf("\n Seleccionar para buscar en base a: ");
				printf("\n [1] Nombre");
				printf("\n [2] Matricula");
				printf("\n [3] Semestres");
				printf("\n [4] Promedio \n");
				
				inputEntero(" ",&estado);
				
				desplegarParametro(&lista, estado);
				
				break;
			case 5:
			//BORRAR ALUMNO
				inputUnsigned("\n Ingrese la matricula del alumno que dara de baja: ",&matAlum);
				borrarAlumno(&lista,matAlum);
				break;
			case 6:
			//FINALIZAR PROGRAMA
			
				break;
			case 7:
				mostrarApuntadores(lista);
				break;
			default:
				break;
		}
		
	}while(option != 6);

	return 0;
}
