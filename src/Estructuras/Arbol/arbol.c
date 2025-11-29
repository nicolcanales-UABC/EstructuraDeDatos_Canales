
#include "arbol.h"

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
{
	if(comparar(dato,raiz->dato)<=0)
	{
		//IZQUIERDA
		if(raiz->izq)
			insertarArbolOrdenado(raiz->izq,dato,comparar);
		else
			raiz->izq = crearNodoA(dato);
	}
	else
	{
		//DERECHA
		if(raiz->dch)
			insertarArbolOrdenado(raiz->dch,dato,comparar);
		else
			raiz->dch = crearNodoA(dato);
	}
}

void insertarArbol(Arbol *arbol,void *dato)
{
	if(!arbol->raiz)
		arbol->raiz = crearNodoA(dato);
	else 
		insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
	arbol->cantidad++;
}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

int comparar_arbol(NodoA* nodoA, NodoA* nodoB, int nivel,int (*comparar)(void*,void*))
{
	//MODIFICAR
    int i = 1;
	if(comparar(nodoA->dato,nodoB->dato) != 0)
	{
		return 0;
	}
    if (nodoA != NULL && nodoB != NULL)
    {
        if(nodoA->dch && nodoB->dch)
        {
			if(comparar(nodoA->dch->dato, nodoB->dch->dato) == 0)
			{
				i = comparar_arbol(nodoA->dch, nodoB->dch, nivel + 1,comparar);
				if(i == 0)
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
            
        }
		if(nodoA->dch == NULL && nodoB->dch != NULL)
		{
			return 0;
		}
		if(nodoA->dch != NULL && nodoB->dch == NULL)
		{
			return 0;
		}
        if(nodoA->izq && nodoB->izq)
        {

			if(comparar(nodoA->izq->dato, nodoB->izq->dato) == 0)
			{
				i = comparar_arbol(nodoA->izq, nodoB->izq, nivel + 1,comparar);
				if(i == 0)
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
        
        }
		if(nodoA->izq == NULL && nodoB->izq != NULL)
		{
			return 0;
		}
		if(nodoA->izq != NULL && nodoB->izq == NULL)
		{
			return 0;
		}
    }
	return i;
}

void compararArbol(Arbol arbolA, Arbol arbolB)
{
	if(arbolA.cantidad != arbolB.cantidad)
	{
		printf("\n Arboles diferentes - ERROR ESTRUCTURA Y DATOS");
		return;
	}
	int aux;
	//¿QUÉ REGRESE UN NUMERO?
	aux = comparar_arbol(arbolA.raiz,arbolB.raiz,0,arbolA.comparar);
	if(aux != 0)
	{
		printf("\n Arboles identicos");
	}
	else
	{
		int cantidadA = arbolA.cantidad;
		int cantidadB = arbolB.cantidad;
		void **datosA = calloc(cantidadA,sizeof(void*));
		void **datosB = calloc(cantidadB,sizeof(void*));
		int indiceA = 0;
		int indiceB = 0;
		//int auxA, auxB;
		extraccionDatos(arbolA.raiz,datosA,&indiceA);
		extraccionDatos(arbolB.raiz,datosB,&indiceB);

		//int arregloA[indiceA];
		//int arregloB[indiceB];

		//ORDENAMOS ARREGLOS
		
		//auxA = *(int*)datosA[0];
		//auxB = *(int*)datosB[0];
		printf("\n ARREGLO ARBOL A y B: ");
		for(int i = 0; i <indiceA; i++)
		{
			//arregloA[i] = *(int*)datosA[i];
			//arregloB[i] = *(int*)datosB[i];
			//if(arregloA[i] != arregloB[i])
			//{
			//	printf("\n Arboles diferentes - ERROR ESTRUCTURA Y DATOS");
			//0	return;
			//}
		}

		//REALIZAR COMPARACION DE DATOS

		printf("\n Arboles diferentes - ERROR ESTRUCTURA / DATOS IGGUALES");

	}
}

void eliminarDato(Arbol *arbol, int dato)
{
	NodoA *aux = NULL;
	//Arbol* busqueda(Arbol *arbol, int dato)
	//aux = busqueda_Dato(arbol, dato);

	if(aux == NULL)
	{
		printf("\n Dato no encontrado");
		return;
	}
	//ELIMINAR DATO Y REACOMODAR

}
//eliminarNodo2(Resultado *res, Arbol *arbol);


void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

void calcularAltura(NodoA *raiz,int *altura)
{
	int izquierdo,derecho;
	izquierdo = derecho = *altura;
	if(raiz->izq && izquierdo++ )
		calcularAltura(raiz->izq,&izquierdo);
	if(raiz->dch && derecho++ )
		calcularAltura(raiz->dch,&derecho); 
	*altura = (izquierdo>derecho) ? izquierdo:derecho;
}

int altura(Arbol arbol)
{
	if(!arbol.raiz)
		return 0;
	int altura = 1;
	calcularAltura(arbol.raiz,&altura);
	return altura;
}

void extraccionDatos(NodoA *raiz,void **datos,int *indice)
{
	if(!raiz)
		return;
	extraccionDatos(raiz->izq,datos,indice);
	datos[*indice] = raiz->dato;
	(*indice)++;
	extraccionDatos(raiz->dch,datos,indice);
}

void equilibrar(Arbol *arbol)
{
	void (*liberar)(void*) = arbol->liberar;
	arbol->liberar = NULL;
	int indice = 0;
	int cantidad = arbol->cantidad;
	int *indices = calloc(cantidad,sizeof(int));
	void **datos = calloc(cantidad,sizeof(void*));


	extraccionDatos(arbol->raiz,datos,&indice);
	
	eliminarArbol(arbol);
	arbol->liberar = liberar;
	insertarBalanceado(arbol, datos, 0, cantidad - 1);
	//ARBOL VACIO
	//DATOS EN EL ARREGLO
	//HACER INSERCIONES EN EL ARBOL PARA QUE 
	//QUEDE EQUILIBRARDO	
	
	//SACAR INDICES Y COLOCARLOS EN EL ARREGLO DE INDICES
	
	free(datos);
	free(indices);
}
void eliminar_NodosA(NodoA *raiz, void (*liberar)(void *))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq, liberar);
	eliminar_NodosA(raiz->dch, liberar);
	//LIBERAR
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
}

