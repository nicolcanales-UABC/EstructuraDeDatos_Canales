cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/Captura -I ../src/Estructuras
libs = ../../lib -lCaptura -lArbol
source = $(wildcard *.c) 
output = ../../bin/practica6

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\Captura
	make -C ..\Estructuras\Nodo
	make -C ..\Estructuras\Arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	..\..\bin\practica6.exe