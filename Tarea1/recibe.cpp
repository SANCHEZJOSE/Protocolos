#include "asincrona.h"
int main(){
	int N=1;
	BYTE mensaje[N];
	printf("su mensaje es	:");
	openPort(18, 100000);
	readPort(18,mensaje,N);
	printf("%d\n",(int)mensaje);
	return 0;
	}