void eliminarArbol(Arbol *arbol)
{
	eliminar_NodosA(arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

void liberarInt(void *dato)
{
    free(dato);
}
void insertarBalanceado(Arbol *arbol, void **datos, int inicio, int fin) {
    if (inicio > fin)
        return;
    int mitad = (inicio + fin) / 2;
    insertarArbol(arbol, datos[mitad]);
    insertarBalanceado(arbol, datos, inicio, mitad - 1);
    insertarBalanceado(arbol, datos, mitad + 1, fin);
	
}


int libroExisteEnArbol(Arbol *arbol, const char *isbn) {
    if (!arbol || !arbol->raiz) return 0;
    
    return buscarPorISBN(arbol->raiz, isbn) != NULL;
}
NodoA* buscarPorISBN(NodoA* nodo, const char* isbn)
{
      if (!nodo) return NULL;
         Libro *lib = (Libro*)nodo->dato;
      if (strcmp(lib->isbn, isbn) == 0) return nodo;
           NodoA* izq = buscarPorISBN(nodo->izq, isbn);
      if (izq) return izq;
         return buscarPorISBN(nodo->dch, isbn);
}


void ordenDos(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	ordenDos(raiz->izq,imprimir);
	printf("\n");
	imprimir(raiz->dato);
	printf("\n");
	ordenDos(raiz->dch,imprimir);	
}
void imprimirOrdenDos(Arbol arbol)
{
	ordenDos(arbol.raiz,arbol.imprimir);
}
int buscarEnArbol2(Arbol *arbol, void *dato,int (*comparar)(void*,void*))
{
    NodoA *actual = arbol->raiz;

    while (actual != NULL)
    {
        int cmp = comparar(dato, actual->dato);

        if (cmp == 0)
            return 1;  // encontrado

        else if (cmp < 0)
            actual = actual->izq;

        else
            actual = actual->dch;
    }

    return 0; // no encontrado
}
