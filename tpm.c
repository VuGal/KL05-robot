#include "MKL05Z4.h"
#include "tpm.h"

//inicjalizacja TPM0 PTB6 - TPM0_CH3, PTA12 - TPM1_CH0
void tpm0Initialize(void)
{
	MCG->C1 |= MCG_C1_IRCLKEN_MASK|MCG_C1_IREFS_MASK;								// ustawienie 'Multipurpose Clock Generator', uzywamy wewnetrznego zegara
	SIM->SCGC6|=SIM_SCGC6_TPM0_MASK;												// zegar podlaczony do TPM0
	SIM->SOPT2|=SIM_SOPT2_TPMSRC(1);												// wybor zegara dla TPM0, w naszym przypadku to MCGFLLCLK 'Multipurpose Clock Generator Frequency Locked Loop Clock'
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);												// wylaczony zegar
	TPM0->SC = TPM_SC_PS(3); 														// prescaler
	TPM0->MOD = 100;																// wartosc modulo = 100
	
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;												//podpiecie zegara do portu B
	PORTB->PCR[6] = PORT_PCR_MUX(2);												
	FPTB->PDDR = 1UL<<6;														    //PTB6 jako wyjscie TPM0_CH3 (PWM oparty na zegarze TPM0)
	PORTB->PCR[11] = PORT_PCR_MUX(1);												
	FPTB->PDDR = 1UL<<11;
	FPTB->PCOR = 1UL<<11;														    //PTB11 jako wyjscie dla DIR (sterowania kierunkiem obrotu silnika)
	TPM0->CONTROLS[3].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;					//wlaczenie trybu 'Edge Aligned PWM' EPMW, na kanale 3 TMP0
	TPM0->CONTROLS[3].CnV = 20;														//wartosc CnV odpowiada za szerokosc impulsu (czyli w tym przypadku wypelnienie 20%)
	
	TPM0->SC|=TPM_SC_CMOD(1);														//wlaczenie timera TPM0
	//A_PWM
}

//inicjalizacja TPM1
void tpm1Initialize(void)
{
	MCG->C1 |= MCG_C1_IRCLKEN_MASK|MCG_C1_IREFS_MASK;					// ustawienie 'Multipurpose Clock Generator', uzywamy wewnetrznego zegara
	SIM->SCGC6|=SIM_SCGC6_TPM1_MASK;									// zegar podlaczony do TPM1
	SIM->SOPT2|=SIM_SOPT2_TPMSRC(1);									// wybor zegara dla TPM1, w naszym przypadku to MCGFLLCLK 'Multipurpose Clock Generator Frequency Locked Loop Clock'
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);									// wylaczony zegar
	TPM1->SC = TPM_SC_PS(3);											// prescaler
	TPM1->MOD = 100;													// wartosc modulo = 100
	
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;									//podpiecie zegara do portu A
	PORTA->PCR[12] = PORT_PCR_MUX(2);
	FPTA->PDDR = 1UL<<12;												//PTA12 jako wyjscie TPM1_CH0 (PWM oparty na zegarze TPM1)
	PORTA->PCR[10] = PORT_PCR_MUX(1);
	FPTA->PDDR = 1UL<<10;
	FPTA->PCOR = 1UL<<10;												//PTA10 jako wyjscie dla DIR (sterowania kierunkiem obrotu silnika)
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;		//wlaczenie trybu 'Edge Aligned PWM' (EPWM) na kanale 0 TMP1
	TPM1->CONTROLS[0].CnV = 20;											//wartosc CnV odpowiada za szerokosc impulsu (czyli w tym przypadku wypelnienie 20%)
	
	TPM1->SC|=TPM_SC_CMOD(1);											//wlaczenie timera TPM1
	//B_PWM
	
}
