
#include "funciones.h"
#define U_TIME 50000
#define PUERTO 17
#define CANTIDAD 10000


int opcion;
char aux;
int c=0, cont=0;

void menu(int opcion);

int main(){
        printf("\n\t Menu\n\n1. Enviar Mensaje\n2. Cerrar receptor y programa\n\nElija una opcion: ");
        scanf(" %d",&opcion);
        Paquete p;
        int size;
        switch(opcion){
                case 1:
                        scanf("%c",&aux);
                        p.cmd=1;
                        printf("\tCual es su mensaje? : ");
                        fgets((char*)p.data,N,stdin);
                        printf("\nEnviando Mensaje.. \n");
                        size= strlen((char*)p.data);
                        openPort( PUERTO , U_TIME );
                        while(cont<=CANTIDAD){
                                size--;
                                p.Long=size;
                                envia(PUERTO,p);
                                cont++;
                        }
                        break;
                case 2:
                        p.cmd=7;
                        return 0;
                        break;
                }
        return 0;
}



