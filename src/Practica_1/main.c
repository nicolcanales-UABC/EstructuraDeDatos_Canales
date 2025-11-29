//INCLUDES
#include <stdio.h>
#include <string.h>
#include "../Estructuras/Lista/lista.h"
//FUNCION MAIN
#define LONGITUD 100

typedef struct
{
	char nombre[LONGITUD];
	unsigned int mat;
	int semestres;
	float prom;
}Alumno;

//PROTOTIPOS
void* crearEntero(int dato);
int compararEnteros(void *a, void *b);
void imprimirEntero(void *a);
void* crearFlotante(float dato);
int compararFlotante(void *a, void *b);
void imprimirFlotante(void *a);
void* crearAlumno( Alumno a);
int compararAlumnos(void *a,void *b);
void imprimirAlumno(void *a);

//MIS PROTOTIPOS
void menu();
void capChar(char *);
int capInt();
float capFloat();
unsigned int capUnsigned();
int compararMat(void *, void *);
int compararSemestre(void *, void *);
int compararProm(void *, void *);
void ordenaTodo3000inador(Lista *, int);


/// FUNCIONALES
int verificarMatricula(Lista *, unsigned int );
void insertarAlumno(Lista *, unsigned int );
void insertarOrdenadoInador3000(Lista *,void* , int );
void desplegarParametro(Lista *, int );
void borrarAlumno(Lista *, int );
int verificarName(char *);

int main(void)
{
	//INICIALIZAMOS LISTA
	Lista lista;
	lista.inicio = NULL;
	lista.cant = 0;
	lista.imprimir = &imprimirAlumno;
	lista.comparar = &compararAlumnos;

	//DECLARAMOS VARIABLES
	int estado, option;
	unsigned int matAlum;
	//char nombreAlum[LONGITUD];
	//float promedio;

		//VARIABLES AUXILIARES
	//Nodo *q;
	//Alumno *apt;

	//SECCIÓN DE MENÚ

	do
	{
		menu();
		option = capInt();

		switch(option)
		{
			case 1:
			//REGISTRAR ALUMNO
				estado = 0;
				
				if(lista.cant != 0)
				{
					do
					{
						printf("\n Ingrese matricula del alumno: \n");
						matAlum = capUnsigned();
						estado = verificarMatricula(&lista, matAlum);
						
					}while(estado == 1);
				}
				else
				{
					printf("\n Ingrese matricula del alumno: \n");
					matAlum = capUnsigned();
				}
				insertarAlumno(&lista,matAlum);

				break;
			case 2:
			//DESPLEGAR ALUMNOS
				mostrarLista(lista);
				break;
			case 3:
			//REORDENAR LISTA
				printf("\n Seleccionar para ordenar en base a: ");
				printf("\n [1] Nombre");
				printf("\n [2] Matricula");
				printf("\n [3] Semestres");
				printf("\n [4] Promedio \n");
				
				estado = capInt();
				ordenaTodo3000inador(&lista, estado);

				break;
			case 4:
			//BUSCAR ALUMNO
				printf("\n Seleccionar para buscar en base a: ");
				printf("\n [1] Nombre");
				printf("\n [2] Matricula");
				printf("\n [3] Semestres");
				printf("\n [4] Promedio \n");
				
				estado = capInt();

				desplegarParametro(&lista, estado);

				break;
			case 5:
			//BORRAR ALUMNO
				printf("\n Ingrese la matricula del alumno que dara de baja: ");
				matAlum = capUnsigned();
				borrarAlumno(&lista,matAlum);
				break;
			default:
				break;
		}

	}while(option != 6);
	
	
	//mostrarLista(lista);
	borrarLista(&lista);
	return 0;
}


/// INTENTO

