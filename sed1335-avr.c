/*----------------------------------------------------------------------------
 Author:         Sven Sperner	<cethss@gmail.com>
 Remarks:        
 known Problems: GLCD_SetPixel fehlerhaft!
 Version:        05.10.2008
 Description:    SED1335-Routinen
----------------------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define SED1335_DATA_PORT	PORTA
#define SED1335_DATA_DIR	DDRA
#define SED1335_DATA_PIN	PINA

#define SED1335_CONTROL_PORT	PORTC
#define SED1335_CONTROL_DIR	DDRC
#define	SED1335_CONTROL_PIN	PINC

#define SED1335_RES		(1 << PC0)
#define SED1335_RD		(1 << PC1)
#define SED1335_WR		(1 << PC2)
#define SED1335_CS		(1 << PC3)
#define SED1335_A0		(1 << PC4)
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_InitPorts(void)
{
SED1335_DATA_DIR = 0xFF;
SED1335_CONTROL_PORT |= (SED1335_A0 | SED1335_WR | SED1335_RD | SED1335_CS | SED1335_RES); 
SED1335_CONTROL_DIR |= (SED1335_A0 | SED1335_WR | SED1335_RD | SED1335_CS | SED1335_RES); 
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
SED1335_DATA_PORT = dataToWrite;
SED1335_DATA_DIR = 0xFF;
SED1335_CONTROL_PORT &= ~(SED1335_CS | SED1335_A0 | SED1335_WR);
asm("nop");
SED1335_CONTROL_PORT |= (SED1335_CS | SED1335_A0 | SED1335_WR);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite)
{
SED1335_DATA_PORT = commandToWrite;
SED1335_DATA_DIR = 0xFF;
SED1335_CONTROL_PORT &= ~(SED1335_CS |SED1335_WR);
asm("nop");
SED1335_CONTROL_PORT |= (SED1335_CS | SED1335_WR);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
SED1335_CONTROL_PORT &= ~(SED1335_CS | SED1335_RD);
asm("nop");
SED1335_DATA_DIR = 0x00;
asm("nop");
tmp =  SED1335_DATA_PIN;
SED1335_CONTROL_PORT |= (SED1335_CS | SED1335_RD);
return tmp;
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadByteFromROMMemory(unsigned char * ptr)
{
return pgm_read_byte(ptr);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

