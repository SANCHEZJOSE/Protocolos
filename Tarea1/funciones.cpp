#include "asincrona.h"
#include "funciones.h"
int fcs (BYTE*x,int n){
        int c = 0;
        for( int j = 0 ; j < n ;j++){
                for(int i = 0 ; i < 8 ; i++){
                        if( (x[j]>>i) & 0x01 ){
                        	c++;
			}
                }
        }
        return c;
}
bool envia(int port, Paquete &p){
        p.frame[0] = (p.cmd & 0x07) | ( (p.Long & 0x1F)<<3);
        for( int i = 0 ; i < p.Long ; i++ )
                p.frame[1+i] = p.data[i];
        p.fcs =fcs(p.frame,p.Long+1); //calcular checksum
        p.frame[p.Long+1]= p.fcs & 0xFF;
        writePort(port, p.frame, p.Long+2);
        return true;
}

bool recibe(int port, Paquete &p,int timeOutMs){
        int n=p.Long;
	readPort(port,p.frame,1,timeOutMs);
        if(n>0){
                p.cmd = p.frame[0] & 0x07;
                p.Long = (p.frame[0] & 0xF8)>>3;
                //n=
		readPort(port,p.frame+1,p.Long+1,timeOutMs);
                if(n != p.Long+1)
                        return false;
                p.fcs =fcs(p.frame,p.Long+1);
                if(p.fcs == p.frame[p.Long+1]){
                        for(int i = 0 ; i < p.Long ; i++)
                                p.data[i] = p.frame [i+1];
                        fflush(stdout);
                        return true;
                }else{
                        printf("Error en trama.");
                        fflush(stdout);
                        return false;
                }
        }
        return false;
}
