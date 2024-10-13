#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"std_types.h"
#include"gpio.h"
#include"icu.h"
#include"LED.h"
#include"LCD.h"
#include"buzzer.h"

#define trigger_PORTID PORTD_ID  // Define the port ID of the trigger
#define trigger_PINID   PIN7_ID // Define the pin ID of the trigger


#define TIME_CONSTANT 117.6 // constant value used to calculate the distance

//Function Declaration used in the driver
void ultrasonic_init(void);
void ultrasonic_trigger(void);
uint16 ultrasonic_readDistance(void);
void ultrasonic_edgeProcessing(void);
void LED_BUZZER_mapping(void);

#endif /* ULTRASONIC_H_ */
