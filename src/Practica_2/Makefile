cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/Captura -I ../src/Estructuras/ListaDoble
libs = ../../lib -lCaptura -lListadoble
source = $(wildcard *.c) 
output = ../../bin/practica2

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C ..\Captura
	make -C ..\Estructuras\Nodo
	make -C ..\Estructuras\ListaDoble
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"