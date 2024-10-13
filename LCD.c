#include "LCD.h"
#include"gpio.h"
#include"common_macros.h"
#include<util/delay.h>
/* Driver responsible to configure the LCD controller
 * set of commands and enables for the LCD pins and data paths
 */


void LCD_Init(void){
	/* LCD initialization of the pins and configure them
	 * setting the pins as output to enable the screen display
	 */
	GPIO_setupPinDirection(LCD_RS_PORTID,LCD_RS_PINID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_Enable_PORTID,LCD_Enable_PINID,PIN_OUTPUT);
	GPIO_setupPortDirection(LCD_dataPath_PORTID,PORT_OUTPUT);
	_delay_ms(20);
#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_dataPath_PORTID,LCD_DB4_PINID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_dataPath_PORTID,LCD_DB5_PINID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_dataPath_PORTID,LCD_DB6_PINID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_dataPath_PORTID,LCD_DB7_PINID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(twoLine4bit_init1);
	LCD_sendCommand(twoLine4bit_init2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(twoLine4bit_mode);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_dataPath_PORTID,PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(twoLine8bit_mode);

#endif
	LCD_sendCommand(cursor_off);
	LCD_sendCommand(clear_command);
}


void LCD_sendCommand(uint8 command){
	/*Function sending command to the data paths of LCD
	 * to ease set the command on the LCD pin
	 */
	GPIO_writePin(LCD_RS_PORTID,LCD_RS_PINID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB4_PINID,GET_BIT(command,4));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB5_PINID,GET_BIT(command,5));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB6_PINID,GET_BIT(command,6));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB7_PINID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB4_PINID,GET_BIT(command,0));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB5_PINID,GET_BIT(command,1));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB6_PINID,GET_BIT(command,2));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB7_PINID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_dataPath_PORTID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}


/* Function used to send a character to be displayed on the LCD*/
void LCD_displayChar(uint8 data){
	GPIO_writePin(LCD_RS_PORTID,LCD_RS_PINID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB4_PINID,GET_BIT(data,4));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB5_PINID,GET_BIT(data,5));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB6_PINID,GET_BIT(data,6));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB7_PINID,GET_BIT(data,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB4_PINID,GET_BIT(data,0));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB5_PINID,GET_BIT(data,1));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB6_PINID,GET_BIT(data,2));
	GPIO_writePin(LCD_dataPath_PORTID,LCD_DB7_PINID,GET_BIT(data,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_dataPath_PORTID,data); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_Enable_PORTID,LCD_Enable_PINID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}
// Function used to display a whole string in the LCD
void LCD_displayString(const char *str){
	uint8 i=0;
	while (str[i]!='\0'){
		LCD_displayChar(str[i]);
		i++;
	}
}
//Function send the command to clear the whole screen
void LCD_clearScreen(void){
	LCD_sendCommand(clear_command);

}
//Function used to move the cursor to the needed location by row and column
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 lcd_memoryAddress;
	switch(row)
	{
	case 0:
		lcd_memoryAddress=col;
		break;
	case 1:
		lcd_memoryAddress=col+0x40;
		break;
	case 2:
		lcd_memoryAddress=col+0x10;
		break;
	case 3:
		lcd_memoryAddress=col+0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memoryAddress | set_cursorLocation);
}
// Function of multiple usage takes the desired location to set the cursor and displays a string
void LCD_displayStringRowColumn(uint8 row,uint8 col, const char *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}
// function used to change the integers to strings and displays it
void LCD_integerToString(int data){
	char buffer[16];
	itoa(data,buffer,10);
	LCD_displayString(buffer);
}


