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

extern inputType        type;
extern                  label_tree *labels;
extern short int        memoryPosition;
extern short int        instructionPos;
extern int              lineCounter;
extern instruction      instruction_list[20];

bool containsChar (char input[], char c) {
    int i;
    unsigned long int size_str = strlen(input);
    
    for(i = 0; i < size_str; i ++) {
        if(input[i] == c) {
            return true;
        }
    }
    
    return false;
}

bool isInstruction(char input[]) {
    int i = 0;
    
    for(i = 0; i < 20; i++) {
        if(!strcmp(input, instruction_list[i].mnemonic))
            return true;
    }
    
    /***********************************/
    // Error treatment
    
    fprintf(stderr, "ERROR on line %d\n%s is not a valid instruction!\n", lineCounter, input);
    exit(1);
    
    /***********************************/
    
    return false;
}

/* Checks if the input is a label */
bool isLabel (char input[]) {
    int i;
    unsigned long int size_str = strlen(input);
    
    if(input == NULL) { return false; }
    
    if(input[size_str - 1] == ':') {
        // Checks if it starts with a number
        if(input[0] >= '0' && input[0] <= '9') {
            fprintf(stderr, "ERROR on line %d\n%s is not a valid label", lineCounter, input);
            exit(1);
        }
        
        // Checks if there's a colon in the middle of the input
        for(i = 0; i < size_str; i ++) {
            if(input[i] == ':' && i != size_str - 1) {
                fprintf(stderr, "ERROR on line %d\n%s is not a valid label", lineCounter, input);
                exit(1);
            }
        }
        
        return true;
    }
    
    return false;
}

/* Checks if input is a Directive */
bool isDirective (char input[]) {
    return input[0] == '.';
}

/* checks if input is a Comment */
bool isComment (char input[]) {
    return input[0] == '#';
}

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

void reader(char input[]) {
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
void pre_process(char input[]) {
    inputType t = identifyType(input);
    switch (t) {
        case DIRECTIVE:
            
            if(!strcmp(input, ".word")) memoryPosition++;
            if(!strcmp(input, ".wfill")) {
                long long int n;
                read_number_generic(&n);
                memoryPosition += n;
            }
            if(!strcmp(input, ".align")) {
                long long int n;
                read_number_generic(&n);
                
                if(instructionPos == LEFT) {
                    while(memoryPosition % n) { _increment(true); }
                } else {
                    
                    _increment(false);
                    while(memoryPosition % n) { _increment(true); }
                }
            }
            if(!strcmp(input, ".org")) {
                long long int n;
                read_number_generic(&n);
                memoryPosition = n;
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
