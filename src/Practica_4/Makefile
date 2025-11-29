cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/Captura -I ../src/Estructuras/Pila
libs = ../../lib -lCaptura -lPila
source = $(wildcard *.c) 
output = ../../bin/practica4

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\Captura
	make -C ..\Estructuras\Nodo
	make -C ..\Estructuras\Pila
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"