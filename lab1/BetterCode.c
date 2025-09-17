#include <avr/io.h>

char read_keypad(void)
{
	unsigned char x;
	PORTB &= 0b11111111;
	/* -------- COL 0 (PA4 LOW) -------- */
	PORTA |= 0b11110000;      // all columns HIGH (idle)
	PORTA &= 0b11101111;      // PA4 LOW, others HIGH
	asm volatile("nop");
	x = PINA & 0b00001111;    // read rows (PA3..PA0)

	if ((x & 0b00001000) == 0) {
            return '1';
	}else if ((x & 0b00000100) == 0) {
            return '4';
	}else if ((x & 0b00000010) == 0) {
            return '7';
	}


	/* -------- COL 1 (PA5 LOW) -------- */
	PORTA |= 0b11110000;
	PORTA &= 0b11011111;      // PA5 LOW
	asm volatile("nop");
	x = PINA & 0b00001111;

	if ((x & 0b00001000) == 0) {
            return '2';
	}else if ((x & 0b00000100) == 0) {
            return '5'; 
	}else if ((x & 0b00000010) == 0) {
            return '8';
	}else if ((x & 0b00000001) == 0) {
            return '0';
	}

	/* -------- COL 2 (PA6 LOW) -------- */
	PORTA |= 0b11110000;
	PORTA &= 0b10111111;      // PA6 LOW
	asm volatile("nop");
	x = PINA & 0b00001111;

	if ((x & 0b00001000) == 0) {
            return '3';
	}else if ((x & 0b00000100) == 0) {
            return'6';
	}else if ((x & 0b00000010) == 0){ 
            return '9'; 
	}

	return 'x';
}

	
	

void set_7segment(char x){
	if(x == '0'){
		PORTB = 0b11000000; // 0
	}else if (x == '1'){
		PORTB = b11111001;
	}else if (x == '2'){
		PORTB = 0b10100100;
	}else if (x == '3'){
		PORTB = 0b10110000;
	}else if (x == '4'){
		PORTB = 0b10011001; // 4;
	}else if (x == '5'){
		PORTB = 0b10010010; // 5
	}else if (x == '6'){
		PORTB = 0b10000010; // 6
	}else if (x == '7'){
		PORTB = 0b11111000; // 7
	}else if (x == '8'){
		PORTB = 0b10000000; // 8;
	}else if (x == '9'){
		PORTB = 0b10010000;  // 9
	}else{
		PORTB = 0b11111111;  // all off
	}
}

int main(void) {
	DDRB = 0b11111111;        // Port B: 7-seg outputs
	DDRA = 0b11110000;        // PA7..PA4 outputs (columns), PA3..PA0 inputs (rows)
	PORTA = 0b00000000;       // pull-ups on rows; columns idle HIGH
	PORTB = 0b11111111;
	while (1) {
		set_7segment(read_keypad());
		asm volatile("nop");
	}
}
