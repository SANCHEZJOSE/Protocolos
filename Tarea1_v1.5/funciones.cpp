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
        if(p.Long>0){
                        //3 bits        +       5 bits               
        p.frame[0] = (p.cmd & 0x07) | ( (p.Long & 0x1F)<<3);
                         //4 bits        +       4 bits  
        p.frame[1]=((p.Long >> 5) & 0x0F) | ((p.data[0] & 0x0F) << 4);
        for( int i = 0 ; i < p.Long-1; i++ ){
                                        //4 bits        +       4 bits  
                p.frame[2+i] = ((p.data[i]>>4)&0x0F) | ((p.data[i+1]&0x0F)<<4);
        }

        p.frame[p.Long+1]=((p.data[p.Long-1]<<4)&0x0F);

        p.fcs =fcs(p.frame,p.Long+2); //calcular checksum
        p.frame[p.Long+1]=((p.data[p.Long-1]<<4)&0x0F) | ((p.fcs&0x0F)<<4);//agrega checksum a frame
        p.frame[p.Long+2]=((p.fcs>>4)&0xFF);
        writePort(port, p.frame, p.Long+3);
        }
        return true;
}

bool recibe(int port, Paquete &p,int timeOutMs){
        int n=readPort(port,p.frame,2,timeOutMs);
        if(n>0){
                p.cmd = p.frame[0] & 0x07;
                p.Long = ((p.frame[0] & 0xF8)>>3) | ((p.frame[1]&0x0F)<<4);
		readPort(port,p.frame+2,p.Long+1,timeOutMs);
                if(n != p.Long+1)
                        return false;
                p.fcs =fcs(p.frame,p.Long+2);
                if( p.fcs == ((p.frame[p.Long+1]>>4) | (p.frame[p.Long+2]<<8)) ){
                        p.data[0]=(p.frame[1]>>4) | ((p.frame[2]&0x0F)<<4);
                        for(int i = 0 ; i < p.Long; i++){
                                p.data[i+1]=(p.frame[i+2]>>4) | ((p.frame[i+3]&0x0F)<<4);
                        }
                        return true;
                }else{
                        printf("Error en trama.");
                        fflush(stdout);
                        return false;
                }
        }
        return false;
}
