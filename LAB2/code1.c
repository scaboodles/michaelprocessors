/*
 * LAB2.c
 *
 * Created: 10/1/2025 1:16:45 PM
 * Author : lpizz
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define CPU 1000000
#define BAUD 1200
#define SET (CPU/(16*BAUD))-1
void serial_init(void){
	// Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UCSRC = 0b10000110;
	// Normal speed, disable multi-proc
	UCSRA = 0b00000000;
	// Baud rate 1200bps, assuming 1MHz clock
	UBRRL = (unsigned char)SET;
	UBRRH = (unsigned char) (SET >> 8);
	// Enable Tx and Rx, disable interrupts
	UCSRB = 0b00011000;
}
/*
void serial_send(unsigned char data){
	// Wait until UDRE flag = 1
	while ((UCSRA & (1 << UDRE)) == 0x00){;}
	// Write char to UDR for transmission
	UDR = data;
}

unsigned char serial_receive(void){
	// Wait until RXC flag = 1
	while ((UCSRA & (1 << RXC)) == 0x00){;}
	// Read the received char from UDR
	return (UDR);
}
*/

int serial_send(char c, FILE *stream){
	// Wait until UDRE flag is set to logic 1
	while ((UCSRA & (1 << UDRE)) == 0x00){;}
	UDR = c; // Write character to UDR for transmission
	return 0;
}
int serial_receive(FILE *stream){
	// Wait until RXC flag is set to logic 1
	while ((UCSRA & (1 << RXC)) == 0x00){;}
	return UDR; // Read the received character from UDR
}

unsigned char read_keypad(void) {
	
	unsigned char x;
	
	
	

	DDRA = 0b11110000;
	
	PORTA = 0b10111111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00001000) == 0){
		return '4';
		} if ((x & 0b00000100) == 0){
		return '1';
		} if ((x & 0b00000010) == 0) {
		return '7';
	}
	
	PORTA = 0b11011111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00001000) == 0){
		return '5';
		} if ((x & 0b00000100) == 0){
		return '2';
		} if ((x & 0b00000010) == 0){
		return '8';
		} if ((x & 0b00000001) == 0){
		return '0';
	}
	
	PORTA = 0b11101111;
	asm volatile("nop");
	x = PINA;
	if ((x & 0b00001000) == 0){
		return '6';
		} if ((x & 0b00000100) == 0){
		return '3';
		} if ((x & 0b00000010) == 0) {
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

int main(void){
	serial_init();
	unsigned char k;
	unsigned char j; 
	unsigned int a,b;
	stdout = fdevopen(serial_send, NULL);
	stdin = fdevopen(NULL, serial_receive);
	DDRB = 0xFF;
	
	while (1){
		/*
		//Task 1:
		k = read_keypad();
		serial_send(k);
		_delay_ms(100);
		*/
		
		/*
		//Task 2:
		printf("\n\rEnter a character = ");
		printf("%c", k);
		
		k = serial_receive();
		_delay_ms(200);
		display_7led(k);
		*/
		
		//Task 3:
		
		printf("\n\rPlease enter two integer values:\n\r");
		
		printf("Enter integer a: ");
		scanf("%d", &a);
		printf("\n\rEnter integer b: ");
		scanf("%d", &b );
		
		printf("\n\rInteger a = %d", a);
		printf("\n\rInteger b = %d", b);
		
		printf("\n\r\n\rArithmetic Output:");
		printf("\n\ra+b = %d", a + b);
		printf("\n\ra-b = %d", a - b);
		printf("\n\ra*b = %d", a * b);
		printf("\n\ra/b = %d", a / b);
		
		_delay_ms(1000);
	}

}

