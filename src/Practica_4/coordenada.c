
#include "coordenada.h"

unsigned char ** crear_laberinto(void)
{
    int i,j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

 
    
    unsigned char **lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    
    for(i=0;i<REN;i++)
    {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    
    for(i=0;i<REN;i++)
    {
        //printf("\n\r");
        for(j=0;j<COL;j++)
        {
            //printf("%c",tmp[(i*COL)+j]);
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}


void imprimirLab(unsigned char **lab)
{
	int i,j;
	for(i=0;i<REN;i++)
    {
        printf("\n\r");
        for(j=0;j<COL;j++)
        {
            if(lab[i][j]=='*')printf("  ");
			else printf("%c ",lab[i][j]);
        }   
    }
}

Coordenada* crearCoordenada(int x,int y)
{
	Coordenada *nueva = malloc(sizeof(Coordenada));
	nueva->x=x;
	nueva->y=y;
	return nueva;
}


void imprimirCoordenada(void *dato)
{
	Coordenada *a = dato;
	printf("[%-2d,%-2d]", a->x,a->y);
}
//ESTA NO SE USA
int compararCoordenada(void *a,void *b) 
{
	Coordenada *aa=a,*bb=b;
	if(aa->x==bb->x && aa->y==bb->y)
		return 1;
	return 0;
}


unsigned char alternativas(unsigned char **lab,Coordenada *coordenada)
{		
	unsigned char caracter;
	unsigned char banderas;
	banderas = 0;	
	//EVALUAR ALTERNATIVA Y REGISTRAR POSIBILIDAD DE MOVIMIENTO
	//EN UN REGISTRO DE BITS/BANDERAS	
	caracter = lab[coordenada->x-1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ARRIBA;
	
	caracter = lab[coordenada->x+1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ABAJO;
	
	caracter = lab[coordenada->x][coordenada->y+1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= DERECHA;
	
	caracter = lab[coordenada->x][coordenada->y-1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= IZQUIERDA;
	if(banderas != 0)
	{
		return banderas;
	}
	
	return banderas;
}


void imprimirPosibles(unsigned char caminos)
{
	if(caminos&ARRIBA)
		printf("\n ARRIBA");
	if(caminos&ABAJO)
		printf("\n ABAJO");
	if(caminos&IZQUIERDA)
		printf("\n IZQUIERDA");
	if(caminos&DERECHA)
		printf("\n DERECHA");
}