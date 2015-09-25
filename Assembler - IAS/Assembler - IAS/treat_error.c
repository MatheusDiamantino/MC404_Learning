//
//  treat_error.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/25/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "treat_error.h"
#include "defines.h"

extern int          lineCounter;
extern short int    instructionPos;

void _error_bounds(long long int low_bound, long long int high_bound, long long int to_treat) {
    
    if(to_treat < low_bound || to_treat > high_bound) {
        fprintf(stderr, "ERROR on line %d\n%lld is out of bounds specified (%lld:%lld)\n", lineCounter, to_treat, low_bound,
                high_bound);
        
        exit(1);
    }
    
}

void _error_instruction_not_found(char *instruction) {
    
    fprintf(stderr, "ERROR on line %d\n%s is not a valid instruction!\n", lineCounter, instruction);
    exit(1);
    
}

void _error_no_argument_instruction(char *instruction, bool has_argument, bool is_comment) {
    
    if(has_argument && !is_comment) {
        fprintf(stderr, "ERROR on line %d\n%s should not receive an argument!\n", lineCounter, instruction);
        exit(1);
    }
    
}

void _error_word_on_right_instruction(char *instruction) {
    
    if(instructionPos == RIGHT && (!strcmp(instruction, ".word") || !strcmp(instruction, ".wfill"))) {
        fprintf(stderr, "ERROR on line %d\nRequesting %s directive on right instruction", lineCounter, instruction);
        exit(1);
    }
    
}

void _error_not_10_digit_HEX_number(char *number) {
    
    if(strlen(number) != 12 && strlen(number) > 1 && number[1] == 'x' && number[0] == '0') {
        fprintf(stderr, "ERROR on line %d\n%s is not a 10 digit HEX number\n", lineCounter, number);
        exit(1);
    }
    
}

void _error_not_valid_number(char *number) {
    
    if(strlen(number) > 2 && number[0] == '0' && number[1] == 'x')
        fprintf(stderr, "ERROR on line %d\n%s is not a valid HEX number\n", lineCounter, number);
    else if (strlen(number) > 2 && number[1] != 'x') {
        fprintf(stderr, "ERROR on line %d\n%s is not a valid DEC number\n", lineCounter, number);
    }
    exit(1);
    
}
