#ifndef STRUCT
#define STRUCT

#define N 510

struct Paquete{
	int cmd;
	int Long;
	unsigned char data[N];
	int fcs;
	unsigned char frame [N+2];
};
#endif
