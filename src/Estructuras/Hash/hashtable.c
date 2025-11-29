#include "hashtable.h"

int folding(char *cadena)
{
	int clave, seg, j, n;

	clave = seg = j = 0;
	n = 1;

	for(int i = 0; cadena[i] != '\0'; i++)
	{
		if(j == 3)
		{
			j = 0;
			clave += seg*n;
			n++;
			seg = 0;
		}
		seg += cadena[i];
		j++;
	}
	if(j != 0)
	{
		clave += seg*n;
	}	
	return clave;
}

int foldingISBN(void *dato)
{
	Libro *aux = (Libro*) dato;
	return folding(aux->isbn);
}
int foldingTITULO(void *dato)
{
	Libro *aux = (Libro*) dato;
	return folding(aux->titulo);
}
int foldingAUTOR(void *dato)
{
	Libro *aux = (Libro*) dato;
	return folding(aux->autor);
}
int foldingDATE(void *dato)
{
	Libro *aux = (Libro*) dato;
	return aux->fecha;
}


int compararISBN(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	Libro *bb = (Libro*) b;

	if(folding(aa->isbn) == folding(bb->isbn))
	{
		return 0;
	}
	else if(folding(aa->isbn) < folding(bb->isbn))
	{
		return -1;
	}
	else
	{
		return 1;
	}

}
int compararISBN_LC(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	char *bb = (char*) b;

	if(folding(aa->isbn) == folding(bb))
	{
		return 0;
	}
	else if(folding(aa->isbn) < folding(bb))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int compararTITULO(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	Libro *bb = (Libro*) b;

	if(folding(aa->titulo) == folding(bb->titulo))
	{
		return 0;
	}
	else if(folding(aa->titulo) < folding(bb->titulo))
	{
		return -1;
	}
	else
	{
		return 1;
	}

}
int compararTITULO_LC(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	char *bb = (char*) b;

	if(folding(aa->titulo) == folding(bb))
	{
		return 0;
	}
	else if(folding(aa->titulo) < folding(bb))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int compararAUTOR(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	Libro *bb = (Libro*) b;

	if(folding(aa->autor) == folding(bb->autor))
	{
		return 0;
	}
	else if(folding(aa->autor) < folding(bb->autor))
	{
		return -1;
	}
	else
	{
		return 1;
	}

}
int compararAUTOR_LC(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	char *bb = (char*) b;

	if(folding(aa->autor) == folding(bb))
	{
		return 0;
	}
	else if(folding(aa->autor) < folding(bb))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int compararDATE(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	Libro *bb = (Libro*) b;

	return (compararEntero(&aa->fecha,&bb->fecha));
}

int compararDATE_LC(void *a, void *b)
{
	Libro *aa = (Libro*) a;
	int *bb = (int*) b;

	return (compararEntero(&aa->fecha,bb));
}
int compararEntero(void*a,void*b)
{
	int *aa = (int*)a,*bb = (int*)b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

char minuscula(char c)
{
	if( c >= 'A' && c <= 'Z')
	{
		return c+32;
	}
	return c;
}

int hash(int clave,int tam)
{
	return clave % tam;
}

int rehash(int indice,int k,int tam)
{
	return (indice+k*k)%tam;
}

int validarHashTable(HashTable *hashtable)
{
	if(!hashtable->tabla)
	{
		printf("\n No se ha reservado espacio");
		return 0;
	}
	if(!hashtable->folding )
	{
		printf("\n No se ha asignado alguna de estas funciones: folding,hash,rehash");
		return 0;		
	}
	if(!hashtable->comparar || !hashtable->imprimir)
	{
		printf("\n No se ha asignado alguna de estas funciones: comparar,imprimir");
		return 0;		
	}
	return 1;	
}


HashTable inicializarHashTable(int tam,void (*imprimir)(void*),int (*comparar)(void*,void*),int (*folding)(void*))
{
	HashTable hashtable = (HashTable) {NULL,tam,0,folding,imprimir,comparar};
	while(!hashtable.tabla)
		hashtable.tabla = (void**) calloc(tam,sizeof(void*));
	return hashtable;	
}
int insertarClave(HashTable* hashtable,void *dato)
{
    if(!validarHashTable(hashtable))
        return 0;
    
    // Verificar si el libro ya existe ANTES de insertar
    Libro *nuevoLibro = (Libro*)dato;
    int existe = 0;
    
    // Buscar si ya existe un libro con el mismo ISBN
    for (int i = 0; i < hashtable->tam; i++) {
        if (hashtable->tabla[i] != NULL) {
            Libro *libroExistente = (Libro*)hashtable->tabla[i];
            if (strcmp(libroExistente->isbn, nuevoLibro->isbn) == 0) {
                existe = 1;
                break;
            }
        }
    }
    
    if (existe) {
        printf("\n El libro con ISBN %s ya existe en la tabla", nuevoLibro->isbn);
        return 0;
    }
    
    // Verificar factor de carga y redimensionar si es necesario
    if (hashtable->tam > 0) {
        float factor_carga = (float)hashtable->cant / hashtable->tam;
        if (factor_carga > 0.7) {
            int new_tam = hashtable->tam * 2;
            remapHashTable(hashtable, new_tam);
        }
    }
    
    int clave,indice,nuevo_indice,k;
    clave = hashtable->folding(dato);
    indice = hash(clave,hashtable->tam);
    
    if(hashtable->tabla[indice] == NULL) {
        hashtable->tabla[indice] = dato;
    } else {
        k = 0;
        do {
            k++;
            nuevo_indice = rehash(indice,k,hashtable->tam);
        } while( hashtable->tabla[nuevo_indice] != NULL && k < hashtable->tam);
        
        if(k >= hashtable->tam) {
            printf("\n Tabla hash llena, no se pudo insertar");
            return 0;
        }
        hashtable->tabla[nuevo_indice] = dato;
    }
    hashtable->cant++;
    return 1;        
}

void imprimirHashTabla(HashTable *hashtable)
{
	if(!validarHashTable(hashtable))
		return;
	int i,cont=0;
	for(i = 0; i < hashtable->tam ; i++)
	{
		if(hashtable->tabla[i]!=NULL)
		{
			printf("\n [%d] = ",i);
			hashtable->imprimir(hashtable->tabla[i]);
			cont++;
			if( cont == hashtable->cant)
				break;
		}
		else
			printf("\n [%d] = ",i);
	}		
}

Arbol buscarClave(HashTable* hashtable,void *dato,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
    Arbol arbol = {NULL,0,imprimir,comparar,NULL};
    
    if(!validarHashTable(hashtable))
        return arbol;	
    
    int clave,indice,nuevo_indice,k;
    clave = hashtable->folding(dato);
    indice = hash(clave,hashtable->tam);
    
    // Usar un conjunto temporal para evitar duplicados
    int *encontrados = calloc(hashtable->cant, sizeof(int));
    int idx = 0;
    
    for (k = 0; k < hashtable->tam; k++)
    {
        nuevo_indice = rehash(indice, k, hashtable->tam);

        if (hashtable->tabla[nuevo_indice] == NULL)
            continue;

        // Verificar si ya procesamos este libro
        int ya_encontrado = 0;
        for (int i = 0; i < idx; i++) {
            if (hashtable->tabla[encontrados[i]] == hashtable->tabla[nuevo_indice]) {
                ya_encontrado = 1;
                break;
            }
        }
        
        if (ya_encontrado) continue;
        
        // Usar la función de comparación de la tabla hash
        if (hashtable->comparar(hashtable->tabla[nuevo_indice], dato) == 0)
        {
            // Verificar si ya está en el árbol usando comparación por ISBN
            int duplicado = 0;
            if (arbol.raiz != NULL) {
                //Libro *libroArbol = NULL;
                Libro *libroActual = (Libro*)hashtable->tabla[nuevo_indice];
                
                // Función auxiliar para buscar por ISBN en el árbol
                
                
                if (buscarPorISBN(arbol.raiz, libroActual->isbn) != NULL) {
                    duplicado = 1;
                }
            }
            
            if (!duplicado) {
                insertarArbol(&arbol, hashtable->tabla[nuevo_indice]);
                encontrados[idx++] = nuevo_indice;
            }
        }
    }
    
    free(encontrados);
    return arbol;
}




Arbol buscarLAUTOR(HashTable* hashtable,void *dato,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
	Arbol arbol = {NULL,0,imprimir,comparar,NULL};
	
	//arbolA.imprimir = &imprimirEntero;
	//arbolA.comparar = &compararEntero;
	//arbolA.liberar = &liberarInt
	if(!validarHashTable(hashtable))
		return arbol;	
	int clave,indice,nuevo_indice,k;
	//printf("\n BANDERA 1");
	clave = hashtable->folding(dato);
	indice = hash(clave,hashtable->tam);
	//printf("\n BANDERA 2");
	for (k = 0; k < hashtable->tam; k++)
	{

        nuevo_indice = rehash(indice, k, hashtable->tam);

        // si está vacía, no detenemos
        if (hashtable->tabla[nuevo_indice] == NULL)
            continue;

        // comparamos libro con libro
        if (hashtable->comparar(hashtable->tabla[nuevo_indice], dato) == 0)
		{
			insertarArbol(&arbol, hashtable->tabla[nuevo_indice]);
			
		}
            
    }
	return arbol;
}

float factorCarga(HashTable *hashtable)
{
    if (!hashtable || hashtable->tam == 0)
        return 0.0f;
    return (float)hashtable->cant / hashtable->tam;
}

//////

Arbol buscarRangoTitulo(HashTable *hashtable, char min, char max,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
    Arbol arbol = {NULL,0,imprimir,comparar,NULL};
    if (!validarHashTable(hashtable)) 
		return arbol;


    if (min > max)
	{
		char aux = min; 
		min = max; 
		max = aux;
	}

    for (int i = 0; i < hashtable->tam; i++) 
	{
        if (hashtable->tabla[i] != NULL) {
            Libro *lib = (Libro*) hashtable->tabla[i];

            if (lib->titulo[0] == '\0') 
				continue;

            char c = minuscula(lib->titulo[0]);

            if (c >= min && c <= max) 
				insertarArbol(&arbol, lib);
        }
    }
    return arbol;
}

Arbol buscarRangoAutor(HashTable *hashtable, char min, char max,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
    Arbol arbol = {NULL,0,imprimir,comparar,NULL};
    if (!validarHashTable(hashtable)) 
        return arbol;

    if (min > max) {
        char aux = min; 
        min = max; 
        max = aux;
    }

    // Usar un array para trackear ISBNs ya insertados
    char **isbnsInsertados = calloc(hashtable->cant, sizeof(char*));
    int count = 0;

    for (int i = 0; i < hashtable->tam; i++)
	{
        if (hashtable->tabla[i] != NULL) {
            Libro *lib = (Libro*)hashtable->tabla[i];
            
            if (lib->autor[0] == '\0') 
                continue;

            char c = minuscula(lib->autor[0]);
			//printf("\n %c", c);
            
            if (c >= min && c <= max) 
			{
                // Verificar si ya insertamos este ISBN
                int duplicado = 0;
                for (int j = 0; j < count; j++) {
                    if (strcmp(isbnsInsertados[j], lib->isbn) == 0) {
                        duplicado = 1;
                        break;
                    }
                }
                
                if (!duplicado) 
				{
                    insertarArbol(&arbol, lib);
					//printf("\n GUARDADO: %c", c);
                    isbnsInsertados[count] = lib->isbn;
                    count++;
                }
            }
        }
    }

    free(isbnsInsertados);
    return arbol;
}

Arbol buscarRangoFecha(HashTable *hashtable, int min, int max,void (*imprimir)(void*),int (*comparar)(void*,void*))
{
    Arbol arbol = {NULL,0,imprimir,comparar,NULL};
    if (!validarHashTable(hashtable)) 
		return arbol;


	if (min > max)
	{
		int aux = min; 
		min = max; 
		max = aux;
	}
    
    for (int i = 0; i < hashtable->tam; i++) {
        if (hashtable->tabla[i] != NULL) 
		{
            Libro *lib = (Libro*) hashtable->tabla[i];
            
			if (lib->fecha >= min && lib->fecha <= max) 
				insertarArbol(&arbol, lib);
        }
    }
    return arbol;
}

int eliminarLibroPorISBN(HashTable *hashtable, const char *isbn, void (*liberar)(void*))
{
    if (!validarHashTable(hashtable) || isbn == NULL)
        return 0;

    // Crear libro temporal para búsqueda
    Libro libroBusqueda = {0};
    strncpy(libroBusqueda.isbn, isbn, sizeof(libroBusqueda.isbn) - 1);
    
    int encontrado = 0;
    
    for (int i = 0; i < hashtable->tam; i++) 
    {
        void *p = hashtable->tabla[i];
        
        if (p == NULL)
            continue;

        Libro *libro = (Libro*)p;
        
        // Comparar directamente por ISBN
        if (strcmp(libro->isbn, isbn) == 0) {
            if (liberar)
                liberar(p);
            hashtable->tabla[i] = NULL;
            hashtable->cant--;
            encontrado = 1;
            break;
        }
    }

    // Redimensionar si es necesario
    if (hashtable->tam > 10) {
        float factor_carga = (float)hashtable->cant / hashtable->tam;
        if (factor_carga < 0.2) {
            int new_tam = hashtable->tam / 2;
            if (new_tam < 10) new_tam = 10;
            remapHashTable(hashtable, new_tam);
        }
    }

    return encontrado;
}

int eliminarLibro(HashTable *hashtable, void *dato, void (*liberar)(void*))
{
    if (!validarHashTable(hashtable) || dato == NULL)
        return 0;

    int encontrado = 0;
    
    for (int i = 0; i < hashtable->tam; i++) 
    {
        void *p = hashtable->tabla[i];
        
        if (p == NULL)
            continue;

        // Usar la función de comparación de la tabla hash
        if (hashtable->comparar(p, dato) == 0) {
            if (liberar)
                liberar(p);
            hashtable->tabla[i] = NULL;
            hashtable->cant--;
            encontrado = 1;
            break; // Solo eliminar una ocurrencia
        }
    }

    // Redimensionar si el factor de carga es muy bajo
    if (hashtable->tam > 10) {
        float factor_carga = (float)hashtable->cant / hashtable->tam;
        if (factor_carga < 0.2) {
            int new_tam = hashtable->tam / 2;
            if (new_tam < 10) new_tam = 10;
            remapHashTable(hashtable, new_tam);
        }
    }

    return encontrado;
}


void remapHashTable(HashTable *hashtable, int new_tam)
{
    if (!validarHashTable(hashtable) || new_tam <= 0)
        return;

    if (new_tam == hashtable->tam)
        return;

    //printf("\n Redimensionando tabla hash de %d a %d", hashtable->tam, new_tam);

    int old_tam = hashtable->tam;
    void **backup = (void **) malloc(old_tam * sizeof(void *));
    
    if (!backup) 
        return;

    int n = 0;
    for (int i = 0; i < old_tam; i++) {
        void *p = hashtable->tabla[i];
        if (p != NULL) {
            backup[n++] = p;
        }
    }

    free(hashtable->tabla);
    hashtable->tam = new_tam;
    hashtable->tabla = (void**) calloc(new_tam, sizeof(void*));
    hashtable->cant = 0;

    for (int i = 0; i < n; i++) {
        insertarSinResize(hashtable, backup[i]);
    }

    free(backup);
}

int insertarSinResize(HashTable* hashtable, void *dato)
{
    if(!validarHashTable(hashtable))
        return 0;

    int clave = hashtable->folding(dato);
    int indice = hash(clave, hashtable->tam);

    if(hashtable->tabla[indice] == NULL)
        hashtable->tabla[indice] = dato;
    
	else{
        int k = 0;
        int nuevo_indice;
        do{
            k++;
            nuevo_indice = rehash(indice,k,hashtable->tam);
        } while( hashtable->tabla[nuevo_indice] != NULL);
        hashtable->tabla[nuevo_indice] = dato;
    }
    hashtable->cant++;
    return 1;
}