void insertarAlumno(Lista *lista, unsigned int matAlum)
{
	char name[LONGITUD];
	Alumno apt;
	int numSe;
	float promedio;

	do
	{
		printf("\n Ingrese Nombre del alumno: \n");
		capChar(name);

	}while((verificarName(name)) == 1);
	
	do
	{
		printf("\n Cantidad de semestres: \n");
		numSe = capInt();
		if(numSe > 15 || numSe < 1)
		{
			printf("\n Cantidad invalida de semestres");
		}
	}while(numSe > 15 || numSe < 1);

	do
	{
		printf("\n Promedio del alumno: \n");
		promedio = capFloat();
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
//
int verificarName(char *varChar)
{

	for(int i = 0; i<LONGITUD; i++)
	{
		if(varChar[i] == '\0')
		{
			return 0;
		}
		if(varChar[i] < 'A' || (varChar[i] > 'Z' && varChar[i]))
		{
			if(varChar[i] < 'a' || varChar[i] > 'z')
			{
				if(varChar[i] != ' ')
				{
					printf("\n NOMBRE INVALIDO");
					return 1;
				}
				
			}
		}
	}
	return 0;
}

/////////// CAPTURA //////////

void menu()
{
	printf("\n [1] Registrar alumno");
	printf("\n [2] Desplegar alumnos");
	printf("\n [3] Reordenar");
	printf("\n [4] Buscar alumno");
	printf("\n [5] Borrar alumno");
	printf("\n [6] FINALIZAR PROGRAMA \n");
}

void capChar(char *varChar)
{
	//char c;

	fgets(varChar,LONGITUD,stdin);

	for(int i = 0; i<LONGITUD; i++)
	{
		if(varChar[i] == '\n')
		{
			varChar[i] = '\0';
			break;
		}
	}
	//scanf("%s", varChar);
	//while( (c = getchar() ) != '\n' && c != EOF){} //Limpia el buff
}
int capInt()
{
	char c;
	int var;

	scanf("%d", &var);
	while( (c = getchar() ) != '\n' && c != EOF){} //Limpia el buff
	return var;

}

unsigned int capUnsigned()
{
	char c;
	unsigned int var;

	scanf("%u", &var);
	while( (c = getchar() ) != '\n' && c != EOF){} //Limpia el buff
	return var;

}
float capFloat()
{
	float flotante;
	char c;
	
	scanf("%f", &flotante);
	while( (c = getchar() ) != '\n' && c != EOF){} //Limpia el buff
	return flotante;
}

///////////

int compararMat(void *a, void *b) 
{
	Alumno *aa, *bb;
	
	aa = a; //Le asignamos el alumno
	bb = b;
	
	if( aa->mat < bb->mat)
	{
		//compararemos la matricula
		return -1;
	
	}
	else if(aa->mat > bb->mat)
	{
		return 1;
	}
	else
	{
		//Son iguales
		return 0;
	}
}
int compararSemestre(void *a, void *b) 
{
	Alumno *aa, *bb;
	
	aa = a; //Le asignamos el alumno
	bb = b;
	
	if( aa->semestres < bb->semestres)
	{
		//compararemos la matricula
		return -1;
	
	}
	else if(aa->semestres > bb->semestres)
	{
		return 1;
	}
	else
	{
		//Son iguales
		return 0;
	}
}
int compararProm(void *a, void *b)
{
	Alumno *aa, *bb;
	
	aa = a; //Le asignamos el alumno
	bb = b;
	
	if( aa->prom < bb->prom)
	{
		//compararemos la matricula
		return -1;
	
	}
	else if(aa->prom > bb->prom)
	{
		return 1;
	}
	else
	{
		//Son iguales
		return 0;
	}
}
void ordenaTodo3000inador(Lista *lista, int compara)
{
	//ESTA FUNCIÓN BUSCA ORDENAR LA LISTA EN BASE A LOS PARAMETROS SELECCIONADOS POR EL USER
		// COMPARA: 1 - NOMBRE, 2 - MATRICULA, 3 - SEMESTRES, 4 - PROMEDIO...
	Lista aux = (Lista){NULL, NULL, NULL, 0};
	Alumno *apt;
	Nodo *q;
	
	for(q = lista->inicio; q != NULL; q = q->sig)
	{
		apt = q->dato;
		insertarOrdenadoInador3000(&aux, apt, compara);
	}
	lista->inicio = aux.inicio;
}

/////////////////////////////

void borrarAlumno(Lista *lista, int matricula)
{
	Nodo *actual,*anterior = NULL;
	Alumno *aux;
	
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		aux = actual->dato;
		
		if(matricula == aux->mat)
		{
			if(anterior!=NULL)
				anterior->sig = actual->sig;
			else
				lista->inicio = actual->sig;
			//free(actual->dato);
			free(actual);
			lista->cant--;
			break;			
		}		
		anterior = actual;
	}	
}

void insertarOrdenadoInador3000(Lista *lista,void* dato, int estado)
{
	Nodo *nuevo = crearNodo(dato);
	Nodo *actual,*anterior=NULL;
	
	
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if(estado == 1)
		{
			//NOMBRE
			if( (compararAlumnos(dato,actual->dato)) == -1)
			{
				if(anterior!=NULL)
				{
					//INSERTO EN MEDIO
					anterior->sig = nuevo;
					nuevo->sig = actual;
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
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
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
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
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
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
				}
				else
				{
					//INSERTAR EN EL INICIO
					nuevo->sig = actual;
					lista->inicio = nuevo;
				}
				break;
			}
		}
		else
		{
			printf("\n NOT FOUND");
			return;
		}
		
		anterior = actual;
	}		
	if(lista->inicio == NULL) //LISTA VACIA : INSERTAR UNICO DATO
		lista->inicio = nuevo;
	else if ( anterior !=NULL) // RECORRI TODA LA LISTA: INSERTAR AL FINAL
		anterior->sig = nuevo;	
	lista->cant++;	
}

