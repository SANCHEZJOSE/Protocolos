#include "asincrona.h"
#include "funciones.h"

#define U_TIME 5000
#define PUERTO 18

int main(){
	openPort(PUERTO,U_TIME);
	while (true){
		Paquete p;
	if(recibe(PUERTO,p,U_TIME/1000*3)){//timeuot debe ser > a 3 veces la 
	//duracion del bit de parada.
		p.data[p.Long]='\0';
		printf("paquete ok: |%s|\n",p.data);
		}
	else{
		printf("Error de trama \n");
		}
	}
	//closePort(fn);
	return 0;
}
