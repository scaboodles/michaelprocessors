#include <avr/io.h>
#include <util/delay.h>

int keypad[4][3] = {
    {1, 2, 3},
    {4, 5, 6}, 
    {7, 8, 9},
    {-1, 0, -1}
};

//char keypad[4][3] = {
//    {'1', '2', '3'},
//    {'4', '5', '6'}, 
//    {'7', '8', '9'},
//    {' ', '0', ' '}
//};

unsigned char seven_seg[10] = {
    0b11000000, // 0
    0b11111001, // 1  
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

int main(){
    unsigned char x;
    unsigned char key; 
    DDRB = 0b11110000;
    PORTB = 0b11011111; 
    asm volatile("nop");
    while (1)
    {
        x = PINB; // read from port B
        if ((x & 0b00000010) == 0){ // check bit 1 (row 3)
            PORTA = seven_seg[8];
        }else{
            PORTA = seven_seg[0];
        }
        _delay_ms(5);
    }
    
}

