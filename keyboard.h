/*----------------------------------------------------------------------------
 Author:         Sven Sperner	<cethss@gmail.com>
 Remarks:        
 known Problems: fehlende Special-Keys
 Version:        05.10.2008
 Description:    PS/2-Keyboard
----------------------------------------------------------------------------*/
#define KEY_F9 1
#define KEY_F5 2
#define KEY_F3 3
#define KEY_F1 4
#define KEY_F2 5
#define KEY_F12 6
#define KEY_F10 7
#define KEY_F8 8
#define KEY_F6 9
#define KEY_F4 10
#define KEY_TAB 11
#define KEY_ALT 12
#define KEY_SHIFTl 13
#define KEY_STRGl 14
#define KEY_SPACE 15
#define KEY_CAPS 16
#define KEY_SHIFTr 17
#define KEY_RETURN 18
#define KEY_BACKSPACE 19
#define KEY_ENTER 20
#define KEY_PAUSE 21
#define KEY_ESC 22
#define KEY_NUM 23
#define KEY_F11 24
#define KEY_ROLLEN 25
#define KEY_F7 26

char decodeFunctionKey(int);
char decodeChar(int);
// char decodeShiftedChar(int);
