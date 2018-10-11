
all:
	g++ -o envia.o envia.cpp -Wall -c -g
	g++ -o serial.o serial.cpp -Wall -c -g
	g++ -Wall -g envia.o serial.o -o envia
	g++ -o recibe.o recibe.cpp -Wall -c -g
	g++ -Wall -g recibe.o serial.o -o recibe

clean:
	rm -rf *.o envia recibe
