#include "listadoble.h"
#include "../../Practica_2/alumno.h"
#include <stdio.h>
#include <string.h>

#define LONGITUD 100

ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}

void mostrarListaD(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: \n",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf(" ");
		imprimirAlumno(p->dato);
	}
	printf("NULL");
}
void mostrarListaA(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: \n",lista.cant);
	p = lista.fin;
	
	for( p = lista.fin ;  p!=NULL ; p = p->ant )
	{
		printf(" ");
		imprimirAlumno(p->dato);
	}
	printf("NULL");
}
void mostrarApuntadores(ListaD lista)
{
	NodoD *q, *aux_a, *aux_b;
	Alumno *apt, *a, *b;
	
	q = lista.fin;
	apt = q->dato;
	
	printf("\n ULTIMO DATO DE LA LISTA %s", apt->nombre);
	
	printf("\n Lista[%d]: ",lista.cant);
	for(q = lista.inicio; q != NULL; q = q->sig)
	{
		apt = q->dato;
		printf("\n %s", apt->nombre);
		
		if(q->sig != NULL)
		{
			aux_a = q->sig;
			a = aux_a->dato;
			printf("\n SIGUIENTE: %s", a->nombre);
		}
		else
		{
			printf("\n SIGUIENTE: NULL");
		}
		if(q->ant != NULL)
		{
			aux_b = q->ant;
			b = aux_b->dato;
			printf("\n ANTERIOR: %s", b->nombre);
		}
		else
		{
			printf("\n ANTERIOR: NULL");
		}
		
	}

}
void insertarEnPosicion(ListaD *lista,void* dato,int pos)
{	
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos <= lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<=lista->cant  ; i++)
		{
			if( i==pos)
			{
				if(anterior == NULL)
				{
					insertarInicio(lista,dato);
					return;
				}
				else
				{
					NodoD *nuevo = crearNodo(dato);
					nuevo->sig = actual;
					anterior->sig = nuevo;
					nuevo->ant = anterior;
					lista->fin = nuevo;
					
					lista->cant++;
					return;
				
				}
			}
			anterior = actual;
			actual = actual->sig;
		}				
	}	
}

void insertarInicio(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodo(dato);
	nuevo->sig = lista->inicio;
	lista->inicio = nuevo;	
	lista->fin = nuevo;
	lista->cant++;
}

void borrarAlumno(ListaD *lista, int matricula)
{
	NodoD *siguiente, *actual,*anterior = NULL;
	Alumno *aux;
	
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		aux = actual->dato;
		
		if(matricula == aux->mat)
		{
			if(anterior!=NULL)
			{
				if(actual->sig != NULL)
				{
					siguiente = actual->sig;
					anterior->sig = siguiente;
					siguiente->ant = anterior;
				}
				else
				{
					anterior->sig = actual->sig;
				}
			}
			else
			{
				lista->inicio = actual->sig;
			}
			//free(actual->dato);
			free(actual);
			lista->cant--;
			break;			
		}		
		anterior = actual;
	}	
}

void ordenaTodo3000inador(ListaD *lista, int compara)
{
	//ESTA FUNCIÓN BUSCA ORDENAR LA LISTA EN BASE A LOS PARAMETROS SELECCIONADOS POR EL USER
		// COMPARA: 1 - NOMBRE, 2 - MATRICULA, 3 - SEMESTRES, 4 - PROMEDIO...
	ListaD aux = (ListaD){NULL, NULL, 0, NULL, NULL, NULL};
	Alumno *apt;
	NodoD *q;
	
	for(q = lista->inicio; q != NULL; q = q->sig)
	{
		apt = q->dato;
		insertarOrdenadoInador3000(&aux, apt, compara);
	}
	for(q = aux.inicio; q != NULL; q = q->sig)
	{
		aux.fin = q;
		apt = q->dato;
		//printf("\n fin de lista: %s", apt->nombre);
	}
	
	lista->inicio = aux.inicio;
	lista->fin = aux.fin;
}
void insertarOrdenadoInador3000(ListaD *lista,void* dato, int estado)
{
	NodoD *nuevo = crearNodo(dato);
	NodoD *actual,*anterior=NULL;
	//Alumno *aux_a, *aux_b;
	
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if(estado == 1)
		{
			//NOMBRE
			if( (compararAlumnos(dato,actual->dato)) == -1)
			{
				//aux_a = nuevo->dato;
				//aux_b = actual->dato;
				//printf("\n nuevo: %s actual: %s", aux_a->nombre, aux_b->nombre);
				
				if(anterior!=NULL)
				{
					//INSERTO EN MEDIO
					anterior->sig = nuevo;
					nuevo->sig = actual;
					nuevo->ant = anterior;
					actual->ant = nuevo;
					
				}
				else
				{
					//INSERTAR EN EL INICIO
					//printf("\n Insertar en inicio %s", aux_a->nombre);
					nuevo->sig = actual;
					actual->ant = nuevo;
					lista->inicio = nuevo;
				}
				break;
			}
		}
		else if(estado == 2)
		{
			//MATRICULA
			if((compararMat(dato,actual->dato)) == -1)
			{
				if(anterior!=NULL)
				{
					//INSERTO EN MEDIO
					anterior->sig = nuevo;
					nuevo->sig = actual;
					nuevo->ant = anterior;
					actual->ant = nuevo;
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
					actual->ant = nuevo;
					lista->inicio = nuevo;
				}
				break;
			}
		}
		else if(estado == 3)
		{
			//SEMESTRE
			if((compararSemestre(dato,actual->dato)) == -1)
			{
				if(anterior!=NULL)
				{
					//INSERTO EN MEDIO
					anterior->sig = nuevo;
					nuevo->sig = actual;
					nuevo->ant = anterior;
					actual->ant = nuevo;
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
					actual->ant = nuevo;
					lista->inicio = nuevo;
				}
				break;
			}
		}
		else if(estado == 4)
		{
			//PROMEDIO
			if((compararProm(dato,actual->dato)) == -1)
			{
				if(anterior!=NULL)
				{
					//INSERTO EN MEDIO
					anterior->sig = nuevo;
					nuevo->sig = actual;
					nuevo->ant = anterior;
					actual->ant = nuevo;
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
					actual->ant = nuevo;
					lista->inicio = nuevo;
				}
				break;
			}
		}
		else
		{
			//CUANDO ESTADO ES INCORRECTO
			printf("\n NOT FOUND");
			return;
		}
		
		anterior = actual;
	}		
	if(lista->inicio == NULL) //LISTA VACIA : INSERTAR UNICO DATO
	{
		lista->inicio = nuevo;
		//lista->fin = nuevo;
	}
	else if ( anterior !=NULL) // RECORRI TODA LA LISTA: INSERTAR AL FINAL
	{
		anterior->sig = nuevo;
		nuevo->ant = anterior;
		//lista->fin = nuevo;
	}
	lista->cant++;	
}

