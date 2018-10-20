#include "asincrona.h"
#include "funciones.h"

#define U_TIME 10000
#define PUERTO 18

int main(){
	openPort(PUERTO,U_TIME);
	while (true){
		Paquete p;
		bool ok = recibe(PUERTO,p,300);
	if(ok){
		p.data[p.Long]='\0';
		printf("paquete ok: |%s|\n",p.data);
		fflush(stdout);
		}
	}
	//closePort(fn);
	return 0;
}
