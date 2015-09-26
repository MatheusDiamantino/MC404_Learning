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
#include "treat_error.h"

extern memory_word              word;
extern memory_map_tree          *instr_tree;
extern instruction              instruction_list[N_INSTR];
extern label_tree               *labels, *sym;
extern short int                memoryPosition;
extern short int                instructionPos;
extern int                      lineCounter;


/* --------------------------------------------------------------------
 *
 * LOCAL FUNCTION
 *
 * Insert string into the tree. If str is NULL, insert the instructions
 * in 'word' variable
 *
 * ------------------------------------------------------------------- */
void _insert_memory_map(char *str) {
    
    if(instructionPos == RIGHT) {
        word.right_argument = 0;
        word.right_instruction = 0;
    }
    if(str == NULL)
        instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output(word.left_instruction,
                                                                                 word.right_instruction, word.left_argument,
                                                                                 word.right_argument));
    else instr_tree = insert_memory_map(instr_tree, memoryPosition, str);
    
    word.left_argument = -1;
    word.left_instruction = -1;
    word.right_instruction = -1;
    word.right_argument = -1;
}


/* --------------------------------------------------------------------
 *
 * LOCAL FUNCTION
 *
 * Insert values in the 'word' variable
 *
 * ------------------------------------------------------------------- */
void _insert_instruction(long long int instr, long long int arg) {
    
    if(instructionPos == LEFT) {
        word.left_instruction = instr;
        word.left_argument = arg;
    } else {
        word.right_argument = arg;
        word.right_instruction = instr;
        
        _insert_memory_map(format_output(word.left_instruction, word.right_instruction, word.left_argument,
                                         word.right_argument));
        
        word.left_argument = -1;
        word.left_instruction = -1;
        word.right_instruction = -1;
        word.right_argument = -1;
    }
    
}

/* -----------------------------------------------
 *
 * Take off the colon of the label and store it
 *
 * -----------------------------------------------*/
void treat_label(char input[]) {
    input[strlen(input) - 1] = '\0';
    labels = Insert(labels, memoryPosition, input, instructionPos);
    return;
}

/* -----------------------------------------------
 *
 * Read the rest of commented line
 *
 * -----------------------------------------------*/
void treat_comment(char input[]) {
    read_junk();
    return;
}

/* -----------------------------------------------
 *
 * Treat all directive options
 *
 * -----------------------------------------------*/
