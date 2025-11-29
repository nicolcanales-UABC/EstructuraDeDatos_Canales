
#include <stdio.h>
#include "../Estructuras/Pila/pila.h"
#include "../Captura/captura.h"

#define LONGITUD 64

void imprimirCadena(void *a);
void liberarCadena(void *a);
int verificarParentesis(char cad[100], Pila *pila);

int main(void)
{
	int option, aux_ver;
	
	char cad[100];
	
	char *ap = NULL;

	Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};

	do
	{
		printf("\n [1] Infix a Postfix \n [2] Finalizar programa");
		inputEntero("\n Selecciona opcion: ",&option);

		if(option == 1)
		{
			//INFIX A POSTFIX
				//PEDIR CADENA
				
				//LIMPIAR PILA
			while(!vacia(pila))
			{
				//ap = pop(&pila);
				pop(&pila);
			}
			
			inputCadena("\n Ingrese cadena: ", cad, 100);
			printf("\n CADENA INGRESADA: %s", cad);
				
				//VERIFICAR PARENTESIS
			aux_ver = verificarParentesis(&cad[0], &pila);
			while(!vacia(pila))
			{
				//ap = pop(&pila);
				pop(&pila);

			}
			if(aux_ver == 0)
			{
				printf("\n ERROR");
			}
			else
			{
				//COMENZAR PROCESO DE INFIX A POSTFIX
				char cad_res[100];
				char aux, auxDos;
				char *operadores = "+-*/^";
				int index = 0;
				int stop;

				for(int i = 0;  cad[i] != '\0'; i++)
				{	
					aux_ver = 0;
					stop = 0;
					aux = cad[i];
					for(int j = 0; operadores[j] != '\0';j++)
					{
						if(aux == operadores[j])
						{
							aux_ver = 1;
							break;
						}
					}
					if(aux_ver == 0)
					{
						if(aux == '(')
						{
							ap = cadenaDinamica(&aux);
							push(&pila, ap);
						}
						else if(aux == ')')
						{
							do
							{
								auxDos = *(char*)pop(&pila);
								if(auxDos != '(')
								{
									cad_res[index] = auxDos;
									index++;
								}
								
							}while(auxDos != '(');
						}
						else
						{
							cad_res[index] = aux;
							index++;
						}
						
					}
					else
					{
						//INCIA INSERCION Y POP DE LA PILA
						if(vacia(pila))
						{
							ap = cadenaDinamica(&aux);
							push(&pila, ap);
						}
						else
						{
							if(aux == '+' || aux == '-')
							{
								//auxDos = peak(&pila);
								while(!vacia(pila))
								{
									auxDos = *(char*)peek(&pila);
									if(auxDos != '(')
									{
										auxDos = *(char*)pop(&pila);
										cad_res[index] = auxDos;
										index++;
									}
									else
									{
										break;
									}
								}
								ap = cadenaDinamica(&aux);
								push(&pila, ap);
							}
							else if(aux == '*' || aux == '/')
							{
								do
								{
									auxDos = *(char*)peek(&pila);
									if(auxDos == '^')
									{
										auxDos = *(char*)pop(&pila);
										cad_res[index] = auxDos;
										index++;
									}
									else if(auxDos == '*' || auxDos == '/')
									{
										auxDos = *(char*)pop(&pila);
										cad_res[index] = auxDos;
										index++;
									}
									else if(auxDos == '(')
									{
										stop = 1;
									}
									else if(auxDos == '+' || auxDos == '-')
									{
										stop = 1;
									}
									if(vacia(pila))
									{
										stop = 1;
									}

								}while(stop == 0);
								
								ap = cadenaDinamica(&aux);
								push(&pila, ap);
							}
							else if(aux == '^')
							{
								ap = cadenaDinamica(&aux);
								push(&pila, ap);
							}

						}
					}
					
				}

				while(!vacia(pila))
				{
					auxDos = *(char*)pop(&pila);
					cad_res[index] = auxDos;
					index++;
				}
				cad_res[index] = '\0';
				printf("\n RESULTADO: %s", cad_res);

			}
		}

	}while(option != 2);
	

	return 0;
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

int verificarParentesis(char cad[100], Pila *pila)
{
	int cantObj, objEv,valido, cant, auxiliar, auxDos;
	char aux;
	char *ap = NULL;
		//INICIALIZAR BANDERAS
	cantObj = 0;
	objEv = 0;
	valido = 1;
	cant = 0;
	auxiliar = 0;
	auxDos = 0;

	
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
			push(pila, ap);
		}
		if(cad[i] == ')' || cad[i] == '}' || cad[i] == ']')
		{
			auxDos = 1;
			if(vacia(*pila))
			{
				valido = 0;
				break;
			}
			objEv++;
			auxiliar = 1;
			ap = pop(pila);
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
	if(!vacia(*pila))
	{
		valido = 0;
		return 0;
	}

	if(valido == 1)
	{
					
		if((cant == 1 && auxiliar == 0) || (cant == 0 && auxiliar == 0 && auxDos == 1))
		{
			printf("\n No es valido");
			return 0;
		}
		else if(cant == 0 && auxDos == 0)
		{
			printf("\n Nada por validar");
			return 2;
		}
		else
		{
			printf("\n Es valido");
			return 1;
		}
				
	}
	else
	{
		printf("\n No es valido");
		return 0;
	}
}