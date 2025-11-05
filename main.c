
/*
 * LAB3.c
 *
 * Created: 11/4/2025 2:36:34 PM
 * Author : lpizz
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



volatile uint32_t period;
volatile uint32_t freq;


volatile int overflow_count; 

ISR(TIMER1_OVF_vect){
	 overflow_count++;			// ofcount increment
	 } 


void delay(int n){ 
	int overflow_limit; 
	
	overflow_limit = n * 15;	// oflimit defined, not changed, n represents the amount of seconds that will have a delay
	overflow_count = 0;			// ofcount defined, changed using ISR
	TCNT1 = 0;					// Reset timer 1
	while (overflow_count <= overflow_limit){;}
								// As long as the total of count does not exceed the of limit then the timer will run
}
	

void serial_init(void){
								
	UCSRA = 0b00000000;			// Normal speed, disable multi-proc
	UCSRB = 0b00011000; 			// Enable Tx and Rx pins, enable RX interrupt
	UCSRC = 0b10000110;			// Asynchronous mode, no parity, 1 stop bit, 8 data bits
	UBRRL = 0x33; UBRRH = 0x00;	// Baud rate 1200bps, assuming 1MHz clock
}


ISR(TIMER1_CAPT_vect) {     // capture ISR
	
	period = ICR1;
	freq = 1000000/period;		// set the frequency with respect to the period
	TCNT1 = 0;
}


int serial_send(char c, FILE *stream){
								// Wait until UDRE flag is set to logic 1
	while ((UCSRA & (1 << UDRE)) == 0x00){;}
		UDR = c;				// Write character to UDR for transmission
		return 0;
}

int main(void){
	DDRE &= ~(1 << PE0); 
	DDRB = 0xFF;                 // LEDs as outputs

//	TCCR1A = 0;                  // normal mode
//	TCCR1B = (1 << CS10);        // prescaler = 1, start Timer1

//	TIMSK |= (1 << TOIE1);       // **enable Timer1 overflow interrupt**
	
	
	sei();                       // **enable global interrupts**
	serial_init();				// initialize serial port

	TCCR1A = 0b00000000;		// for task 2
	TCCR1B = (1<<ICNC1) | (1<<ICES1) | (1<<CS10); 		// for task 2															
	TIMSK |= (1 << TOIE1) | (1 << TICIE1);
		
		
	stdout = fdevopen(serial_send, NULL); 
								// enable output to terminal
    while (1) 
    {
		
		/*
		// Task 1:
		
		PORTB = 0b10101010;		// only 1,3,5,7
		delay(4);				// 4 sec delay
		PORTB = 0b01010101;		// only 0,2,4,6
		delay(4);				// 4 sec delay
		*/
		
		
		// Task 2:
		PORTB = ~(uint8_t)(period >> 8); // top 8 bits to PORTB
		
		printf("Period = %ld microsecond \r \n", period);
								// send period
		printf("Frequency = %ld Hz \r \n", freq);
								// send freq
		
    }
}

