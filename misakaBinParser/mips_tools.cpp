#include "stdafx.h"

using namespace MisakaTool;

//helper struct to store state of the MIPS code translation
long MipsCpy::lbu(long adr){
	if (adr & 0x40000000){
		unsigned char value = reinterpret_cast<unsigned char &>((*container)[adr & 0x0FFFFFFF]);
		return value;
	}
	//return *(reinterpret_cast<unsigned char *>(adr));
	return  reinterpret_cast<unsigned char &>((*container2)[adr]);
}

void MipsCpy::sb(long toStore, long location){
	location = location & 0x0FFFFFFF;
	if (location >= container->size()){
		container->resize(location + 1);
	}
	//unsigned char *loc = reinterpret_cast<unsigned char *>(location);
	//*loc = toStore & 0xFF;
	unsigned char byte = (toStore & 0xFF);
	(*container)[location] = reinterpret_cast<char &>(byte);
}

void MipsCpy::sw(long toStore, long location){
	unsigned int *loc = reinterpret_cast<unsigned int *>(location);
	*loc = toStore & 0xFFFFFFFF;
}
