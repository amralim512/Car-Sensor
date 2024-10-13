#ifndef LCD_H_
#define LCD_H_
#include"gpio.h"
#define LCD_DATA_BITS_MODE 4
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#define LCD_RS_PORTID PORTA_ID // define the RS port in the LCD driver
#define LCD_RS_PINID  PIN1_ID  // define the RS pin in the LCD driver

#define LCD_Enable_PORTID  PORTA_ID // define the EN port in the LCD driver
#define LCD_Enable_PINID   PIN2_ID  // define the EN pin in the LCD driver
#define LCD_dataPath_PORTID PORTA_ID // define the data path port in the LCD driver

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PINID      PIN3_ID
#define LCD_DB5_PINID      PIN4_ID
#define LCD_DB6_PINID      PIN5_ID
#define LCD_DB7_PINID      PIN6_ID

#endif

// set of commands used by the LCD driver can help in ease of sending the command
#define twoLine8bit_mode 0x38  // define the mode to two line and 8 bits
#define twoLine4bit_mode 0x28
#define twoLine4bit_init1 0x33
#define twoLine4bit_init2 0x32
#define cursor_off 0x0c    // turns off the cursor from the LCD screen
#define cursor_on 0x0E
#define clear_command 0x01  // clear all the screen
#define set_cursorLocation 0x80 // define the location of the cursor
#define go_tohome 0x02



/*Functions Initialization for the used by the driver */
void LCD_sendCommand(uint8 command);
void LCD_Init(void);
void LCD_displayChar(uint8 data);
void LCD_displayString(const char *str);
void LCD_clearScreen(void);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col, const char *str);
void LCD_integerToString(int data);




#endif
