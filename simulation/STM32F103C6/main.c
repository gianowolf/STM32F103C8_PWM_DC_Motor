#include <stm32f103x6.h>
#include "Seos.h"

int main (void)
{ 
	SEOS_Boot();
	while (1)
	{
		SEOS_Dispatcher();
		SEOS_Sleep();
	}
}
