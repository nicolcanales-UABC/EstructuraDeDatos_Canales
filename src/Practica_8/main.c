#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#include "../Captura/captura.h"
#include "../Estructuras/Pila/pila.h"
#include "../Estructuras/Cola/cola.h"
#include "../Estructuras/Arbol/arbol.h"

typedef struct
{
    char caracter;
    float *valor;
} Dato;

void** ingresaInicio(Pila *pila);
void postfixCola(void** datos, Cola* cola);
void postfixArbol(Cola* cola, Arbol* arbol, Pila *pila);
int esOperador(char caracter);
void imprimirDatoArbol(void *dato);
void liberarDato(void *dato); 
void capturarValores(NodoA* raiz, char *letras, float *valores, int *n);
float evaluarArbol(NodoA* raiz);
float realizarCalculo(float a, float b, char op);
Dato* crearDato(char caracter);

int main(void){

    Pila pila;
    inicializarPila(&pila); 
    Cola cola = inicializarCola();
    Arbol arbol;

    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = imprimirDatoArbol; 
    arbol.comparar = NULL; 
    arbol.liberar = liberarDato; 

    int option;

    do {
        printf("\n [0] CAPTURAR EXPRESION \n [1] IMPRIMIR ARBOL DE EXPRESION");
		printf("\n [2] EVALUAR EXPRESION \n [3] TERMINAR PROGRAMA");
        inputEntero("\n Selecciona opcion: ",&option);

        switch(option){
            case 0:
            {
                    //CAPTURAR EXPRESIÓN
                // REINICIO
                eliminarPila(&pila);
                inicializarPila(&pila);
                eliminarCola(&cola);
                cola = inicializarCola();
                eliminarArbol(&arbol); 

                // INICIALIZAR
                arbol.raiz = NULL;
                arbol.cantidad = 0;
                arbol.imprimir = imprimirDatoArbol;
                arbol.comparar = NULL;
                arbol.liberar = liberarDato; 

                void **postfix = ingresaInicio(&pila);
                
                if (postfix != NULL) {
                    printf("\n Postfix: ");
                    for(int i=0; postfix[i] != NULL; i++) {
                        printf("%c ", ((Dato*)postfix[i])->caracter);
                    }
                    printf("\n");

                    postfixCola(postfix, &cola);
                    postfixArbol(&cola, &arbol, &pila);
                    printf("\n ARBOL CONSTRUIDO.\n");
                    
                    free(postfix); // El arreglo de punteros ya no se necesita
                }
                break;
            }
            case 1:
                    //IMPRIMIR ARBOL DE EXPRESION
                imprimirArbol(arbol);
    
                break;
            case 2:
            {
                char letras[50];
                float valores[50];
                int n = 0;

                capturarValores(arbol.raiz, letras, valores, &n);

                printf("\n Valores capturados");
                    float resultado = evaluarArbol(arbol.raiz);
                printf(" \n RESULTADO: %.2f \n", resultado);
            }
                break;
            case 3:
                
                break;
            default:
                printf("\n NO");
                break;
        }
    } while(option != 3);

    eliminarPila(&pila);
    eliminarCola(&cola);
    eliminarArbol(&arbol); 
    
    return 0;
}


Dato* crearDato(char caracter){
    Dato *nuevo = (Dato*)calloc(1, sizeof(Dato));
    if (nuevo) {
        nuevo->caracter = caracter;
        nuevo->valor = NULL;
    }
    return nuevo;
}


void imprimirDatoArbol(void *dato) {
    Dato *info = (Dato*)dato;
    if (info) {
        printf("%c", info->caracter);
    }
}

void liberarDato(void *dato) {
    if (dato) {
        Dato *info = (Dato*)dato;
        if (info->valor) {
            free(info->valor);
        }
        free(info);
    }
}

