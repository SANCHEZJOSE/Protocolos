#include "funciones.h"
#define U_TIME 50000
#define PUERTO 17
int main(){
	//int c = 0;
	openPort( PUERTO , U_TIME ) ;
	Paquete p;
	p.cmd=3;
	while(true){//(c<=10000){
		printf("Cual es su mensaje? : ");
		fgets((char*)p.data,N,stdin);
		int size = strlen((char*)p.data);
		size--;
		p.Long=size;
		envia(PUERTO,p);
		//c++;
	}
	//closePort(puerto);
	return 0;
}
