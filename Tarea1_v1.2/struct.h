#ifndef STRUCT
#define STRUCT

#define N 510//Bytes de data

struct Paquete{
	int cmd;//3 bits
	int Long;//510 < 2^9=> 9 bits
	unsigned char data[N];//510 Bytes=4080 bits max
	int fcs;//4080 < 2^12 => 12 bits
	unsigned char frame [N+3];//4080+9+510+12+3=513 Bytes max
};
#endif
