#ifndef ALUMNO_H
#define ALUMNO_H

typedef struct
{
	char nombre[100];
	unsigned int mat;
	int semestres;
	float prom;
}Alumno;

void* crearAlumno( Alumno a);
void imprimirAlumno(void *a);

	//VERIFICACIONES

int verificarName(char *);
int compararAlumnos(void *a,void *b);
int compararMat(void *, void *);
int compararSemestre(void *, void *);
int compararProm(void *, void *);

#endif