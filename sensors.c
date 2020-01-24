#include "MKL05Z4.h"
#include "sensors.h"

#define OUT_PIN 7 //PTB7
#define OUT1_PIN 6 //PTA6
#define OUT2_PIN 8  //PTA8

//inicjalizacja sensorow
void sensorsInitialize(void)
{
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;				//podlaczenie zegara do portu A

	PORTA->PCR[OUT1_PIN]|=PORT_PCR_MUX(1);
	PORTA->PCR[OUT1_PIN]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTA->PCR[OUT1_PIN]|=PORT_PCR_IRQC(11); 				// pin, do ktorego zostal podlaczony sensor, jako wejscie z aktywnym przerwaniem
	// na dowolnym zboczu
	
	PORTA->PCR[OUT2_PIN]|=PORT_PCR_MUX(1);
	PORTA->PCR[OUT2_PIN]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTA->PCR[OUT2_PIN]|=PORT_PCR_IRQC(11);		// pin, do ktorego zostal podlaczony sensor, jako wejscie z aktywnym przerwaniem
	// na dowolnym zboczu
	
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;			//podlaczenie zegara do portu B
	
	PORTB->PCR[OUT_PIN]|=PORT_PCR_MUX(1);
	PORTB->PCR[OUT_PIN]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTB->PCR[OUT_PIN]|=PORT_PCR_IRQC(11);			// pin, do ktorego zostal podlaczony sensor, jako wejscie z aktywnym przerwaniem
	// na dowolnym zboczu
	
	NVIC_ClearPendingIRQ(30);			//wyczysc czekajace przerwania na porcie A
	NVIC_EnableIRQ(30);					//wlacz przerwania na porcie A
	NVIC_ClearPendingIRQ(31);			//wyczysc czekajace przerwania na porcie B
	NVIC_EnableIRQ(31);					//wlacz przerwania na porcie B
	NVIC_SetPriority(30, 2);			//ustaw priorytet przerwan
	NVIC_SetPriority(31, 2);
	
}

//odczyt z przedniego sensora
int32_t sensorReadForward(void)
{
	return FPTB->PDIR&(1UL<<OUT_PIN);		//odczytanie stanu rejestru wejsciowego danego portu za pomoca rejestru szybkiego dostepu
}

//odczyt z lewego sensora
int32_t sensorReadLeft(void)
{
	return FPTA->PDIR&(1UL<<OUT1_PIN);	//odczytanie stanu rejestru wejsciowego danego portu za pomoca rejestru szybkiego dostepu
}

//odczyt z prawego sensora
int32_t sensorReadRight(void)
{
	return FPTA->PDIR&(1UL<<OUT2_PIN);	//odczytanie stanu rejestru wejsciowego danego portu za pomoca rejestru szybkiego dostepu
}
