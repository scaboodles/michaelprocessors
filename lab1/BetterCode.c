#include <avr/io.h>



unsigned char read_keypad(void) {
	
	unsigned char x;

	DDRA = 0b11110000;

	PORTA = 0b10111111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00000100) == 0){ 
		return '4';
	} if ((x & 0b00000010) == 0){
		 return '1';
	} if ((x & 0b00001000) == 0) {
		return '7';
	}

	PORTA = 0b11011111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00000100) == 0){ 
		return '5';
	} if ((x & 0b00000010) == 0){ 
		return '2';
	} if ((x & 0b00001000) == 0){ 
		return '8';
	} if ((x & 0b00000001) == 0){
		 return '0';
	}

	PORTA = 0b11101111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00000100) == 0){
		 return '6';
	} if ((x & 0b00000010) == 0){ 
		return '3';
	} if ((x & 0b00001000) == 0) {
		return '9';
	}
	return 0;
	
}

void display_7led(unsigned char k) {
	if (k == '0') PORTB = 0b11000000;
	else if (k == '1'){ 
		PORTB = 0b11111001;
		} else if (k == '2'){ 
		PORTB = 0b10100100;
		} else if (k == '3'){ 
		PORTB = 0b10110000;
		} else if (k == '4') {
		PORTB = 0b10011001;
		} else if (k == '5') {
		PORTB = 0b10010010;
		} else if (k == '6'){ 
		PORTB = 0b10000010;
		} else if (k == '7'){ 
		PORTB = 0b11111000;
		} else if (k == '8'){ 
		PORTB = 0b10000000;
		} else if (k == '9'){ 
		PORTB = 0b10010000;
		} else {
		PORTB = 0b11111111;
		}
}

int main(void) {
	DDRA = 0xF0;
	DDRB = 0x00;

	while (1) {
		unsigned char k = read_keypad();
		display_7led(k);
	}
}
