#include "asincrona.h"
int main(){
	while(true){
	int N=513;
	BYTE mensaje[N];
	openPort(18,10000);
	readPort(18,mensaje,N,100);
	printf("su mensaje es :|%s|\n",(char*)mensaje);
	}
	return 0;
	}
