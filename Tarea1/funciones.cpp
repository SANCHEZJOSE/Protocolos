#include <funciones.h>
#include <stdio.h>


int fcs(BYTE *x,int n){
	int c=0;
	for(int j=0;j<n;j++){
        for (int i = 0; i < 8; ++i)
        {
            if ((x[j]>>i)&0x01){
                c++;}
            }
        }
    }


