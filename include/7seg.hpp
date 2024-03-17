#ifndef CJ_7SEG
#define CJ_7SEG

#define SevenSegCC1 11
#define SevenSegCC2 10

#define SevenSegA 26
#define SevenSegB 27
#define SevenSegC 29
#define SevenSegD 18
#define SevenSegE 25
#define SevenSegF 7
#define SevenSegG 28
#define SevenSegDP 24

void init7Seg();

void sevSegDisplay(int n);

void sevSegLeftDigit(short on);
//0 for off, 1 for on
void sevSegRightDigit(short on);
void writeDigit(short n);

#endif