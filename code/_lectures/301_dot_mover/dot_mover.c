#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

#define MATRIX_WIDTH (16)
#define MATRIX_BASE ((volatile uint8_t *)0xE020)

// MODEL state
uint8_t matrix[16];
uint8_t row, col;

// MODEL init
void model_init(void){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        matrix[i] = B8(00000000);
    }
    row = 3;
    col = 4;
    model_light_row_col(row, col);
}

// MODEL set row, col
void model_set_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] | (1U << row);
}

// MODEL clear row, col
void model_clear_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] & ~(1U << row);
}

// MODEL move
typedef enum {
    NONE, UP, DOWN, LEFT, RIGHT
} direction;

void model_move(direction d) {
    uint8_t new_row, new_col;
    switch (d) {
        case NONE:  new_row = row;
                    new_col = col;
                    break;
        case DOWN:  new_col = col;
                    new_row = (row < 1) ? row : row - 1;
                    break;
        case UP:    new_col = col;
                    new_row = (row > 6) ? row : row + 1;
                    break;
        case LEFT:  new_col = (col < 1) ? col : col - 1;
                    new_row = row;
                    break;
        case RIGHT: new_col = (col > 6) ? col: col + 1;
                    new_row = row;
                    break;
    }
    if ( !((new_row) == row && (new_col == col)) ) {
        model_clear_row_col(row, col);
        model_set_row_col(row, col);
    }
}

// VIEW update - transfer MODEL to VIEW
void update_view(){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        *(MATRIX_BASE + i) = matrix[i];
    }
}

// CONTROLLER
void read_keypad_and_update_model(void){
    
}
