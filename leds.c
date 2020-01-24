#include "MKL05Z4.h"
#include "leds.h"

const uint32_t blue_mask = 1UL<<10;
const uint32_t red_mask = 1UL<<8;
const uint32_t green_mask = 1UL<<9;

//inicjalizacja diod LED
void ledsInitialize(void)
{
	SIM->SCGC5|= SIM_SCGC5_PORTB_MASK;  //podpiecie zegara do portu B
	PORTB->PCR[10] = PORT_PCR_MUX(1);
	PORTB->PCR[8] = PORT_PCR_MUX(1);
	PORTB->PCR[9] = PORT_PCR_MUX(1); 	//ustawienie pinow jako GPIO
  	FPTB->PDDR|= blue_mask;
	FPTB->PDDR|= red_mask;
	FPTB->PDDR|= green_mask;			//ustawienie pinow jako wyjsciowe
	PTB->PSOR = blue_mask;
	PTB->PSOR = green_mask;
	PTB->PSOR = red_mask;				//zgaszenie diod (odwrotna logika, kiedy podajemy 1 dioda gasnie, kiedy 0 zapala sie)
}

//zapalenie niebieskiej diody
void ledBlueOn (void) {
	PTB->PCOR = blue_mask;  
	for(int i=0; i<1200000; ++i);
}

//zgaszenie niebieskiej diody
void ledBlueOff(void)
{
	PTB->PSOR = blue_mask;
	for(int i=0; i<1200000; ++i){};
}

//zapalenie czerwonej diody
void ledRedOn (void) {
	PTB->PCOR = red_mask;
	for(int i=0; i<1200000; ++i) {};	
}

//zgaszenie czerwonej diody
void ledRedOff(void)
{
	PTB->PSOR = red_mask;
	for(int i=0; i<1200000; ++i){};	
}

//zapalenie zielonej diody
void ledGreenOn (void) {
	PTB->PCOR = green_mask;
	for(int i=0; i<1200000; ++i);
}

//zgaszenie zielonej diody
void ledGreenOff(void)
{
	PTB->PSOR = green_mask; 
	for(int i=0; i<1200000; ++i);
}