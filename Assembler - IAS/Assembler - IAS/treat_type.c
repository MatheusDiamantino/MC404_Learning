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
#include "treat_MMP.h"
#include "labelBST.h"
#include "defines.h"
#include "readInput.h"
#include "instruction.h"
#include "identifier.h"
#include "memory_map_BST.h"

extern memory_word              word;
extern memory_map_tree          *instr_tree;
extern instruction              instruction_list[N_INSTR];
extern label_tree               *labels, *sym;
extern short int                memoryPosition;
extern short int                instructionPos;
extern int                      lineCounter;

/*
 * Take off the colon of the label and store it
 */
void treat_label(char input[]) {
    char *str = strtok(input, ":");
    Insert(labels, memoryPosition, str, instructionPos);
    return;
}

/*
 * Read the rest of commented line
 */
void treat_comment(char input[]) {
    read_junk();
    return;
}


/*
 * Treat all directive options
 */
void treat_directive(char input[]) {
    if(!strcmp(input, ".set")) {
        char            symbol[65];
        long long int   num;
        
        read_input(symbol);
        read_number_generic(&num);
        
        if(num < 0 || num > pow(2.0, 31.0) - 1) {
            fprintf(stderr, "ERROR on line %d\nArgument for %s is out of bounds! (0:2^31 - 1)", lineCounter, input);
            exit(1);
        }
        
        Insert(sym, num, symbol, -1);
    } else if (!strcmp(input, ".word")){
        
        /***********************************/
        // Error treatment
        
        // In case it's trying to use .word while in the right instruction
        if(instructionPos == RIGHT) {
            fprintf(stderr, "ERROR on line %d\nRequesting %s directive on right instruction", lineCounter, input);
            exit(1);
        }
        
        /***********************************/
        
        char str[MAXROT];
        read_input(str);
        label_tree *node = NULL;
        
        if(isLabel(str)) { node = Find(labels, str); }
        
        if(node != NULL) { instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output_HEX(node -> memPos)); }
        else {
            node = Find(sym, str);
            
            if(node != NULL) { instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output_HEX(node -> memPos)); }
            else {
                instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output_HEX(convert_string_number(str)));
            }
        }
        _increment(true);
        
    } else if (!strcmp(input, ".wfill")) {
        short int memory_used;
        char num[MAXROT];
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
        
        label_tree *node = NULL;
        long long int mem_pos;
        
        if(isLabel(num)) { node = Find(labels, num); }
        
        if(node != NULL) { mem_pos = node -> memPos; }
        else {
            node = Find(sym, num);
            
            if(node != NULL) { mem_pos = node -> memPos; }
            else {
                mem_pos =  convert_string_number(num);
            }
        }
        
        for (i = 0; i < memory_used; i++) {
            instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output_HEX(mem_pos));
            _increment(true);
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
            while(memoryPosition % multiple) { _increment(true); }
        } else {
            _increment(false);
            while(memoryPosition % multiple) { _increment(true); }
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
    int                 i = 0;
    label_tree          *label;
    char                arg[MAXROT];
    bool                next_argument = false;
    
    word.word = -1;
    
    // Finding the instruction requestes (Jesus, it's messy ....)
    for(i = 0; i < N_INSTR; i++) {
        if(!strcmp(instruction_list[i].mnemonic, input)) {
            if(instruction_list[i].expect_argument) {
                next_argument = read_input(arg);
            
                if(isLabel(arg)) {
                    label = Find(labels, arg);
                
                    /***********************************/
                    // Error treatment
                
                    if(label == NULL) {
                        fprintf(stderr, "ERROR on line %d\n %s is not a label \n", lineCounter, arg);
                        exit(1);
                    }
                
                    /***********************************/
                    
                    if(label -> instruction == RIGHT && instruction_list[i].lr_instr != NONE) {
                        if(instructionPos == LEFT) {
                            word.left_argument = label -> memPos;
                            word.left_instruction = instruction_list[i + 1].code;
                        } else if(instructionPos == RIGHT) {
                            word.right_argument = label -> memPos;
                            word.right_instruction = instruction_list[i + 1].code;
                        }
                    } else {
                        if(instructionPos == LEFT) {
                            
                            word.left_argument = label -> memPos;
                            word.left_instruction = instruction_list[i].code;
                            
                        } else if(instructionPos == RIGHT) {
                            word.right_argument = label -> memPos;
                            word.right_instruction = instruction_list[i].code;
                            
                        }
                    }
                
                
                } else {
                    
                    if(instructionPos == LEFT) {
                        word.left_argument = convert_string_number(arg);
                        word.left_instruction = instruction_list[i].code;
                    } else if(instructionPos == RIGHT) {
                        word.right_argument = convert_string_number(arg);
                        word.right_instruction = instruction_list[i].code;
                        
                        /* CONVERT TO STRING */
                    }
                }
            } else {
                
                /*
                 * ERROR: In case the program is providing argument for a non-argument instruction
                 */
                char str[MAXCHAR];
                if(read_input(str) && !isComment(str)) {
                    fprintf(stderr, "ERROR on line %d\n%s shoud not receive argument!\n", lineCounter, input);
                    exit(1);
                }
                
                if(instructionPos == LEFT) {
                    word.left_instruction = instruction_list[i].code;
                    word.left_argument = 0;
                } else if(instructionPos == RIGHT) {
                    word.left_instruction = instruction_list[i].code;
                    word.left_argument = 0;
                }
                
            }
            
            if(instructionPos == RIGHT) {
                instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output(word.left_instruction, word.right_instruction, word.left_argument, word.right_argument));
            }
            
            _increment(false);
            
            return;
        }
    }
    
    /***********************************/
    // Error treatment
    
    fprintf(stderr, "ERROR on line %d\n%s is not a valid instruction!\n", lineCounter, input);
    exit(1);
    
    /***********************************/
}