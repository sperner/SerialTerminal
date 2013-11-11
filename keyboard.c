/*----------------------------------------------------------------------------
 Author:         Sven Sperner	<cethss@gmail.com>
 Remarks:        
 known Problems: fehlende Special-Keys
 Version:        05.10.2008
 Description:    PS/2-Keyboard Scancode-Umwandlungen
----------------------------------------------------------------------------*/
#include "keyboard.h"

char decodeFunctionKey(int code) {
	switch (code) {
		case 0x01: return KEY_F9; break;
		case 0x03: return KEY_F5; break;
		case 0x04: return KEY_F3; break;
		case 0x05: return KEY_F1; break;
		case 0x06: return KEY_F2; break;
		case 0x07: return KEY_F12; break;
		case 0x09: return KEY_F10; break;
		case 0x0a: return KEY_F8; break;
		case 0x0b: return KEY_F6; break;
		case 0x0c: return KEY_F4; break;
		case 0x0d: return KEY_TAB; break;
		case 0x11: return KEY_ALT; break;
		case 0x12: return KEY_SHIFTl; break;
		case 0x14: return KEY_STRGl; break;
		case 0x29: return KEY_SPACE; break;
		case 0x58: return KEY_CAPS; break;
		case 0x59: return KEY_SHIFTr; break;
		case 0x5a: return KEY_RETURN; break;
		case 0x66: return KEY_BACKSPACE; break;
		case 0xe0: return KEY_ENTER; break;
		case 0xe1: return KEY_PAUSE; break;
		case 0x76: return KEY_ESC; break;
		case 0x77: return KEY_NUM; break;
		case 0x78: return KEY_F11; break;
		case 0x7e: return KEY_ROLLEN; break;
		case 0x83: return KEY_F7; break;
	}
	return 0;
}

char decodeChar(int code) {
	switch (code) {
		case 0x0d: return 0x09; break; //TAB(horizontalTab)
		case 0x0e: return '^'; break;
		case 0x15: return 'q'; break;
		case 0x16: return '1'; break;
		case 0x1a: return 'y'; break;
		case 0x1b: return 's'; break;
		case 0x1c: return 'a'; break;
		case 0x1d: return 'w'; break;
		case 0x1e: return '2'; break;
		case 0x21: return 'c'; break;
		case 0x22: return 'x'; break;
		case 0x23: return 'd'; break;
		case 0x24: return 'e'; break;
		case 0x25: return '4'; break;
		case 0x26: return '3'; break;
		case 0x29: return 0x20; break; //SPACE(Space)
		case 0x2a: return 'v'; break;
		case 0x2b: return 'f'; break;
		case 0x2c: return 't'; break;
		case 0x2d: return 'r'; break;
		case 0x2e: return '5'; break;
		case 0x31: return 'n'; break;
		case 0x32: return 'b'; break;
		case 0x33: return 'h'; break;
		case 0x34: return 'g'; break;
		case 0x35: return 'z'; break;
		case 0x36: return '6'; break;
//	 	case 0x39: return ';'; break;
		case 0x3a: return 'm'; break;
		case 0x3b: return 'j'; break;
		case 0x3c: return 'u'; break;
		case 0x3d: return '7'; break;
		case 0x3e: return '8'; break;
		case 0x41: return ','; break;
		case 0x42: return 'k'; break;
		case 0x43: return 'i'; break;
		case 0x44: return 'o'; break;
		case 0x45: return '0'; break;
		case 0x46: return '9'; break;
		case 0x49: return '.'; break;
		case 0x4a: return '-'; break;
		case 0x4b: return 'l'; break;
		case 0x4c: return 'ö'; break;
		case 0x4d: return 'p'; break;
		case 0x4e: return 'ß'; break;
		case 0x52: return 'ä'; break;
		case 0x54: return 'ü'; break;
		case 0x55: return '`'; break;
		case 0x5a: return 0x0d; break; //RETURN(CarriageReturn)
		case 0x5b: return '+'; break;
		case 0x5d: return '#'; break;
		case 0x61: return '<'; break;
		case 0x66: return 0x08; break; //BACKSPACE(Backspace)
		case 0x69: return '1'; break;
		case 0x6b: return '4'; break;
		case 0x6c: return '7'; break;
		case 0x70: return '0'; break;
		case 0x71: return ','; break;
		case 0x72: return '2'; break;
		case 0x73: return '5'; break;
		case 0x74: return '6'; break;
		case 0x75: return '8'; break;
		case 0x76: return 0x1b; break; // ESC(Escape)
		case 0x79: return '+'; break;
		case 0x7a: return '3'; break;
		case 0x7b: return '-'; break;
		case 0x7c: return '*'; break;
		case 0x7d: return '9'; break;
		case 0xe0: return 0x0a; break; //ENTER(NewLine)
	}
	return 0;
}

