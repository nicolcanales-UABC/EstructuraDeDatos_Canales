#include "alumno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGITUD 100

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
void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("%s_%u S:%d Prom: %0.2f",aa->nombre,aa->mat, aa->semestres, aa->prom);
	printf("\n");
}

    //VERIFICACIONES

int verificarName(char *varChar)
{

	for(int i = 0; i<LONGITUD; i++)
	{
		if(varChar[i] == '\0')
		{
			return 0;
		}
		if(varChar[i] < 'A' || varChar[i] > 'Z')
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

int compararAlumnos(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}

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