void treat_directive(char input[]) {
    
    /* Treats .set directive */
    if(!strcmp(input, ".set")) {
        char            symbol[MAXROT];
        long long int   num;
        
        if(!read_input(symbol)) _error_expected_argument(input);    // If argument is not specified
        
        if(!read_number_generic(&num)) _error_expected_argument(input); // If argument is not specified
        
        
        _error_bounds(0, pow(2.0, 31.0) - 1, num);          // Verifies if number is inside bound specified
        
        
        sym = Insert(sym, num, symbol, -1);
        
     /* Treats .word directive */
    } else if (!strcmp(input, ".word")){
        
       
        _error_word_on_right_instruction(input);            // Verifies if it's not requesting .word on right instruction
    
        
        char        str[MAXROT];
        
        if(!read_input(str)) _error_expected_argument(input);   // If argument is not specified
        
        label_tree *node = NULL;
        
        if(isLabel(str)) { str[strlen(str) - 1] = '\0'; node = Find(labels, str); }
        
        // Insert value in the tree if it's a label, symbol or number
        if(node != NULL) { _insert_memory_map(format_output_HEX(node -> memPos)); }
        else {
                
            node = Find(sym, str);
            
            if(node != NULL)
                _insert_memory_map(format_output_HEX(node -> memPos));
            
            
            else {
                if(!string_is_number(str)) _error_not_valid_SYM_or_label(str);
                _insert_memory_map(format_output_HEX(convert_string_number(str)));
            }
        }
        
        _increment(true);
        
        
     /* Treats .wfill directive */
    } else if (!strcmp(input, ".wfill")) {
        long long int           memory_used;            // Memory used for the .wfill directive
        char                    num[MAXROT];            // Value to be stored
        int                     i = 0;
        label_tree              *node = NULL;           // Tree node that'll be the node of the found label or sym
        long long int           to_be_stored;           // Value to be stored by .wfill
        
       _error_word_on_right_instruction(input);         // Verifies if it's not requesting .word on right instruction
        
        
        if(!read_input(num)) _error_expected_argument(input);   // If argument is not specified
        
        memory_used = convert_string_number(num);       // Read input and tries to convert it to number
        
      
        _error_bounds(0, 1023, memory_used);            // Verifies if number given isn't out of bounds
        
        
        if(!read_input(num)) _error_expected_argument(input);   // If argument is not specified
        
        
        // if input is label, take off the colon of the string
        if(isLabel(num)) { num[strlen(num) - 1] = '\0'; node = Find(labels, num); }
        
        // Store value depending if it's label, symbol or number
        if(node != NULL) { to_be_stored = node -> memPos; }
        else {
            node = Find(sym, num);
            
            if(node != NULL)    to_be_stored = node -> memPos;
            else                to_be_stored =  convert_string_number(num);
        }
        
        
        // Store the value N times in the memory map
        for (i = 0; i < memory_used; i++) {
            _insert_memory_map(format_output_HEX(to_be_stored));
            
            _increment(true);
        }
        
        
    /* Treats .align directive */
    } else if (!strcmp(input, ".align")) {
        long long int           multiple;                   // Multiple given to the .align directive
        char                    str[MAXROT];                // Input to be read
        
        if(!read_input(str)) _error_expected_argument(input);   // If argument is not specified
        
        multiple = convert_string_number(str);
        
        
        _error_bounds(0, 1023, multiple);                   // Verifies if input is out of bounds specified
        
        
        // Aligns the memory position with the multiple given
        if(instructionPos == LEFT) {
            
            while(memoryPosition % multiple) { _increment(true); }      // Finds next memory position multiple
            
        } else {
            _insert_memory_map(NULL);                       // Inserts memory word into the tree with right instr = 0
            
            _increment(false);
            
            while(memoryPosition % multiple) { _increment(true); }      // Finds next memory position multiple
        }
        
        
    /* Treats .org directive */
    } else if (!strcmp(input, ".org")) {
        long long int num;
        
        if(!read_number_generic(&num))_error_expected_argument(input); // If argument is not given
        
        _error_bounds(0, 1023, num);                // Verifies if number given isn't out of bounds
    
        
        if(instructionPos == RIGHT) {
            
            _insert_memory_map(NULL);   // Insert word in the memory map if there's no right instruction (fill it with 0's)
            _increment(false);
        }
        _change_position(num);
    }

}

/* --------------------------------------------------------------------
 *
 * Tries to find the instruction requested and treats it accordingly
 *
 * ------------------------------------------------------------------- */

void treat_instruction(char input[]) {
    int                 i = 0;
    label_tree          *label;
    char                arg[MAXROT];
    
    // Finding the instruction requests
    for(i = 0; i < N_INSTR; i++) {
        if(!strcmp(instruction_list[i].mnemonic, input)) {
            
            // If the instruction expect an argument
            if(instruction_list[i].expect_argument) {
                
                if(!read_input(arg)) _error_expected_argument(input);
                label = Find(labels, arg);
                
                
                
                // Error when argument given is a word and isn't a label on the data base
                
               if(!string_is_number(arg) && label == NULL) {
                   _error_not_valid_SYM_or_label(arg);
                }
                
                
                if(label != NULL) {
                    
                    if(label -> instruction == RIGHT && instruction_list[i].lr_instr != NONE) {
                        
                        _insert_instruction(instruction_list[i + 1].code, label -> memPos);
                        
                    } else {
                        
                        _insert_instruction(instruction_list[i].code, label -> memPos);
                        
                    }
                    
                } else {
                    
                    _insert_instruction(instruction_list[i].code, convert_string_number(arg));
                    
                }
            } else {
                
                char str[MAXROT];
                
                
                _error_no_argument_instruction(input, read_input(str), isComment(str));
                
                _insert_instruction(instruction_list[i].code, 0);
                
            }
            
            _increment(false);
            
            return;
        }
    }
    
    _error_instruction_not_found(input);                    // If it hasn't found the instruction on the data base
}