void desplegarParametro(Lista *lista, int estado)
{
	Nodo *q;
	Alumno *apt;
	char nombre[LONGITUD];
	int mat, sem, aux = 0;
	mat = sem = 0;
	float promedio = 0;
	
	switch(estado)
	{
		case 1:
		//NOMBRE
			printf("\n Ingrese nombre del alumno: ");
			capChar(nombre);
			break;
		case 2:
		//MATRÍCULA
			printf("\n Ingrese matricula: ");
			mat = capUnsigned();
			break;
		case 3:
		//SEMESTRE
			printf("\n Ingrese semestre: ");
			sem = capInt();
			break;
		case 4:
		//PROMEDIO
			printf("\n Ingrese promedio: ");
			promedio = capFloat();
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
			printf("\n Alumno %s encontrado", apt->nombre);
			printf("\n Matricula: %u", apt->mat);
			printf("\n Semestre: %d ", apt->semestres);
			printf("\n Promedio: %0.2f \n", apt->prom);
			aux = 1;
		}
		else if(apt->mat == mat && estado == 2)
		{
			printf("\n Matricula %u encontrada", apt->mat);
			printf("\n Esta matricula pertenece a %s", apt->nombre);
			printf("\n Semestre: %d ", apt->semestres);
			printf("\n Promedio: %0.2f \n", apt->prom);
			return;
		}
		else if(apt->semestres == sem && estado == 3)
		{
			printf("\n Semestre: %d ", apt->semestres);
			printf("\n Alumno: %s ", apt->nombre);
			printf("\n Matricula: %u", apt->mat);
			printf("\n Promedio: %0.2f \n", apt->prom);
			aux = 1;
		}
		else if(apt->prom == promedio && estado == 4)
		{
			printf("\n Promedio: %0.2f", apt->prom);
			printf("\n Alumno: %s ", apt->nombre);
			printf("\n Matricula: %u", apt->mat);
			printf("\n Semestre: %d \n", apt->semestres);
			aux = 1;
		}
	}
	
	if(aux == 0)
	{
		printf("\n Informacion no encontrada");
	}
	
}

///////// FUNCIONALES ///////

int verificarMatricula(Lista *lista, unsigned int mat)
{
	Nodo *q;
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

/////////////////////////////

void* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEnteros(void *a, void *b)
{
	int *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}

void imprimirEntero(void *a)
{
	int *ea;
	ea = a;
	printf("%d",*ea);
}

void* crearFlotante(float dato)
{
	float *nuevo = malloc(sizeof(float));
	*nuevo = dato;
	return nuevo;
}



int compararFlotante(void *a, void *b)
{
	float *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}


void imprimirFlotante(void *a)
{
	float *ea;
	ea = a;
	printf("%.2f",*ea);
}




void* crearAlumno( Alumno a)
{
	Alumno *nuevo = malloc(sizeof(Alumno));
	strcpy(nuevo->nombre, a.nombre);
	nuevo->mat = a.mat;
	nuevo->semestres = a.semestres;
	nuevo->prom = a.prom;
	//*nuevo = a;
	return nuevo;	
}

int compararAlumnos(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}
void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("%s_%u S:%d Prom: %0.2f",aa->nombre,aa->mat, aa->semestres, aa->prom);
	
}