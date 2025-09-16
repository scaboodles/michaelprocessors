#include <avr/io.h>
#include <util/delay.h>

unsigned char read_matrix(){
    _delay_ms(1);
    return PINB;
}

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

unsigned char int_to_7seg(int digit) {
    if(digit >= 0 && digit <= 9) {
        return seven_seg[digit];
    }
    return 0b11111111; // all off for invalid input
}

int get_row(unsigned char colstat){
    if((colstat & 0b00001000) == 0){ 
        return 1;
    }else if((colstat & 0b00000100) == 0){ 
        return 2;
    }else if((colstat & 0b00000010) == 0){ 
        return 3;
    }else if((colstat & 0b00000001) == 0){ 
        return 4;
    }
    return 0;
}

int main(){
    unsigned char matrix;
    int row;
    DDRB = 0b11110000;
    DDRA = 0b11111111;
    PORTB |= 0b00001111; // Enable pull-ups on row inputs
    while(1){
        // col 0
        PORTB = 0b10111111;
        _delay_ms(5);
        matrix = read_matrix();
        row = get_row(matrix);
        if(row > 0){
            int key = keypad[row-1][0];
            if(key >= 0 && key <= 9) {
                PORTA = seven_seg[key];
            }
            continue;
        }

        // col 1
        PORTB = 0b11011111;
        _delay_ms(5);
        matrix = read_matrix();
        row = get_row(matrix);
        if(row > 0){
            int key = keypad[row-1][1];
            if(key >= 0 && key <= 9) {
                PORTA = seven_seg[key];
            }
            continue;
        }
        
        // col 2
        PORTB = 0b11101111;
        _delay_ms(5);
        matrix = read_matrix();
        row = get_row(matrix);
        if(row > 0){
            int key = keypad[row-1][2];
            if(key >= 0 && key <= 9) {
                PORTA = seven_seg[key];
            }
            continue;
        }

        _delay_ms(5);
    }
}

