#include "asincrona.h"
#include "funciones.h"
#include "struct.h"

#define size 513

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

int fcs (BYTE x,int n){
    int c = 0;
    for(int i = 0 ; i < 8 ; i++){
        if( (x>>i) & 0x01 ){
           c++;
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
            p.frame[2+i] = ((p.data[i] & 0xF0)>>4) | ((p.data[i+1]&0x0F)<<4);
        }

        p.frame[p.Long+1]=((p.data[p.Long-1]&0xF0)>>4);

            p.fcs =fcs(p.frame,p.Long+2); //calcular checksum
            p.frame[p.Long+1]=((p.data[p.Long-1]&0xF0)>>4) | ((p.fcs&0x0F)<<4);//agrega checksum a frame
            p.frame[p.Long+2]=((p.fcs>>4)&0xFF);
            writePort(port, p.frame, p.Long+3);
        }
    return true;
}

bool recibe(int port, Paquete &p,int timeOutMs){
        int Error=0;//detección de error checksum
        bool paridad=true;//detección de error de paridad
        int n=readPort(port,p.frame,513,timeOutMs,paridad);//devuelve la cantidad de caracteres leidos
        p.cmd = p.frame[0] & 0x07;//3 bits de comandos
        p.Long = ((p.frame[0] & 0xF8)>>3) | ((p.frame[1]&0x0F)<<5);//guarda el largo empaquetado en frame
         if((n) != p.Long+3)//compara el tamaño del string leido con el tamaño teorico
            Error=1;
        p.fcs=fcs(p.frame,p.Long+1)+fcs((p.frame[p.Long+1]&0x0F),1);//obtención del checksum al desempaquetar
        if( p.fcs == ((p.frame[p.Long+1]>>4) | (p.frame[p.Long+2])<<4) ){//checksum obtenido vs checksum desempaquetado
            p.data[0]=(p.frame[1]>>4) | ((p.frame[2]&0x0F)<<4);//obtención de la data desde el frame
            for(int i = 0 ; i < p.Long; i++){
                p.data[i+1]=(p.frame[i+2]>>4) | ((p.frame[i+3]&0x0F)<<4);
            }
		return true;
        }else{
            Error=1;
        }
    if (Error==1 || !paridad)
    {
        return false;
    }
    else{
        return true;
    }
    
}