char decodeShiftedChar(int code) {
	switch (code) {
		case 0x0d: return 0x09; break; //TAB(horizontalTab)
		case 0x0e: return '°'; break;
		case 0x15: return 'Q'; break;
		case 0x16: return '!'; break;
		case 0x1a: return 'Y'; break;
		case 0x1b: return 'S'; break;
		case 0x1c: return 'A'; break;
		case 0x1d: return 'W'; break;
		case 0x1e: return '"'; break;
		case 0x21: return 'C'; break;
		case 0x22: return 'X'; break;
		case 0x23: return 'D'; break;
		case 0x24: return 'E'; break;
		case 0x25: return '$'; break;
		case 0x26: return '§'; break;
		case 0x29: return 0x20; break; //SPACE(Space)
		case 0x2a: return 'V'; break;
		case 0x2b: return 'F'; break;
		case 0x2c: return 'T'; break;
		case 0x2d: return 'R'; break;
		case 0x2e: return '%'; break;
		case 0x31: return 'N'; break;
		case 0x32: return 'B'; break;
		case 0x33: return 'H'; break;
		case 0x34: return 'G'; break;
		case 0x35: return 'Z'; break;
		case 0x36: return '&'; break;
//	 	case 0x39: return ';'; break;
		case 0x3a: return 'M'; break;
		case 0x3b: return 'J'; break;
		case 0x3c: return 'U'; break;
		case 0x3d: return '/'; break;
		case 0x3e: return '('; break;
		case 0x41: return ';'; break;
		case 0x42: return 'K'; break;
		case 0x43: return 'I'; break;
		case 0x44: return 'O'; break;
		case 0x45: return '='; break;
		case 0x46: return ')'; break;
		case 0x49: return ':'; break;
		case 0x4a: return '_'; break;
		case 0x4b: return 'L'; break;
		case 0x4c: return 'Ö'; break;
		case 0x4d: return 'P'; break;
		case 0x4e: return '?'; break;
		case 0x52: return 'Ä'; break;
		case 0x54: return 'Ü'; break;
		case 0x55: return '`'; break;
		case 0x5a: return 0x0d; break; //RETURN(CarriageReturn)
		case 0x5b: return '*'; break;
		case 0x5d: return '\''; break;
		case 0x61: return '>'; break;
		case 0x66: return 0x08; break; //BACKSPACE(Backspace)
		case 0x69: return '1'; break;
		case 0x6b: return '4'; break;
		case 0x6c: return '7'; break;
		case 0x70: return '0'; break;
		case 0x71: return ','; break;
		case 0x72: return '2'; break;
		case 0x73: return '5'; break;
		case 0x74: return '6'; break;
		case 0x75: return '8'; break;
		case 0x76: return 0x1b; break; // ESC(Escape)
		case 0x79: return '+'; break;
		case 0x7a: return '3'; break;
		case 0x7b: return '-'; break;
		case 0x7c: return '*'; break;
		case 0x7d: return '9'; break;
		case 0xe0: return 0x0a; break; //ENTER(NewLine)
	}
	return 0;
}

char decodeAlteredChar(int code) {
	switch (code) {
		case 0x0d: return 0x09; break; //TAB(horizontalTab)
		case 0x0e: return '¬'; break;
		case 0x15: return '@'; break;
		case 0x16: return '¹'; break;
		case 0x1a: return '«'; break;
		case 0x1b: return 'ß'; break;
		case 0x1c: return 'æ'; break;
		case 0x1d: return '?'; break;
		case 0x1e: return '²'; break;
		case 0x21: return '¢'; break;
		case 0x22: return '»'; break;
		case 0x23: return 'ğ'; break;
		case 0x24: return '?'; break;
		case 0x25: return '\\'; break;
		case 0x26: return '³'; break;
		case 0x29: return 0x20; break; //SPACE(Space)
		case 0x2a: return '?'; break;
		case 0x2b: return '?'; break;
		case 0x2c: return '?'; break;
		case 0x2d: return '¶'; break;
		case 0x2e: return '½'; break;
		case 0x31: return 'n'; break;
		case 0x32: return '?'; break;
		case 0x33: return '?'; break;
		case 0x34: return '?'; break;
		case 0x35: return '?'; break;
		case 0x36: return '¬'; break;
//	 	case 0x39: return ';'; break;
		case 0x3a: return 'µ'; break;
		case 0x3b: return 'j'; break;
		case 0x3c: return '?'; break;
		case 0x3d: return '{'; break;
		case 0x3e: return '['; break;
		case 0x41: return '?'; break;
		case 0x42: return '?'; break;
		case 0x43: return '?'; break;
		case 0x44: return 'ø'; break;
		case 0x45: return '}'; break;
		case 0x46: return ']'; break;
		case 0x49: return '·'; break;
		case 0x4a: return '_'; break;
		case 0x4b: return '?'; break;
		case 0x4c: return 'Ö'; break;
		case 0x4d: return 'ş'; break;
		case 0x4e: return '\\'; break;
		case 0x52: return '^'; break;
		case 0x54: return '"'; break;
		case 0x55: return '`'; break;
		case 0x5a: return 0x0d; break; //RETURN(CarriageReturn)
		case 0x5b: return '~'; break;
		case 0x5d: return '`'; break;
		case 0x61: return '|'; break;
		case 0x66: return 0x08; break; //BACKSPACE(Backspace)
		case 0x69: return '1'; break;
		case 0x6b: return '4'; break;
		case 0x6c: return '7'; break;
		case 0x70: return '0'; break;
		case 0x71: return ','; break;
		case 0x72: return '2'; break;
		case 0x73: return '5'; break;
		case 0x74: return '6'; break;
		case 0x75: return '8'; break;
		case 0x76: return 0x1b; break; // ESC(Escape)
		case 0x79: return '+'; break;
		case 0x7a: return '3'; break;
		case 0x7b: return '-'; break;
		case 0x7c: return '*'; break;
		case 0x7d: return '9'; break;
		case 0xe0: return 0x0a; break; //ENTER(NewLine)
	}
	return 0;
}
