#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "funciones.h"
int fcs(BYTE *x,int n);
int main(){
     char DEVICE[13]={"/dev/ttyUSB0"};
     char c[31];
     Byte frame[32];
     int fn=openPort(DEVICE,B9600);
     if(fn==-1){
         printf("Error al abrir el puerto.");
         exit(0);
     }
     int cmd=3;//3bits menossignificativo
     while(true){
        printf("Cual es su mensaje? :");
        fgets((char*)c,sizeof(c),stdin);
        int n = strlen((char*)c);
        n--;

        frame[0]=(cmd&0x07) | ((n & 0x1F)<<3);
        for (int i = 0; i < n; ++i)
        {
            frame[1+i]=c[i];
        }
        frame[n+1]=fcs(frame,n+1);
       
	    writePort(fn,frame,n+2);
     }
     closePort(fn);
     return 0;
}


