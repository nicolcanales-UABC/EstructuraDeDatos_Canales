#ifndef COORDENADA_H
#define COORDENADA_H


#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

#define REN 27
#define COL 26

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int x,y;
}Coordenada;


unsigned char ** crear_laberinto(void);
void imprimirLab(unsigned char **lab);

Coordenada* crearCoordenada(int x,int y);
int compararCoordenada(void *a,void *b);
void imprimirCoordenada(void *dato);

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada);
void imprimirPosibles(unsigned char);


#endif