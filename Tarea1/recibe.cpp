#include "asincrona.h"
int main(){
	int N=20;
	BYTE mensaje[N];
	printf("su mensaje es	:");
	openPort(18, 100000);
	readPort(18,mensaje,N);
	printf("%c",(char)mensaje[0]);
	return 0;
	}
