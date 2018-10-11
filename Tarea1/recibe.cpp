#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "funciones.h"

int main(){
    char DEVICE[13]={"/dev/ttyUSB0"};
     char c[31];
     int fn=openPort(DEVICE,B9600);
     if(fn==-1){
         printf("Error al abrir el puerto.");
         exit(0);
     }
     while(true){
        int n=readport(fn,frame,1,300);
        if (n>0){
            cmd=frame[0] & 0x07;
            int l=(frame[0]  & 0xF8)>>3;
            n=readport(fn,frame+1,l+1,300);
            
            int err=fcs(frame,n+1);
            if (err==frame[l+1])
            {   
                char data[31];
            for (int i = 0; i < l; ++i)
            {
                data[i]=frame[i+1];
            }   
                data[l]='\0';
                printf("paquete OK !%s\n",(char*)data );
            }
            else {
                printf("error en trama\n");}
            }
            }
     closePort(fn);
     return 0;
}

