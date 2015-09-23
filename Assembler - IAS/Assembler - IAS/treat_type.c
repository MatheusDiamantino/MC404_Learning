//
//  treat_type.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "treat_type.h"
#include "labelBST.h"
#include "defines.h"
#include "readInput.h"
#include "instruction.h"
#include "identifier.h"

instruction             instruction_list[N_INSTR];
extern label_tree       *labels;
extern short int        memoryPosition;
extern short int        instructionPos;
extern int              lineCounter;

void treat_label(char input[]) {
    Insert(labels, memoryPosition, input, instructionPos);
    return;
}

void treat_comment(char input[]) {
    read_junk();
    return;
}

void treat_directive(char input[]) {
    if(!strcmp(input, ".set")) {
        char            sym[65];
        long long int   num;
        
        read_input(sym);
        read_number_generic(&num);
        
        if(num < 0 || num > pow(2.0, 31.0) - 1) {
            fprintf(stderr, "ERROR on line %d\nArgument for %s is out of bounds! (0:2^31 - 1)", lineCounter, input);
            exit(1);
        }
        
        /* STORE SYMBOL AND NUMBER !!!!!!! */
        
    } else if (!strcmp(input, ".word")){
        
        /***********************************/
        // Error treatment
        
        // In case it's trying to use .word while in the right instruction
        if(instructionPos == RIGHT) {
            fprintf(stderr, "ERROR on line %d\nRequesting %s directive on right instruction", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        long long int num;
        read_number_generic(&num);
        
        /* STORE NUM AS A NUMBER ON THE MEMORY MAP !!!!!!!! */
        
    } else if (!strcmp(input, ".wfill")) {
        short int memory_used;
        char num[65];
        int i = 0;
        
        /***********************************/
        // Error treatment
        
        if(instructionPos == RIGHT) {
            fprintf(stderr, "ERROR on line %d\nRequesting %s directive on right instruction", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        read_number((int*)&memory_used);
        
        /***********************************/
        // Error treatment
        
        if(memory_used < 0 || memory_used > 1023) {
            fprintf(stderr, "ERROR on line %d\n argument for %s is out of bound! (0:1023)\n", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        read_input(num);
        
        
        for (i = 0; i < memory_used; i++) {
            
            /* STORE NUM AS A NUMBER ON THE MEMORY MAP !!!!! */
            
        }
        
        
        
    } else if (!strcmp(input, ".align")) {
        short int multiple;
        read_number((int*)&multiple);
        
        /***********************************/
        // Error treatment
        
        // In case the multiple given is out of bounds
        if(multiple < 0 || multiple > 1023) {
            fprintf(stderr, "ERROR on line %d\n argument for %s is out of bound! (0:1023)\n", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        // Aligns the memory position with the multiple given
        if(instructionPos == LEFT) {
            while(memoryPosition % multiple) { memoryPosition++; }
        } else {
            instructionPos = LEFT;
            memoryPosition++;
            while(memoryPosition % multiple) { memoryPosition++; }
        }
        
    } else if (!strcmp(input, ".org")) {
        long long int num;
        
        read_number_generic(&num);
        
        /***********************************/
        // Error treatment
        
        if(num < 0 || num > 1023) {
            fprintf(stderr, "ERROR on line %d\n argument for %s is out of bound! (0:1023)\n", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        memoryPosition = (short int)num;
    }

}
void treat_instruction(char input[]) {
    int i = 0;
    label_tree *label;
    char arg[MAXROT];
    
    for(i = 0; i < N_INSTR; i++) {
        if(!strcmp(instruction_list[i].mnemonic, input)) {
            if(instruction_list[i].expect_argument) {
                read_input(arg);
            
                if(isLabel(arg)) {
                    label = Find(labels, arg);
                
                    /***********************************/
                    // Error treatment
                
                    if(label == NULL) {
                        fprintf(stderr, "ERROR on line %d\n %s is not a label \n", lineCounter, arg);
                        exit(1);
                    }
                
                    /***********************************/
                
                    if(instruction_list[i].lr_instr != NONE) { /*  INSERT INSTRUCTION BASED ON THE LABEL */ }
                
                    /* ADD INSIDE HERE */
                
                } else {
                    if(instruction_list[i].lr_instr != NONE) { /*  INSERT INSTRUCTION FOR THE LEFT ONE */ }
                    else { /* INSERT INSTRUCTION TO LIST */ }
                }
            } else {
                
                 /* ADD INSTRUCTION TO THE LIST !!!!!!!! */
                
            }
            
            return;
        }
    }
    
    /***********************************/
    // Error treatment
    
    fprintf(stderr, "ERROR on line %d\n %s is not a valid instruction! \n", lineCounter, input);
    exit(1);
    
    /***********************************/
}