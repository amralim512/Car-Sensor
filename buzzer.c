#include"buzzer.h"
#include"gpio.h"
/* Driver responsible for the buzzer initialization
 * turning on the buzzer led
 * turning off the buzzer led
 */
void buzzer_init(){
	// set the pin direction as output for the buzzer
	GPIO_setupPinDirection(buzzer_PORTID,buzzer_PINID,PIN_OUTPUT);
	// initialize the led by off
	GPIO_writePin(buzzer_PORTID,buzzer_PINID,LOW);
}

void buzzer_on(){
	// turn on the buzzer led
	GPIO_writePin(buzzer_PORTID,buzzer_PINID,HIGH);

}
void buzzer_off(){
//	turn off the buzzer led
	GPIO_writePin(buzzer_PORTID,buzzer_PINID,LOW);

}
