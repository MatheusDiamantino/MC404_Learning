//
//  treat_type.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "treat_type.h"
#include "labelBST.h"
#include "defines.h"
#include "readInput.h"
#include "instruction.h"

instruction instruction_list[N_INSTR];
extern treeNode *labels;
extern short int memoryPosition;
extern short int instructionPos;
extern int lineCounter;

void treat_label(char input[]) {
    Insert(labels, memoryPosition, input, instructionPos);
    return;
}

void treat_comment(char input[]) {
    read_junk();
}

void treat_directive(char input[]) {
    if(!strcmp(input, ".set")) {
        char sym[65];
        long long int num;
        read_input(sym);
        read_number_generic(&num);
        
        /* STORE SYMBOL AND NUMBER !!!!!!! */
        
    } else if (!strcmp(input, ".word")){
        
        // In case it's trying to use .word while in the right instruction
        if(instructionPos == RIGHT) {
            printf("ERROR on line %d\nRequesting .word directive on right instruction", lineCounter);
            stderr;
        }
        
        long long int num;
        read_number_generic(&num);
        
        /* STORE NUM AS A NUMBER ON THE MEMORY MAP !!!!!!!! */
        
    } else if (!strcmp(input, ".wfill")) {
        short int memory_used;
        char num[65];
        read_number((int*)&memory_used);
        read_input(num);
        
    } else if (!strcmp(input, ".align")) {
        short int multiple;
        read_number((int*)&multiple);
        
        // In case the multiple given is out of bounds
        if(multiple < 0 || multiple > 1023) {
            printf("ERROR on line %d\n argument for %s is out of bound! (0:1023)\n", lineCounter, input);
            stderr;
        }
        
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
        
        if(num < 0 || num > 1023) {
            printf("ERROR on line %d\n argument for %s is out of bound! (0:1023)\n", lineCounter, input);
            stderr;
        }
        
        memoryPosition = (short int)num;
    }

}
void treat_instruction(char input[]) {
    int i = 0;
    char arg[MAXROT];
    
    for(i = 0; i < N_INSTR; i++) {
        if(!strcmp(instruction_list[i].mnemonic, input)) {
            if(instruction_list[i].expect_argument) { read_input(arg); }
            
            /* ADD INSTRUCTION TO THE LIST !!!!!!!! */
            
            return;
        }
    }










}