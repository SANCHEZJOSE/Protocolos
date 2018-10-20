#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "asincrona.h"
#include "struct.h"

/*PROTOTIPOS*/

int fcs(BYTE* x, int n);
bool envia(int port, Paquete &p);
bool recibe(int port, Paquete &p,int timeOutMs);

#endif


