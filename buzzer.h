#ifndef BUZZER_H_
#define BUZZER_H_

/* defining the logic of the led connection in the buzzer */
#define postive_logic

#ifdef postive_logic
#define LOW 0
#define HIGH 1
#elif negative_logic
#define LOW 1
#define HIGH 0
#endif

#define buzzer_PORTID PORTC_ID  // define the port ID of the buzzer led
#define buzzer_PINID  PIN5_ID   // define the pin ID of the buzzer led
/* Function declaration for the buzzer led*/
void buzzer_init();
void buzzer_on();
void buzzer_off();
#endif /* BUZZER_H_ */
