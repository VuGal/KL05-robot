#include "MKL05Z4.h"
#include "buzzer.h"
#include "leds.h"
#include "motorscontrol.h"

#define BUZZER 5 // D10 = PTA5

const uint32_t buzzer_mask = 1UL<<5;

//inicjalizacja buzzera
void buzzerInitialize(void)
{
	PORTA->PCR[BUZZER]|= PORT_PCR_MUX(1);
	FPTA->PDDR |= buzzer_mask;
	PTA->PCOR = buzzer_mask;				//buzzer jako wyjscie
}

//obsluga buzzera
void buzzerHandler(void)
{
	for(int i=0; i<1200000; i++) stopMotors();
	PTA->PSOR = buzzer_mask;				//podajac stan wysoki na pin wydajemy dzwiek
	for(int j=0; j<600000; j++);
	PTA->PCOR = buzzer_mask;
	ledBlueOn();
	ledBlueOff();
	ledRedOn();
	ledRedOff();
	ledGreenOn();
	ledGreenOff();
}