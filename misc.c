#include "MKL05Z4.h"
#include "misc.h"

//funkcja opozniajaca
void delay(int cycles)
{
	for(int i=cycles*10; i>=0; --i){};
}

