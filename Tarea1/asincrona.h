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
void  openPort(int ,int );
void enviarByte(BYTE);
bool recibirByte(BYTE &);
void writePort(int serial_fd, BYTE *data, int size);
void readPort(int serial_fd, BYTE *data, int size,int);
//void closePort(int fd);

#endif
