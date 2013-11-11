/*----------------------------------------------------------------------------
 Author:         Sven Sperner	<cethss@gmail.com>
 Remarks:        
 known Problems: 
 Version:        28.06.2009
 Description:    Serial Console/Terminal to LCD-Adapter
		 connect Server, Router or whatever a Serial Console features 
		 to a LC-Display as primary Console Output (Grub,Linux,...)
		 using Jan Pieter de Ruiter PS/2 code
----------------------------------------------------------------------------*/
/*	LCD-Pin         	connected to
	'1        /RESET	PortC.0
	'2        /RD   	PortC.1
	'3        /WR		PortC.2
	'4        /CS		PortC.3
	'5        A0		PortC.4
	'6-13     DB0-DB7	PortA
	'14       VCC 		+5V
	'15       VSS 		GND
	'16       VCTL		PortD.5 (PWM) oder +5V<-3,9kOhm-X-390Ohm->GND
	'17	  A		PortD.4 (PWM) oder +5V<-75Ohm
	'18	  K		GND */
/* x |= (1 << Bitnummer);  // Hiermit wird ein Bit in x gesetzt
   x &= ~(1 << Bitnummer); // Hiermit wird ein Bit in x geloescht */

/* CPU/Quarz Frequenz in Mhz, wenn nicht im Makefile definiert */
#ifndef F_CPU
  #define F_CPU	8000000UL	// 8MHz interner Oszillator
#endif

#define UART_BAUD_RATE	19200	// 19200 Baud für UART

#define DEBUG 0

/* notwendige Header einbinden */
#include <avr/io.h>		// Ports,Pins,etc.
#include <avr/interrupt.h>	// Interrupts
#include <stdio.h>	     	// sprintf(),
#include <stdlib.h>     	// rand(), atoi()
#include <string.h>		// strings handeln
#include <util/delay.h>		// _delay_ms()
#include <inttypes.h>
#include "sed1335.h"		// grafik LCD
#include "uart.h"		// RS-232
#include "ps2.h"		// PS2-Keyboard
#include "keyboard.h"		// Key-/Scancodes


/* Delay/Sleep Funktion */
void delay_ms(int ms) {
  int t;
  for(t=0; t<=ms; t++)
	_delay_ms(1); 
}


