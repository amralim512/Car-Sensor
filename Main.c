#include"buzzer.h"
#include"LCD.h"
#include"LED.h"
#include"ultrasonic.h"
#include"common_macros.h"
#include<avr/io.h>

uint16 distance=0;
int main(void){
	// Initialize all the drivers one by one
	SET_BIT(SREG,7); //enable the SREG for the completion of the interrupt
	LED_init();
	buzzer_init();
	LCD_Init();
	ultrasonic_init();
// Initial display
	LCD_displayString("Distance=    cm");

	while(1){
		distance=ultrasonic_readDistance()+1;// calculate the distance from the sensor
	   //Condition for the correct display of the numbers
		if (distance>=100){
			LCD_moveCursor(0,9);
			LCD_integerToString(distance);
		}
		else{
			LCD_moveCursor(0,9);
			LCD_integerToString(distance);
			LCD_displayChar(' ');
		}

		distance=ultrasonic_readDistance()+1;

		// Our System Requirements set to do all the needed functions

		if(distance<=5){
			LED_BUZZER_mapping();
		}

		else if (distance>5 && distance<=10){
			buzzer_off();
			LCD_displayStringRowColumn(1,0,"               ");
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_on(LED_BLUE);
		}
		else if (distance>10 && distance<=15){
			buzzer_off();
			LCD_displayStringRowColumn(1,0,"                 ");
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_off(LED_BLUE);
		}
		else if (distance>15 && distance<=20){
			buzzer_off();
			LCD_displayStringRowColumn(1,0,"                 ");
			LED_on(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
		else if (distance>20){
			buzzer_off();
			LCD_displayStringRowColumn(1,0,"                 ");
			LED_off(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
	}


}