void** ingresaInicio(Pila *pila){
    void** salida = calloc(50, sizeof(void*)); 
    char mensaje[50];
    
    inputCadena("\n Ingrese expresion: ", mensaje, 50);

    int i = 0;
    int pos = 0;
    while(mensaje[i] != '\0'){
        char a = mensaje[i];

        if((a >= 'A' && a<= 'Z') || (a >= 'a' && a<= 'z')){
            salida[pos++] = crearDato(a); 
        } else if(a == '('){
            Dato* dato_parentesis = crearDato(a);
            Nodo *nuevo = crearNodo(dato_parentesis); 
            push_nodo(pila, nuevo);
        } else if(esOperador(a)){
            while(!vacia(*pila) && ((Dato*)peek_nodo(*pila))->caracter != '(' &&
                  prioridad(((Dato*)peek_nodo(*pila))->caracter) >= prioridad(a)){ 
                Nodo *sacado = pop_nodo(pila);
                salida[pos++] = (Dato*)sacado->dato; 
                free(sacado); 
            }
            Dato* dato_operador = crearDato(a);
            Nodo *nuevo = crearNodo(dato_operador); 
            push_nodo(pila, nuevo); 
        } else if(a == ')'){
            while(!vacia(*pila) && ((Dato*)peek_nodo(*pila))->caracter != '('){
                Nodo *sacado = pop_nodo(pila); 
                salida[pos++] = (Dato*)sacado->dato; 
                free(sacado); 
            }
            if(vacia(*pila)){
                printf("\n EXPRESION NO VALIDA");
                for(int j = 0; j < pos; j++) liberarDato(salida[j]); 
                free(salida); 
                eliminarPila(pila); 
                return NULL;
            }
           
            Nodo *sacado = pop_nodo(pila); 
            liberarDato(sacado->dato); 
            free(sacado); 
        }
        i++;
    }

    while (!vacia(*pila)) {
        if (((Dato*)peek_nodo(*pila))->caracter == '('){ 
            printf("\n EXPRESION NO VALIDA");
            for (int j = 0; j < pos; j++) liberarDato(salida[j]); 
            free(salida); 
            eliminarPila(pila);
            return NULL; 
        }
        Nodo *extraido = pop_nodo(pila); 
        salida[pos++] = extraido->dato;
        free(extraido);
    }
    return salida;
}

int esOperador(char caracter){
    char *operadores = "+-*/^";
    for(int i=0; operadores[i]!='\0'; i++){
        if(caracter == operadores[i])
            return 1;
    }
    return 0;
}

void postfixCola(void** datos, Cola* cola){
    for(int i = 0; i < 50; i++){
        if(datos[i] == NULL) 
            break; 
        NodoA *nuevo = crearNodoA(datos[i]); 
        enqueue(cola, nuevo); 
    }
}


void postfixArbol(Cola* cola, Arbol* arbol, Pila *pila){

    
    while(!vaciaC(*cola)){
        NodoA* nodo  = (NodoA*)peekC(*cola);
        Dato* dato_info = (Dato*)nodo->dato;
        char a = dato_info->caracter;

        if((a >= 'a' && a <='z') || (a >= 'A' && a <='Z')){
            NodoA* nodo_operando = (NodoA*)dequeue(cola);
            push_nodo(pila, crearNodo(nodo_operando)); 
        } else if(esOperador(a)){
            NodoA *raiz = (NodoA*)dequeue(cola);
            Nodo* nodo_dch = pop_nodo(pila);
            NodoA* hijo_derecho = (NodoA*)(nodo_dch->dato); 
            free(nodo_dch); 

            Nodo* nodo_izq = pop_nodo(pila);
            NodoA* hijo_izquierdo = (NodoA*)(nodo_izq->dato);
            free(nodo_izq);

            raiz->dch = hijo_derecho;
            raiz->izq = hijo_izquierdo;
            push_nodo(pila, crearNodo(raiz));
        }
    }
    
    Nodo* nodo = pop_nodo(pila);
    arbol->raiz = (NodoA*)(nodo->dato);
    free(nodo);
}

float realizarCalculo(float a, float b, char op) {
    float resultado;

    switch(op) {
        case '+':
            resultado = a + b;
            break;
        case '-':
            resultado = a - b; 
            break;
        case '*':
            resultado = a * b;
            break;
        case '/': 
            if (b == 0) {
                resultado = 0; 
            } else {
                resultado = a / b;
            }
            break;
        case '^':
            resultado = pow(a, b);
            break;
        default:
            resultado = 0;
            break;
    }

    return resultado;
}


float evaluarArbol(NodoA* raiz) {
    if (raiz == NULL)
        return 0;
    Dato* info = (Dato*)raiz->dato; 

    if (!esOperador(info->caracter)) { 
        if (info->valor != NULL) {
            return *(info->valor); 
        } else {
            return 0;
        }
    }


    float val_izq = evaluarArbol(raiz->izq);
    float val_dch = evaluarArbol(raiz->dch);

    return realizarCalculo(val_izq, val_dch, info->caracter);
}


void capturarValores(NodoA* raiz, char *letras, float *valores, int *n) {
    if (raiz == NULL)
        return;

    capturarValores(raiz->izq, letras, valores, n);

    Dato* info = (Dato*)raiz->dato;
    if (!esOperador(info->caracter)) {
        int i;
        int existe = 0;

        // Verifica si ya se pidió esta letra
        for (i = 0; i < *n; i++) {
            if (letras[i] == info->caracter) {
                info->valor = &valores[i];
                existe = 1;
                break;
            }
        }

        // Si no existe, se pide una vez
        if (!existe) {
            letras[*n] = info->caracter;
            printf("Ingresa valor para %c: ", info->caracter);
            inputFloat("", &valores[*n]);
            info->valor = &valores[*n];
            (*n)++;
        }
    }

 
    capturarValores(raiz->dch, letras, valores, n);
}
