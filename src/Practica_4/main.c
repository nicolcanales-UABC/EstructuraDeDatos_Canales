#include <stdio.h>
#include <stdlib.h>

#include "../Estructuras/Nodo/nodo.h"
#include "../Estructuras/Pila/pila.h"
#include "coordenada.h"

//IMPLEMENTAR PILA


int main(void)
{
    int i,j = 0;
	Pila pila = {NULL,-1,0,&imprimirCoordenada};
    
	Coordenada *coord = NULL;
	int stop = 0;
    unsigned char **lab; 
	unsigned char banderaDeMexico;
    lab = crear_laberinto();
	lab[9][1] = 'B';
	imprimirLab(lab);
	
	for(i = 0; i<REN; i++)
	{
		for(j = 0; j<COL; j++)
		{
			if(lab[i][j] == 'A')
			{
				coord = crearCoordenada(i,j);
				imprimirCoordenada(coord);
				stop = 1;
				break;
			}
			if(stop == 1)
			{
				break;
			}
		}
		if(stop == 1)
		{
			break;
		}
	}
	//repetir while(lab[coord->x][coord->y] != 'B')
	//lab[coord->x][coord->y] = (lab[coordenada->x][coordenada->y] != 'B')?'.':'B';
	stop = 0;
	
	do
	{
		
		banderaDeMexico = alternativas(lab,coord);
		
		if((banderaDeMexico&ARRIBA) != 0)
		{
			//movemos x-1
			push(&pila, coord);
			if(lab[i][j] != 'x' && lab[i][j] != 'A' && lab[i][j] != 'B' && lab[i][j] != '.' && lab[i][j] != 'o')
			{
				lab[i][j] = '.';
			}
			
			i = coord->x;
			i--;
			j = coord->y;
			coord = crearCoordenada(i,j);
			imprimirCoordenada(coord);
		}
		else if((banderaDeMexico&ABAJO) != 0)
		{
			//movemos x+1
			push(&pila, coord);
			
			if(lab[i][j] != 'x' && lab[i][j] != 'A' && lab[i][j] != 'B' && lab[i][j] != '.' && lab[i][j] != 'o')
			{
				lab[i][j] = '.';
			}
			
			i = coord->x;
			i++;
			j = coord->y;
			coord = crearCoordenada(i,j);
			imprimirCoordenada(coord);
		}
		else if((banderaDeMexico&DERECHA) != 0)
		{
			//movemos y+1
			push(&pila, coord);
			if(lab[i][j] != 'x' && lab[i][j] != 'A' && lab[i][j] != 'B' && lab[i][j] != '.' && lab[i][j] != 'o')
			{
				lab[i][j] = '.';
			}
			
			i = coord->x;
			j = coord->y;
			j++;
			coord = crearCoordenada(i,j);
			imprimirCoordenada(coord);
		}
		else if((banderaDeMexico&IZQUIERDA) != 0)
		{
			//movemos y-1
			push(&pila, coord);
			if(lab[i][j] != 'x' && lab[i][j] != 'A' && lab[i][j] != 'B' && lab[i][j] != '.' && lab[i][j] != 'o')
			{
				lab[i][j] = '.';
			}
			
			i = coord->x;
			j = coord->y;
			j--;
			coord = crearCoordenada(i,j);
			
			imprimirCoordenada(coord);
		}
		else if(banderaDeMexico == 0)
		{
			lab[coord->x][coord->y] = 'o';
			coord = pop(&pila);

			i = coord->x;
			j = coord->y;
			
		}
		i = coord->x;
		j = coord->y;

		printf("\n");
		imprimirLab(lab);
		
		stop++;
		
	}while(lab[coord->x][coord->y] != 'B' && !vacia(pila));
	
	imprimirPilaInvertida(pila);

    printf("\n\n");
	eliminarPila(&pila);
    return 0;
}



