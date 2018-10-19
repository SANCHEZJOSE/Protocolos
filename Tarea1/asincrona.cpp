#include "asincrona.h"
int pin_Signal=17,Periodo=200,bits=12;
void	openPort( int signal , int tiempo){
	pin_Signal=signal;
	if ( wiringPiSetupGpio() == -1 )
		printf("No se pudo iniciar la libreria wiringPi");
	Periodo=tiempo;
}
void enviarByte( BYTE byte ){
	digitalWrite( pin_Signal , LOW );//bit de inicio
	delayMicroseconds( Periodo );//duracion del bit
	int i=0,paridad=0;
	while(i<8){
		if ((byte>>i) & 0x01 ){//pulso por cada bit activo
			digitalWrite( pin_Signal , HIGH );
			delayMicroseconds( Periodo );
			paridad++;
		}
		else{
			digitalWrite( pin_Signal , LOW );
			delayMicroseconds( Periodo );
		}
		i++;
		}
	digitalWrite( pin_Signal , (paridad%2) == 0 );//paridad
	delayMicroseconds( Periodo );
	digitalWrite( pin_Signal , HIGH );//bit de termino
	delayMicroseconds( Periodo*2 );
	}
void writePort(int serial_fd, BYTE *data, int size){
	pin_Signal = serial_fd;
	pinMode(pin_Signal , OUTPUT);
	for(int i=0;i<size;i++){
		enviarByte(data[i]);
		}

	}
void readPort(int serial_fd, BYTE *data, int size){
	pin_Signal=serial_fd;
	pinMode(pin_Signal , INPUT);
	for(int i=0;i<size;i++){
		recibirByte(data[i]);
		}
    
}
bool recibirByte(BYTE & dato){
	bool level,state;
	int paridad,c;
	dato=0;
	state=1;//digitalRead(pin_Signal);
	do
	{
	level=digitalRead(pin_Signal);
	} while (level==state);
    delayMicroseconds(3*Periodo/2);
    int i=0;
	while(i<(bits-3)){
		level=digitalRead(pin_Signal);
		if ((level== 1)&&(i<8)){
			dato= dato | ( 0x01<<i );
			//printf("%d	",i);
			c++;}
		if ( (level == 1) && i==8)
			paridad=1;
		else
			paridad=0;
		i++;
		delayMicroseconds(Periodo);
	}
	return ((c%2) == paridad);
	}