//ALUMNO

void insertarAlumno(ListaD *lista, unsigned int matAlum)
{
	char name[LONGITUD];
	Alumno apt;
	int numSe;
	float promedio;

	do
	{
		inputCadena("\n Ingrese Nombre del alumno: \n",name,LONGITUD); 
	}while((verificarName(name)) == 1);
	
	do
	{
		inputEntero("\n Cantidad de semestres: \n",&numSe);
		
		if(numSe > 15 || numSe < 1)
		{
			printf("\n Cantidad invalida de semestres");
		}
	}while(numSe > 15 || numSe < 1);

	do
	{
		inputFloat("\n Promedio del alumno: \n", &promedio);
		if(promedio > 100 || promedio < 0)
		{
			printf("\n Promedio invalido");
		}

	}while(promedio > 100 || promedio < 0);

	strcpy(apt.nombre, name);
	apt.mat = matAlum;
	apt.semestres = numSe;
	apt.prom = promedio;
	insertarEnPosicion(lista, crearAlumno( apt ) , lista->cant );
}
void desplegarParametro(ListaD *lista, int estado)
{
	NodoD *q;
	Alumno *apt;
	char nombre[LONGITUD];
	unsigned int mat;
	int sem, aux = 0;
	float promedio;
	
	switch(estado)
	{
		case 1:
		//NOMBRE
			inputCadena("\n Ingrese Nombre del alumno: \n",nombre,LONGITUD);
			break;
		case 2:
		//MATRÍCULA
			inputUnsigned("\n Ingrese matricula del alumno: ",&mat);
			break;
		case 3:
		//SEMESTRE
			inputEntero("\n Cantidad de semestres: \n",&sem);
			break;
		case 4:
		//PROMEDIO
			inputFloat("\n Promedio del alumno: \n", &promedio);
			break;
		default:
			printf("\n ERROR 404. ESTADO INCORRECTO");
			return;
	}
	for(q = lista->inicio; q != NULL; q = q->sig)
	{
		apt = q->dato;
		
		if((strcmp(apt->nombre,nombre)) == 0 && estado == 1)
		{
			imprimirAlumno(q->dato);
			
			aux = 1;
		}
		else if(apt->mat == mat && estado == 2)
		{
			imprimirAlumno(q->dato);
			return;
		}
		else if(apt->semestres == sem && estado == 3)
		{
			imprimirAlumno(q->dato);
			aux = 1;
		}
		else if(apt->prom == promedio && estado == 4)
		{
			imprimirAlumno(q->dato);
			aux = 1;
		}
		
	}
	
	if(aux == 0)
	{
		printf("\n Informacion no encontrada");
	}
	
}

//VERIFICACIONES

int verificarMatricula(ListaD *lista, unsigned int mat)
{
	NodoD *q;
	Alumno *apt;
	
	for(q = lista->inicio; q != NULL; q = q->sig)
	{
		apt = q->dato;
		
		if(apt->mat == mat)
		{
			printf("\n Matricula %u encontrada", apt->mat);
			printf("\n Esta matricula pertenece a %s", apt->nombre);
			return 1;
		}
	}
	return 0;
}
