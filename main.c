#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#include "MKL05Z4.h"
#include "leds.h"
#include "tpm.h"
#include "motorscontrol.h"
#include "buzzer.h"
#include "switch.h"
#include "sensors.h"
#include "misc.h"


int flag = 0;

int main(void)
{
	tpm0Initialize();
	tpm1Initialize();
	ledsInitialize();
	sensorsInitialize();
	limitSwitchInitialize();
	buzzerInitialize();
	switchInitialize();
	delay(1500);
	
	while(1) {
		
			//przycisk na szczycie robota wcisniety, zakoncz petle glowna
			if ( !switchHandler() ) {
					break;
			}
		
			//tryb jazdy do przodu + skrecanie
			if (flag == 0)
			{
				
				//wykryto przeszkode z przodu, przejdz do trybu cofania
				if ( !sensorReadForward() && switchHandler() ) flag = 1;
				
				//wykryto sciany po bokach oraz brak przeszkody przed robotem, jedz do przodu
				while( sensorReadForward() && !sensorReadLeft() && !sensorReadRight() && flag == 0 && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler() )
				{
						forwardsMotors();	
				}
				
				//wykryto korytarz z prawej strony, wykonaj skret w prawo
				if ( sensorReadForward() && !sensorReadLeft() && sensorReadRight() && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler() )
				{
					while (sensorReadForward() && !(!sensorReadLeft() && !sensorReadRight()) && flag==0 && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler())
					{
						turnRight();
					}
				}
				
				//wykryto korytarz z lewej strony, wykoaj skret w lewo
				if ( sensorReadForward() && sensorReadLeft() && !sensorReadRight() && flag == 0 && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler())
				{
					while (sensorReadForward() && !(!sensorReadLeft() && !sensorReadRight()) && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler())
					{
						turnLeft();
					}
				}
				
				//nie wykryto zadnych scian, jedz do przodu (robot pokonal labirynt)
				while ( sensorReadForward() && sensorReadLeft() && sensorReadRight() && flag == 0 && limitSwitchLeftHandler() && limitSwitchRightHandler() && switchHandler())
				{
					forwardsMotors();
				}
			}
			
			//tryb cofania - czesc pierwsza - cofaj dopoki nie wykryjesz korytarza po boku
			while ( flag == 1 && switchHandler() )
			{
				
				backwardsMotors();
				if ( ( sensorReadLeft() || sensorReadRight() ) && switchHandler()) 
				{
					for(int i = 0; i<5000; ++i){} //poprawia dzialanie programu (wniosek po testach empirycznych)
					flag = 2;
					break;
				}
			}
			
			//tryb cofania - czesc druga - po wykryciu korytarza po boku cofaj, dopoki z powrotem nie wykryjesz scian,
			//umozliwia przygotowanie robota do ponownej jazdy do przodu i skretu w wykryty korytarz
			while ( flag == 2 && switchHandler() ) 
			{
					backwardsMotors();
					if ( ( !sensorReadLeft() && !sensorReadRight() ) && switchHandler() )
					{
						for(int i=0; i<5000; ++i){}	//poprawia dzialanie programu (wniosek po testach empirycznych)
						flag=0;
						break;
					}
			}
			
			//lewa krancowka wcisnieta - wykryto przeszkode po prawej (krancowki zamontowane na skos),
			//wycofaj i wykonaj lekka korekte jazdy w lewo
			if	( !limitSwitchLeftHandler() && switchHandler() )
			{
				buzzerHandler();
				for(int i=0; i<500000; ++i) backwardsMotors();
				for(int i=0; i<250000; ++i) turnLeft();
			}
			
			//prawa krancowka wcisnieta - wykryto przeszkode po lewej (krancowki zamontowane na skos),
			//wycofaj i wykonaj lekka korekte jazdy w lewo
			if ( !limitSwitchRightHandler() && switchHandler() )
			{
				buzzerHandler();
				for(int i=0; i<500000; ++i) backwardsMotors();
				for(int i=0; i<250000; ++i) turnRight();
			} 
	}
	
	//po wylaczeniu silnikow przyciskiem wydaj dzwiek i zamrugaj diodami (koniec dzialania programu)
	buzzerHandler();
}
