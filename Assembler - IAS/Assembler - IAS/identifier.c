//
//  identifier.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/23/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "identifier.h"
#include "typeEnum.h"
#include "readInput.h"
#include "labelBST.h"
#include "instruction.h"
#include "treat_type.h"
#include "treat_MMP.h"
#include "treat_error.h"

extern inputType        type;
extern                  label_tree *labels;
extern short int        memoryPosition;
extern short int        instructionPos;
extern int              lineCounter;
extern instruction      instruction_list[20];


/* --------------------------------------------------------------------
 *
 * Verifies if given string is a valid instruction
 *
 * ------------------------------------------------------------------- */

bool isInstruction(char input[]) {
    int i = 0;
    
    for(i = 0; i < 20; i++) {
        if(!strcmp(input, instruction_list[i].mnemonic))
            return true;
    }
    

    _error_instruction_not_found(input);        // If it's not a valid instruction
    
    return false;
}

/* --------------------------------------------------------------------
 *
 * Verifies if given string is a valid Label
 *
 * ------------------------------------------------------------------- */

bool isLabel (char input[]) {
    int i;
    unsigned long int size_str = strlen(input);
    
    if(input == NULL) { return false; }
    
    if(input[size_str - 1] == ':') {
        // Checks if it starts with a number
        if(input[0] >= '0' && input[0] <= '9') {
            _error_not_valid_SYM_or_label(input);
        }
        
        // Checks if there's a colon in the middle of the input
        for(i = 0; i < size_str; i ++) {
            if(input[i] == ':' && i != size_str - 1) {
                _error_not_valid_SYM_or_label(input);
            }
        }
        
        return true;
    }
    
    return false;
}

/* --------------------------------------------------------------------
 *
 * Verifies if given string is a Directive
 *
 * ------------------------------------------------------------------- */

bool isDirective (char input[]) {
    return input[0] == '.';
}

/* --------------------------------------------------------------------
 *
 * Verifies if given string is a Comment
 *
 * ------------------------------------------------------------------- */

bool isComment (char input[]) {
    return input[0] == '#';
}

/* --------------------------------------------------------------------
 *
 * Identify tipe of the input given
 *
 * ------------------------------------------------------------------- */

inputType identifyType (char input[]) {
    
    if (isDirective(input)) {
        
        return DIRECTIVE;
    } else if (isLabel(input)) {
        return LABEL;
    } else if (isComment(input)) {
        return COMMENT;
    } else  if(isInstruction(input)){
        return INSTRUCTION;
    }
    
    return ERROR;
    
}

/* --------------------------------------------------------------------
 *
 * With string given, treats the identified input
 *
 * ------------------------------------------------------------------- */

void main_process(char input[]) {
    inputType t;
    
    t =  identifyType(input);
    verify_order(t);
    
    switch (t) {
        case DIRECTIVE:
            treat_directive(input);
            break;
        case COMMENT:
            treat_comment(input);
            break;
        case LABEL:
            //treat_label(input);
            break;
        case INSTRUCTION:
            treat_instruction(input);
            break;
        case ERROR:
            break;
        case NONE:
            break;
    }
    
}

/* --------------------------------------------------------------------
 *
 * Pre - process Cicle
 *
 * ------------------------------------------------------------------- */

void pre_process(char input[]) {
    inputType t = identifyType(input);
    switch (t) {                        // Does the basic operations in order to compute the labels in the pre process cicle
        case DIRECTIVE:
            
            if(!strcmp(input, ".word")) memoryPosition++;
            else if(!strcmp(input, ".wfill")) {
                long long int n;
                read_number_generic(&n);
                memoryPosition += n;
            }
            else if(!strcmp(input, ".align")) {
                long long int n;
                read_number_generic(&n);
                
                if(instructionPos == LEFT) {
                    while(memoryPosition % n) { _increment(true); }
                } else {
                    
                    _increment(false);
                    while(memoryPosition % n) { _increment(true); }
                }
            }
            else if(!strcmp(input, ".org")) {
                long long int n;
                read_number_generic(&n);
                _change_position(n);
            }
            read_junk();
            break;
        case COMMENT:
            treat_comment(input);
            break;
        case LABEL:
            
            treat_label(input);
            break;
        case INSTRUCTION:
            read_junk();
            _increment(false);
            break;
        case ERROR:
            break;
        case NONE:
            break;
    }
}


/* --------------------------------------------------------------------
 *
 * Verifies if the order of the inputs in the same line is in the correct order
 *
 * ------------------------------------------------------------------- */

void verify_order(inputType t) {
    
    if(type == NONE) {
        type = t;
        return;
    }
    
    if(type == INSTRUCTION) {
        if(t != COMMENT) {
            fprintf(stderr, "ERROR on line %d\nOnly comments can go after instructions!\n", lineCounter);
            exit(1);
        }
    } else if(type == DIRECTIVE) {
        if(t != COMMENT) {
            fprintf(stderr, "ERROR on line %d\nOnly comments can go after directives!\n", lineCounter);
            exit(1);
        }
    } else if(type == LABEL){
        if(t == LABEL) {
            fprintf(stderr, "ERROR on line %d\nCannot have more than one label on a line!\n", lineCounter);
            exit(1);
        }
    }
    
    type = t;
    
}
