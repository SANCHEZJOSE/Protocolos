#ifndef ASINCRONA_H
#define ASINCRONA_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <string.h>
///Macros
#define BYTE unsigned char

/// Variables globales
//Pin de la señal,periodo en uS

/// Prototipos
void  openPort(int pinSignal ,int tiempo);
void enviarByte( BYTE byte);
bool recibirByte(BYTE & dato);
void writePort(int pinSignal, BYTE *data, int size);
int readPort(int pinSignal, BYTE *data, int size,int timeout_msec,bool & paridad);
//void closePort(int fd);

#endif
