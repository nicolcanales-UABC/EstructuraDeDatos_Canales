#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Captura/captura.h"
#include "../Estructuras/Hash/hashtable.h"

#include "Libro.h"

int main(void)
{
    Libro *libros;
    libros = obtener_libros();
    int option,auxEntero;
    char *auxCad;
    char cadISBN[MAX_ISBN];
    char cadTITULO[MAX_TITULO];
    char cadAUTOR[MAX_AUTOR];
    char auxMin, auxMax;
    Libro auxL;
    Libro *apL;

        //ARBOLES

    Arbol arbolISBN = {NULL,0,imprimirLibro,compararISBN,NULL};
    //Arbol arbolTITULO = {NULL,0,imprimirLibro,compararTITULO,NULL};
    //Arbol arbolAUTOR = {NULL,0,imprimirLibro,compararAUTOR,NULL};
    Arbol arbolFECHA = {NULL,0,imprimirLibro,compararDATE,NULL};

        //TABLAS HASH
    HashTable tablaISBN = inicializarHashTable(CANT_LIBROS,imprimirLibro,compararISBN, foldingISBN);
    HashTable tablaTITULO = inicializarHashTable(CANT_LIBROS,imprimirLibro,compararTITULO, foldingTITULO);
    HashTable tablaAUTOR = inicializarHashTable(CANT_LIBROS,imprimirLibro, compararAUTOR, foldingAUTOR);
    HashTable tablaDATE = inicializarHashTable(CANT_LIBROS,imprimirLibro,compararDATE, foldingDATE);
    //HashTable buscarRangoTitulo = inicializarHashTable(CANT_LIBROS,imprimirLibro,compararAUTOR, foldingDATE);

    for(int i = 0; i<CANT_LIBROS;i++)
    {
        insertarClave(&tablaISBN,&libros[i]);
        insertarClave(&tablaTITULO,&libros[i]);
        insertarClave(&tablaAUTOR,&libros[i]);
        insertarClave(&tablaDATE,&libros[i]);
    }

    do
    {
        printf("\n                   GOOGLE ACADEMICS                   \n");
        printf("\n ---------------------------------------------------- \n");
        printf("\n BUSCADOR: ");
        printf("\n - [1] ISBN \n - [2] TITULO  \n - [3] AUTOR \n - [4] FECHA ");
        printf("\n - [5] AGREGAR LIBRO \n - [6] ELIMINAR LIBRO ");
        //\n - [7] AUTOR
        printf(" \n [0] FINALIZAR BUSQUEDA");
        //agregar opcion
        inputEntero("\n Selecciona opcion: ",&option);


        switch(option)
        {
            case 1:
            //ISBN
                //ELIMINAR LIBRO POR ISBN
                auxL = (Libro){0};
                inputCadena("\n Ingrese ISBN: ", cadISBN, MAX_ISBN);
                auxCad = cadenaDinamica(cadISBN);
                //inputCadenaDinamica("\n Ingrese ISBN: ", &auxCad, MAX_ISBN);
                //printf("\n %s", cadISBN);
                strncpy(auxL.isbn, auxCad, sizeof(auxL.isbn) - 1);
                //auxL.isbn = cadISBN;
                //arbolISBN = buscarClave(&tablaISBN,&cadISBN,imprimirLibro,compararISBN);
                arbolISBN = buscarClave(&tablaISBN,&auxL,imprimirLibro,compararISBN);
                //printf("AQUI MUERE ");
                //imprimirArbol(arbolISBN);
                imprimirOrdenDos(arbolISBN);

                break;
            case 2:
            //TITULO
                auxL = (Libro){0};
                printf("\n ---------------------------------------------------- \n");
                printf("\n BUSCADOR: ");
                printf("\n - [1] Titulo \n - [2] Rango");
                
                inputEntero("\n Selecciona opcion: ",&option);
                if(option == 1)
                {
                    //BUSCAR Y DESPLEGAR INFORMACIÓN DEL LIBRO
                    inputCadena("\n Ingrese Titulo: ", cadTITULO, MAX_TITULO);
                    auxCad = cadenaDinamica(cadTITULO);
                    //inputCadenaDinamica("\n Ingrese Titulo: ", &auxCad, MAX_TITULO);
                    //strncpy(auxL.titulo, cadTITULO, sizeof(auxL.titulo) - 1);
                    strncpy(auxL.titulo, auxCad, sizeof(auxL.titulo) - 1);
                    arbolISBN = buscarClave(&tablaTITULO,&auxL,imprimirLibro,compararTITULO);
                    imprimirOrdenDos(arbolISBN);
                }
                else if(option == 2)
                {
                    //BUSCAR Y DESPLEGAR INFORMACIÓN DE LOS LIBROS
                    
                    inputChar("\n Ingresa primer caracter: ", &auxMin);
                    inputChar("\n Ingresa segundo caracter: ", &auxMax);
                    if(auxMin >= 'A' && auxMin <= 'Z')
                        auxMin = auxMin + 32;
                    if(auxMax >= 'A' && auxMax <= 'Z')
                        auxMax = auxMax + 32;
                    arbolISBN = buscarRangoTitulo(&tablaTITULO,auxMin,auxMax,imprimirLibro,compararTITULO);
                    imprimirOrdenDos(arbolISBN);
                }

                break;
            case 3:
            //AUTOR
                printf("\n ---------------------------------------------------- \n");
                printf("\n BUSCADOR: ");
                printf("\n - [1] Autor \n - [2] Rango");
                auxL = (Libro){0};
                inputEntero("\n Selecciona opcion: ",&option);
                if(option == 1)
                {
                    //BUSCAR Y DESPLEGAR LIBROS DEL AUTOR
                    //BUSCAR Y DESPLEGAR INFORMACIÓN DEL LIBRO
                    inputCadena("\n Ingrese AUTOR: ", cadAUTOR, MAX_AUTOR);
                    auxCad = cadenaDinamica(cadAUTOR);
                    //inputCadenaDinamica("\n Ingrese AUTOR: ", &auxCad, MAX_AUTOR);
                    strncpy(auxL.autor, auxCad, sizeof(auxL.autor) - 1);
                    arbolISBN = buscarClave(&tablaAUTOR,&auxL,imprimirLibro,compararAUTOR_LC);
                    imprimirOrdenDos(arbolISBN);
                }
                else if(option == 2)
                {
                    //BUSCAR Y DESPLEGAR LIBROS DE LOS AUTORES
                    inputChar("\n Ingresa primer caracter: ", &auxMin);
                    inputChar("\n Ingresa segundo caracter: ", &auxMax);
                    if(auxMin >= 'A' && auxMin <= 'Z')
                        auxMin = auxMin + 32;
                    if(auxMax >= 'A' && auxMax <= 'Z')
                        auxMax = auxMax + 32;
                    arbolISBN = buscarRangoAutor(&tablaAUTOR,auxMin,auxMax,imprimirLibro,compararAUTOR);
                    imprimirOrdenDos(arbolISBN);
                    
                }
                break;
            case 4:
            //FECHA
                printf("\n ---------------------------------------------------- \n");
                printf("\n BUSCADOR: ");
                printf("\n - [1] Fecha \n - [2] Rango");
                auxL = (Libro){0};
                inputEntero("\n Selecciona opcion: ",&option);
                if(option == 1)
                {
                    inputEntero("\n Ingrese fecha del libro: ", &auxEntero);
                    auxL.fecha = auxEntero;
                    arbolFECHA = buscarClave(&tablaDATE,&auxL,imprimirLibro,compararDATE_LC);
                    imprimirOrdenDos(arbolFECHA);
                }
                else if(option == 2)
                {
                    //BUSCAR Y DESPLEGAR LIBROS PERTENECIENTES AL RANGO DE AÑOS
                    int intMIN, intMAX;
                    //BUSCAR Y DESPLEGAR LIBROS PERTENECIENTES AL AÑO
                    inputEntero("\n Ingrese fecha minima: ", &intMIN);
                    inputEntero("\n Ingrese fecha maxima: ", &intMAX);
                    arbolFECHA = buscarRangoFecha(&tablaDATE,intMIN,intMAX,imprimirLibro,compararDATE);
                    imprimirOrdenDos(arbolFECHA);
                }
                break;
            case 5:
            //IMPRIMIR LIBROS SIN LOS ESPACIOS VACÍOS

            //AGREGAR LIBRO
                apL = malloc(sizeof(Libro));
                inputCadena("\n Ingrese ISBN: ", apL->isbn, MAX_ISBN);
                
                inputCadena("\n Ingrese titulo: ", apL->titulo, MAX_TITULO);

                inputCadena("\n Ingrese Autor: ", apL->autor, MAX_AUTOR);

                inputEntero("\n Ingrese year: ", &auxEntero);
                apL->fecha = auxEntero;
                apL->disponible = 1;

                insertarClave(&tablaISBN, apL);
                insertarClave(&tablaTITULO, apL);
                insertarClave(&tablaAUTOR, apL);
                insertarClave(&tablaDATE, apL);

                break;
            case 6:
                auxL = (Libro){0};
                inputCadena("\n Ingrese ISBN del libro a eliminar: ", cadISBN, MAX_ISBN);
                auxCad = cadenaDinamica(cadISBN);
                
                // Buscar primero para confirmar que existe
                Libro libroBuscar = {0};
                strncpy(libroBuscar.isbn, auxCad, sizeof(libroBuscar.isbn) - 1);
                Arbol resultado = buscarClave(&tablaISBN, &libroBuscar, imprimirLibro, compararISBN);
                
                if (resultado.raiz != NULL) {
                    Libro *libroReal = (Libro*)resultado.raiz->dato;
                    printf("\n Eliminando: %s", libroReal->titulo);
                    
                    // Eliminar por ISBN de todas las tablas
                    eliminarLibroPorISBN(&tablaISBN, auxCad, NULL);
                    eliminarLibroPorISBN(&tablaTITULO, auxCad, NULL);
                    eliminarLibroPorISBN(&tablaAUTOR, auxCad, NULL);
                    eliminarLibroPorISBN(&tablaDATE, auxCad, NULL);
                    
                    printf("\n Libro eliminado exitosamente");
                } else {
                    printf("\n Libro no encontrado");
                }
                
                free(auxCad);
                auxCad = NULL;
                break;
                break;
            case 7:
                for(int i = 0 ; i < tablaISBN.cant ; i++)
                {
                    printf("\n ");
                    if(tablaISBN.tabla[i] != NULL)
                        imprimirLibro(&tablaISBN.tabla[i]);
                    //tablaISBN.tabla[i];
                    //AGREGAR A TABLAS
                    //TABLA ISBN
                    //TABLA TITULO
                    //TABLA INICIAL TITULO
                    //TABLA AUTOR		
                    //TABLA AUTOR TITULO
                    //TABLA FECHAS
                }
                break;
            default:
                break;
        }
    }while(option != 0);
    

	//VARIABLE PARA MANEJAR INDICES
  
	//PUNTERO QUE ALMACENA LA REFERENCIA DEL INICIO DE LOS DATOS
    
    
    
	
	//MENU DE BUSQUEDAS
	
	
    printf("\n\n FIN DE PROGRAMA \n");
    return 0;
}