/* Hauptprogramm */
int main(void)
{
  unsigned int address;						//Cursor-Adresse des LCDs
  char column=0;						//Cursor Spalte, 0-39
  char row=0;							//Cursor Reihe,  0-28

  unsigned int uart_in;						//UART Zeichenspeicher
  char buffer[5];						//UART Stringspeicher

  char code;							//Tastendruck ScanCode
  char key;							//Tastendruck ASCII-Code

    #if DEBUG
	DDRB = 0x0F;
	PORTB = 0;
    #endif


    /* initialisiere LCD */
    GLCD_Initialize();
    GLCD_ClearText();
    GLCD_ClearGraphic();
    DDRD |= 0x30;						//OC1A+OC1B -> Ausgänge
    TCCR1A = (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1);		//Standard-PWM...
    TCCR1B = (1<<CS10);
    OCR1A=26;							//Kontrast
    OCR1B=100;							//Hintergrundbeleuchtung

    /* initialisiere UART */
    sei();							//globale Interrupts einschalten
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 	//initialisieren mit Baud und CPU-MHz

    #if DEBUG
	GLCD_TextGoTo( column, row ); column=0; row+=2;;
	GLCD_WriteText( "AtMega16 SerCon->gLCD is up and running!" );
	uart_puts_P( "UART0 is up and running!\n\r" );
    #endif


    /* Hauptschleife */
    for( ;; )
    {
	//uart_putc( '!' );
        uart_in = uart_getc();					//Daten von UART empfangen
        if( uart_in & UART_NO_DATA ) {				//keine Daten von UART verfügbar

	    /* Hauptteil der Tastatur-Behandlung */
	    if( ((CLKPIN & (1<<CLK)) == 0) ) {
		#if DEBUG
		    PORTB |= (1 << 2);
		#endif
		code = Read_ps2data();
		#if DEBUG
		    sprintf(buffer, "0x%x ", code);
		    GLCD_WriteText( buffer );
		    ///uart_puts( buffer );
		#endif
		key = decodeFunctionKey( code );
		if( key > 0 ) {					//Spezialtasten auswerten
		    switch( key ) {
			case KEY_ALT:		while( key == KEY_ALT) {
						    code = Read_ps2data();
						    key = decodeFunctionKey( code );
						}
						key = decodeAlteredChar(code);
						sprintf(buffer, "%c", key);
						uart_puts( buffer );
					break;
			case KEY_ENTER:		column=0;
						GLCD_TextGoTo( column, ++row );
						uart_puts( "\n\r" );
					break;
			case KEY_F1:		uart_puts_P( "apt-get update\n\r" );
					break;
			case KEY_F2:		uart_puts_P( "apt-get upgrade\n\r" );
					break;
			case KEY_F3:		uart_puts_P( "apt-get dist-upgrade\n\r" );
					break;
			case KEY_F4:		uart_puts_P( "apt-get autoremove && apt-get autoclean && apt-get clean\n\r" );
					break;
			case KEY_F5:		if( OCR1A < 30 )
						    OCR1A++;
					break;
			case KEY_F6:		if( OCR1A > 20 )
						    OCR1A--;
					break;
			case KEY_F7:		if( OCR1B < 150 )
						    OCR1B+=5; 
					break;
			case KEY_F8:		if( OCR1B >= 5 )
						    OCR1B-=5; 
					break;
			#if DEBUG
			    case KEY_F11:	    uart_puts_P( "user\n\r" );
						    delay_ms(1000);
						    uart_puts_P( "password\n\r" );
					    break;
			#endif
			case KEY_F12:		uart_putc( ' ' );
					break;
/*			case KEY_NUM:		PORTB |= (1 << 0);
						Write_ps2data( 0xED );
						sprintf(buffer, "-0x%x- ", Read_ps2data());
						GLCD_WriteText( buffer );
						Write_ps2data( 0x2 );
						PORTB &= ~(1 << 0);
					break;
*/			case KEY_RETURN:	column=0;
						GLCD_TextGoTo( column, ++row );
						uart_putc( 0x0d );
					break;
			case KEY_SHIFTl:	//Shift-l nimmt auch die folgenden Zeilen...
			case KEY_SHIFTr:	while( key == KEY_SHIFTl || key == KEY_SHIFTr) {
						    code = Read_ps2data();
						    key = decodeFunctionKey( code );
						}
						key = decodeShiftedChar(code);
						sprintf(buffer, "%c", key);
						uart_puts( buffer );
					break;
			default:		key = decodeChar(code);
						sprintf(buffer, "%c", key);
						uart_puts( buffer );
					break;
		    }
		}
		else {						//Standardtasten auswerten
		    key = decodeChar(code);
		    sprintf(buffer, "%c", key);
		    uart_puts( buffer );
		}
		#if DEBUG
		    PORTB &= ~(1 << 2);
		#endif
		delay_ms(50);					//"entprellen"
	    }
        }
        else {							//Daten von UART verfügbar
	    #if DEBUG
		PORTB |= (1 << 3);
	    #endif
	    if( uart_in & UART_FRAME_ERROR ) {			//Rahmen-Fehler erkannt
		GLCD_TextGoTo( 0, 0 );
		GLCD_WriteText( "UART Frame Error " );
	    }
	    if( uart_in & UART_OVERRUN_ERROR ) {		//...Über???? erkannt
		GLCD_TextGoTo( 0, 0 );
		GLCD_WriteText( "UART Overrun Error " );
	    }
	    if( uart_in & UART_BUFFER_OVERFLOW ) {		//...Überlauf erkannt
		GLCD_TextGoTo( 0, 0 );
		GLCD_WriteText( "UART Buffer overflow " );
	    }

	    /* Hauptteil der Terminal-Ausgabe */
	    switch( uart_in ) {					//empf. Zeichen prüfen
		case 0x8:	GLCD_TextGoTo( --column, row );	//BACKSPACE
				GLCD_WriteText( " " );
			break;
		case 0xa:	row++;				//NewLine / LF
			break;
		case 0xd:	column=0;			//CarriageReturn
			break;
		default:	GLCD_TextGoTo( column++, row );
				sprintf(buffer, "%c", uart_in);
				GLCD_WriteText( buffer );
			break;
	    }
	    if( column > 39 && row == 27 ) {			//Ende in letzter Zeile...
		GLCD_Scroll();
		column=1;
	    }
	    else {
		if( column > 39 ) {				//bei Ende der Zeile...
		    column=1;
		    row++;
		}
		else if( row > 27 ) {				//wenn in letzter Zeile...
		    GLCD_Scroll();
		    column=0;
		    row--;
		}
	    }
	    GLCD_TextGoTo( column, row );			//Cursor positionieren
	    #if DEBUG
		PORTB &= ~(1 << 3);
	    #endif

/*
	    GLCD_TextGoTo( 0, 0 );
	    GLCD_WriteText( "UART_in: " );
	    sprintf(buffer, "0x%x  ", uart_in);
	    GLCD_WriteText( buffer );
*/

        }//if(uart_in &UART_NO_DATA)

    }//for(;;)
    
}//main(void)
