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

/* -----------------------------------------------
 *
 * Verifies if number given is out of bounds specified
 *
 * -----------------------------------------------*/

void _error_bounds(long long int low_bound, long long int high_bound, long long int to_treat) {
    
    if(to_treat < low_bound || to_treat > high_bound) {
        fprintf(stderr, "ERROR on line %d\n%lld is out of bounds specified (%lld:%lld)\n", lineCounter, to_treat, low_bound,
                high_bound);
        
        exit(1);
    }
    
}

/* -----------------------------------------------
 *
 * Instruction not found on data base
 *
 * -----------------------------------------------*/

void _error_instruction_not_found(char *instruction) {
    
    fprintf(stderr, "ERROR on line %d\n%s is not a valid instruction!\n", lineCounter, instruction);
    exit(1);
    
}

/* -----------------------------------------------
 *
 * Instruction did not expected argument
 *
 * -----------------------------------------------*/

void _error_no_argument_instruction(char *instruction, bool has_argument, bool is_comment) {
    
    if(has_argument && !is_comment) {
        fprintf(stderr, "ERROR on line %d\n%s should not receive an argument!\n", lineCounter, instruction);
        exit(1);
    }
    
}

/* -----------------------------------------------
 *
 * Trying to use .word or .wfill on right instruction
 *
 * -----------------------------------------------*/

void _error_word_on_right_instruction(char *instruction) {
    
    if(instruction != NULL) {
        if(instructionPos == RIGHT && (!strcmp(instruction, ".word") || !strcmp(instruction, ".wfill"))) {
            fprintf(stderr, "ERROR on line %d\nRequesting %s directive on right instruction", lineCounter, instruction);
            exit(1);
        }
    }
    
}

/* -----------------------------------------------
 *
 * Not a valid Hex number
 *
 * -----------------------------------------------*/

void _error_not_10_digit_HEX_number(char *number) {
    
    if(number != NULL) {
        if(strlen(number) != 12 && strlen(number) > 1 && number[1] == 'x' && number[0] == '0') {
            fprintf(stderr, "ERROR on line %d\n%s is not a 10 digit HEX number\n", lineCounter, number);
            exit(1);
        }
    }
    
}


/* -----------------------------------------------
 *
 * Not a valid number (HEX or DEC)
 *
 * -----------------------------------------------*/

void _error_not_valid_number(char *number) {
    
    if(number != NULL) {
        if(strlen(number) > 2 && number[0] == '0' && number[1] == 'x')
            fprintf(stderr, "ERROR on line %d\n%s is not a valid HEX number\n", lineCounter, number);
        else if (strlen(number) > 2 && number[1] != 'x') {
            fprintf(stderr, "ERROR on line %d\n%s is not a valid DEC number\n", lineCounter, number);
        }
        exit(1);
    }
    
}


/* -----------------------------------------------
 *
 * Not a Symbol or Label valid
 *
 * -----------------------------------------------*/

void _error_not_valid_SYM_or_label(char *sym) {
    if(sym != NULL) {
        fprintf(stderr, "ERROR on line %d\n%s is not a valid Symbol or Label!\n", lineCounter, sym);
        exit(1);
    }
}

/* -----------------------------------------------
 *
 * Input expected argument but did not receive one
 *
 * -----------------------------------------------*/

void _error_expected_argument(char *instr) {
    if(instr != NULL) {
        fprintf(stderr, "ERROR on line %d\n%s expects argument!\n", lineCounter,instr);
        exit(1);
    }
}
