all:

	g++ -o asincrona.o asincrona.cpp -lwiringPi -Wall -c -g
	g++ -o funciones.o funciones.cpp -lwiringPi -Wall -c -g
	g++ -o envia.o envia.cpp -Wall -c -g
	g++ -o recibe.o recibe.cpp -Wall -c -g
	g++ -Wall -g envia.o asincrona.o funciones.o -lwiringPi -o envia 
	g++ -Wall -g recibe.o asincrona.o funciones.o -lwiringPi -o recibe

clean:

	rm -rf *.o envia recibe
