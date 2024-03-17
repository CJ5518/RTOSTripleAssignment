
#include "Arduino.h"
#include "7seg.hpp"

//0 for off, 1 for on
void sevSegLeftDigit(short on) {
	pinMode(SevenSegCC1, on);
}
//0 for off, 1 for on
void sevSegRightDigit(short on) {
	pinMode(SevenSegCC2, on);
}

void init7Seg() {
  pinMode(SevenSegA, OUTPUT);
  pinMode(SevenSegB, OUTPUT);
  pinMode(SevenSegC, OUTPUT);
  pinMode(SevenSegD, OUTPUT);
  pinMode(SevenSegE, OUTPUT);
  pinMode(SevenSegF, OUTPUT);
  pinMode(SevenSegG, OUTPUT);
  pinMode(SevenSegDP, OUTPUT);
  pinMode(SevenSegCC1, OUTPUT);
  pinMode(SevenSegCC2, OUTPUT);

	//digitalWrite(SevenSegCC1, LOW);
  digitalWrite(SevenSegCC2, LOW);
  digitalWrite(SevenSegA, HIGH);
}

//Switch statement could have been good but whatever
void writeDigit(short n) {
	if (n == 0) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 0);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 1) {
		digitalWrite(SevenSegA, 0);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 0);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 0);
		digitalWrite(SevenSegG, 0);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 2) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 0);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 0);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 3) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 0);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 4) {
		digitalWrite(SevenSegA, 0);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 0);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 5) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 6) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 7) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 0);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 0);
		digitalWrite(SevenSegG, 0);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 8) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 9) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 0);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xA) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 0);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xB) {
		digitalWrite(SevenSegA, 0);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xC) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 0);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 0);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xD) {
		digitalWrite(SevenSegA, 0);
		digitalWrite(SevenSegB, 1);
		digitalWrite(SevenSegC, 1);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 0);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xE) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 0);
		digitalWrite(SevenSegD, 1);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	} else if (n == 0xF) {
		digitalWrite(SevenSegA, 1);
		digitalWrite(SevenSegB, 0);
		digitalWrite(SevenSegC, 0);
		digitalWrite(SevenSegD, 0);
		digitalWrite(SevenSegE, 1);
		digitalWrite(SevenSegF, 1);
		digitalWrite(SevenSegG, 1);
		digitalWrite(SevenSegDP, 0);
	}
}


