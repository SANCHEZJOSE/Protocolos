#include "asincrona.h"
int main(){
	int N=513;
	while(true){
	BYTE mensaje[N];
	printf("cual es su mensaje :");
	fgets((char*)mensaje,N,stdin);
	int size=strlen((char*)mensaje)-1;
	//printf("tamaño %d",size);
	openPort(17,10000);
	writePort(17,mensaje,size);
	}
	return 0;
	}
