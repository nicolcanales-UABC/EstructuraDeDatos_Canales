//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Captura/captura.h"
#include "../Estructuras/Pila/pila.h"
//FUNCION MAIN

#define LONGITUD 64

void imprimirCadena(void *a);
void liberarCadena(void *a);
void menu();

int main(void)
{	
	
	// {INICIO NULO, SIN LIMITE, CANTIDAD 0, COMO IMPRIMIR, COMO LIBERAR}
	Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	
	//Pila pilaUno = {NULL,-1,0,&imprimirCadena,&liberarCadena};

	int option, palindromo, valido, cant, auxiliar, auxDos;
	int cantObj, objEv;
	char cad[100];
	char aux;
	char *ap = NULL;
	
	do
	{
		menu();
		inputEntero("\n Ingrese su opcion: ", &option);
		
		switch(option)
		{
			case 1:
			//PALINDROMO
				palindromo = 1;
				inputCadena("\n Ingrese cadena: ", cad, 100);

				printf("\n CADENA INGRESADA: %s", cad);


				for(int i = 0; cad[i] != '\0'; i++)
				{
					
					if(cad[i] >= 'A' && cad[i] <= 'Z')
					{
						cad[i] += 32;
					}
					if(cad[i] != ' ')
					{
						aux = cad[i];
						ap = cadenaDinamica(&aux);
						push(&pila, ap);
					}
				}
				//imprimirPila(pila);
				//VALIDAMOS SI ES PALINDROMO
				for(int i = 0; cad[i] != '\0'; i++)
				{
					if(vacia(pila))
					{
						break;
					}
					//printf("\n do");
					if(cad[i] != ' ')
					{
						ap = pop(&pila);
						if(cad[i] != *ap && cad[i] != ' ')
						{
							palindromo = 0;
						}
					}
					
				}
				if(palindromo == 1)
				{
					printf("\n Es palindromo");
				}
				else
				{
					printf("\n No es palindromo");
				}

				imprimirPila(pila);

				break;
			case 2:
			//VERIFICACION
				//Implementar un programa que valide una cadena de caracteres que contiene paréntesis, 
					// llaves y corchetes: “( )”, “{ }”, “[ ]” respectivamente
						//() “(x){y}[z] “([x]) → Válido
							//“(x]” → Inválido
				//cantObj, objEv
				cantObj = 0;
				objEv = 0;
				//LIMPIAR PILA
				while(!vacia(pila))
				{
					ap = pop(&pila);
				}
				valido = 1;
				cant = 0;
				auxiliar = 0;
				auxDos = 0;
				inputCadena("\n Ingrese cadena: ", cad, 100);
				printf("\n CADENA INGRESADA: %s", cad);

				for(int i = 0; cad[i] != '\0'; i++)
				{
					if(cad[i] == '(' || cad[i] == '{' || cad[i] == '[' || cad[i] == ')' || cad[i] == '}' || cad[i] == ']')
					{
						cantObj++;
					}
					
				}

				for(int i = 0; cad[i] != '\0'; i++)
				{
					
					if(cad[i] == '(' || cad[i] == '{' || cad[i] == '[')
					{
						objEv++;
						auxDos = 1; //significa quye la cadena no esta compuesta solo de letras
						aux = cad[i];
						ap = cadenaDinamica(&aux);
						push(&pila, ap);
					}
					if(cad[i] == ')' || cad[i] == '}' || cad[i] == ']')
					{
						auxDos = 1;
						if(vacia(pila))
						{
							valido = 0;
							break;
						}
						objEv++;
						auxiliar = 1;
						ap = pop(&pila);
						cant++;
						//printf("\n %c -- %c",*ap, cad[i]);
						if(*ap == '(')
						{
							if(cad[i] != *ap + 1)
							{
								valido = 0;
							}
						}
						else if(*ap == '[' || *ap == '{')
						{
							if(cad[i] != *ap + 2)
							{
								valido = 0;
							}
						}
						
					}
				}
				if(!vacia(pila))
				{
					valido = 0;
				}

				if(valido == 1)
				{
					
					if((cant == 1 && auxiliar == 0) || (cant == 0 && auxiliar == 0 && auxDos == 1))
					{
						printf("\n No es valido");
					}
					else if(cant == 0 && auxDos == 0)
					{
						printf("\n Nada por validar");
					}
					else
					{
						printf("\n Es valido");
					}
				
				}
				else
				{
					printf("\n No es valido");
				}
				
			
				break;
			case 3:
				break;
			default:
				break;
		}
		
	}while(option != 3);

	
	//imprimirPila(pila);
	printf("\n\n FIN DE PROGRAMA");
	//free(cad);
	eliminarPila(&pila);
	return 0;
}

void menu()
{
	printf("\n [1] Palindromo");
	printf("\n [2] Verificacion de parentesis");
	printf("\n [3] Terminar ejecucion");
	
}

void imprimirCadena(void *a)
{
	char *aa = a;
	printf("%s",aa);
	
}

void liberarCadena(void *a)
{
	char *aa = a;
	free(aa);
}