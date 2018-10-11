/******************************************************************/
/* serial.h    Dr. Juan Gonzalez Gomez.    January, 2009          */
/*----------------------------------------------------------------*/
/* Serial communications in Linux                                 */
/*----------------------------------------------------------------*/
/* GPL LICENSE                                                    */
/******************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

#include <termios.h>

#define BYTE unsigned char

/*--------------------------*/
/* FUNCTION PROTOTYPES      */
/*--------------------------*/

int  begin(char *serial_name, speed_t baud);
void write(int serial_fd, BYTE *data, int size);
void end();


#endif
