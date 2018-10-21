#include "asincrona.h"

int pin_Signal=17,Periodo=200,bits=12,pprueba=3*Periodo/2,timeout;
int cant_bytes=0,tolerancia=-56;

unsigned int t_anterior,tiempo=0;//tiempos para timeout(receptor)

void openPort( int pinSignal , int tiempo){
	pin_Signal=pinSignal;
	if ( wiringPiSetupGpio() == -1 )
	{
		printf("No se pudo iniciar la libreria wiringPi");
	}
	Periodo=tiempo;
	pprueba=3*Periodo/2;
}

void enviarByte( BYTE byte ){
	digitalWrite( pin_Signal , LOW );//bit de inicio
	delayMicroseconds( Periodo );//duracion del bit
	int paridad=0;
	for(int i=0;i<8;i++){
		if ((byte>>i) & 0x01 ){//pulso por cada bit activo
			digitalWrite( pin_Signal , HIGH );
			delayMicroseconds( Periodo );
			paridad++;
		}
		else{
			digitalWrite( pin_Signal , LOW );
			delayMicroseconds( Periodo );
		}
	}
	digitalWrite( pin_Signal , (paridad%2) == 0 );//paridad
	delayMicroseconds( Periodo );
	digitalWrite( pin_Signal , HIGH );//bit de termino
	delayMicroseconds( Periodo*2 );
}

bool recibirByte(BYTE & dato){
	bool level;
	int paridad,c;
	dato=0;
	int i=0;
	while(i<9){
		level=digitalRead(pin_Signal);
		if ((level== 1)&&(i<8)){
			dato= dato | ( 0x01<<i );
			c++;}
			if ( (level == 1) && i==8)
				paridad=1;
			else
				paridad=0;
			i++;
			delayMicroseconds(Periodo+tolerancia);
		}
		return ((c%2) != paridad);
}

void writePort(int pinSignal, BYTE *data, int size){
		pin_Signal = pinSignal;
		pinMode(pin_Signal , OUTPUT);
		for(int i=0;i<size;i++){
			enviarByte(data[i]);
		}
}
int readPort(int pinSignal, BYTE *data, int size,int timeout_msec){
	tiempo=0;
	pin_Signal=pinSignal;
	pinMode(pin_Signal , INPUT);
	timeout=timeout_msec;
	bool level,state;
	state=1;
	for(int i=0;i<size;i++){
		if (i>0)
			t_anterior=millis();//tiempo antes de esperar el bit de inicio
	do
	{
		level=digitalRead(pin_Signal);
		if(i>0){
			tiempo=millis()-t_anterior;//delta tiempo
			if(tiempo>=(unsigned int)timeout)
				break;}
	} while (level==state);//&& tiempo<(unsigned int)timeout);
	cant_bytes=i;
	if (tiempo<(unsigned int)timeout || i==0){
		delayMicroseconds(pprueba+tolerancia);
		if (!recibirByte(data[i]))
			{
			return -1;
			}
	}
	else {
		data[i]='\0';
		return i;
		}
	}
	return cant_bytes;
}

