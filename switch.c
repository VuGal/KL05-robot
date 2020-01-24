#include "MKL05Z4.h"
#include "switch.h"

#define SWITCH 13

//inicjalizacja przycisku
void switchInitialize(void)
{
	PORTB->PCR[SWITCH]|=PORT_PCR_MUX(1);
	PORTB->PCR[SWITCH]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTB->PCR[SWITCH]|=PORT_PCR_IRQC(11);  //PTB13 ustawione jako wejscie sygnalu z przelacznika, wlaczone przerwania
}

//obsluga przycisku
int32_t switchHandler(void)
{
	return FPTB->PDIR&(1UL<<SWITCH);	//odczytujemy stan przycisku za pomocą rejestrow szybkiego dostepu
}