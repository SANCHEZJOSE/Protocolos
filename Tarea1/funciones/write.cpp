#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <unistd.h>
#define BYTE unsigned char
#define U_TIME 200//105	//medio ciclo de la señal
#define Pin_signal 17 //en donde se generara la señal

int main()
{
	if (wiringPiSetupGpio()==-1)
	{
		printf("No se pudo iniciar la libreria wiringPi");
		return 0;
	}
	pinMode(Pin_signal,OUTPUT);

		char byte;
		int c;
		printf("ingrese un caracter\n");
		scanf("%c",&byte);
		digitalWrite(Pin_signal,LOW);//bit de inicio
		delayMicroseconds(U_TIME);
		int i=0;
		while(i<8){
			if ((byte>>i) & 0x01){
				digitalWrite(Pin_signal,HIGH);
				delayMicroseconds(U_TIME);
				c++;
			}
			else{
				digitalWrite(Pin_signal,LOW);
				delayMicroseconds(U_TIME);
			}
			i++;
			}
		digitalWrite(Pin_signal,(c%2)==0);//pariedad
		delayMicroseconds(U_TIME);
		digitalWrite(Pin_signal,HIGH);//bit de termino
		delayMicroseconds(U_TIME*2);
		return 0;
}
