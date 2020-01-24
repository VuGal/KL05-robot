#include "MKL05Z4.h"
#include "motorscontrol.h"
//RIGHT MOTOR PTB6 TPM0CH3
//LEFT MOTOR PTA12 TPM1CH0

#define RIGHT_SWITCH 8	//PTA0 // PTB8
#define LEFT_SWITCH 9 //PTA9


//zatrzymanie silnikow
void stopMotors(void)
{
	TPM0->CONTROLS[3].CnV=0; 	//wypelnienie PWM'a TPM0 0%
	TPM0->SC&=~(1<<0);			//wylaczenie timera
	TPM1->CONTROLS[0].CnV=0;	//wypelenie PWM'a TPM1 0%
	TPM1->SC&=~(1<<0);			//wylaczenie timera
}

//jazda do przodu
void forwardsMotors(void)
{
	PTA->PCOR = 1<<10;		
	FPTB->PCOR = 1<<11;		//kierunek obrotu kol (do przodu)
	TPM0->CONTROLS[3].CnV=30;	//wypelnienie 30%
	TPM0->SC|=TPM_SC_CMOD(1); 	//wlaczenie TPM0
	TPM1->CONTROLS[0].CnV=30;	//wypelnienie 30%
	TPM1->SC|=TPM_SC_CMOD(1);	//wlaczenie TPM1
}

//jazda do tylu
void backwardsMotors(void)
{
	FPTA->PSOR = 1<<10;
	FPTB->PSOR = 1<<11;		//kierunek obrotu kol (do tylu)
	TPM0->CONTROLS[3].CnV=TPM1->CONTROLS[0].CnV=20; //wypelnienie 20%
	TPM0->SC|=TPM_SC_CMOD(1);
	TPM1->SC|=TPM_SC_CMOD(1);
}

//skret w lewo
void turnLeft(void)
{
	FPTA->PCOR = 1<<10;
	FPTB->PCOR = 1<<11;
	TPM0->CONTROLS[3].CnV=30;
	TPM1->CONTROLS[0].CnV=10;
	TPM0->SC|=TPM_SC_CMOD(1);
	TPM1->SC|=TPM_SC_CMOD(1);
}

//skret w prawo
void turnRight(void)
{
	FPTA->PCOR = 1<<10;
	FPTB->PCOR = 1<<11;
	TPM0->CONTROLS[3].CnV=10;
	TPM1->CONTROLS[0].CnV=30;
	TPM0->SC|=TPM_SC_CMOD(1);
	TPM1->SC|=TPM_SC_CMOD(1);
}

//inicjalizacja krancowek
void limitSwitchInitialize(void)
{
	PORTA->PCR[LEFT_SWITCH]|=PORT_PCR_MUX(1);
	PORTA->PCR[LEFT_SWITCH]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTA->PCR[LEFT_SWITCH]|=PORT_PCR_IRQC(11);	 //pin, do ktorego zostala podlaczona krancowka, jako wejscie z aktywnym przerwaniem
	
	PORTB->PCR[RIGHT_SWITCH]|=PORT_PCR_MUX(1);
	PORTB->PCR[RIGHT_SWITCH]|=PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTB->PCR[RIGHT_SWITCH]|=PORT_PCR_IRQC(11);
}

//obsluga lewej krancowki
int32_t limitSwitchLeftHandler(void)
{
	return FPTA->PDIR&(1UL<<LEFT_SWITCH); //odczyt za pomoca rejestrow szybkiego dostepu
}

//obsluga prawej krancowki
int32_t limitSwitchRightHandler(void)
{
	return FPTB->PDIR&(1UL<<RIGHT_SWITCH);
}