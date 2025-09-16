#include <avr/io.h>
#include <util/delay.h>

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

//unsigned char 
void read_keypad(){
    // read column 2
    PORTB = 0b11011111; 
    _delay_ms(5);
    unsigned char x = PINA; // read from port A
    if ((x & 0b00000010) == 0){ // check bit 1 (row 3)
        PORTB = seven_seg[8];
    }else if((x & 0b00000100) == 0){ // check bit 2 (row 2)
        PORTB = seven_seg[5];
    }else if((x & 0b00001000) == 0){ // check bit 2 (row 1)
        PORTB = seven_seg[2];
    }

    PORTA = 0b10111111; 
    _delay_ms(5);
    if ((x & 0b00000010) == 0){ // check bit 1 (row 3)
        PORTB = seven_seg[1];
    }else if((x & 0b00000100) == 0){ // check bit 2 (row 2)
        PORTB = seven_seg[4];
    }else if((x & 0b00001000) == 0){ // check bit 2 (row 1)
        PORTB = seven_seg[7];
    }

}

//void display_7led(unsigned char a){

//}

int main(){
    unsigned char matrix;
    int row;
    DDRB = 0b11111111;
    DDRA = 0b11110000;

    while (1){
        read_keypad();
        _delay_ms(5);
    }
}

