/****************************************************************
* First Assignment: Assembler for the IAS Architecture          *
*                                                               *
* Written by: Matheus Mortatti Diamantino     RA: 156740        *
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "labelBST.h"
#include "identifier.h"
#include "typeEnum.h"
#include "instruction.h"
#include "defines.h"
#include "memory_map_BST.h"
#include "treat_type.h"

inputType           type;
memory_word         word;
char                line[MAXCHAR];
memory_map_tree     *instr_tree;
FILE                *fRead;
label_tree          *labels, *sym;
int                 memoryPosition;
short int           instructionPos;
int                 lineCounter;
instruction         instruction_list[N_INSTR] = {
    {"LD\0", 1, NONE, true},
    {"LD-\0", 2, NONE, true},
    {"LD|\0", 3, NONE, true},
    {"LDmq\0", 10, NONE, false},
    {"LDmq_mx\0", 9, NONE, true},
    {"ST", 33, NONE, true},
    {"JMP", 13, LEFT, true},
    {"JMP", 14, RIGHT, true},
    {"JUMP+", 15, LEFT, true},
    {"JUMP+", 16, RIGHT, true},
    {"ADD", 5, NONE, true},
    {"ADD|", 7, NONE, true},
    {"SUB", 6, NONE, true},
    {"SUB|", 8, NONE, true},
    {"MUL", 11, NONE, true},
    {"DIV", 12, NONE, true},
    {"LSH\0", 20, NONE, false},
    {"RSH\0", 21, NONE, false},
    {"STaddr", 18, LEFT, true},
    {"STaddr", 19, RIGHT, true},
};

int main (int argc, char* argv[]) {
    type                            = NONE;
	memoryPosition                  = 0;
	instructionPos                  = LEFT;
    lineCounter                     = 0;
    instr_tree                      = NULL;
    labels                          = NULL;
    sym                             = NULL;
    word.left_instruction           = -1;
    word.left_argument              = -1;
    word.right_instruction          = -1;
    word.right_argument             = -1;
	fRead                           = fopen(argv[1], "r");
    char                            *input;
    
	if(fRead) {
        
		// Reads 'till the end of file (first cicle)
		while (fgets(line, MAXCHAR, fRead) != NULL) {
            input = strtok(line, " \t\n");
            while (input != NULL) {
                pre_process(input);
                input = strtok(NULL, " \t\n");
            }
            type = NONE;
            lineCounter++;
		}
        rewind(fRead);
        
        memoryPosition  = 0;
        instructionPos  = LEFT;
        lineCounter     = 0;
        
        while (fgets(line, MAXCHAR, fRead) != NULL) {
            input = strtok(line, " \t\n");
            while (input != NULL) {
                reader(input);
                input = strtok(NULL, " \t\n");
            }
            type = NONE;
            lineCounter++;
        }
        
        if(word.right_instruction == -1 && word.left_instruction != -1) {
            word.right_argument = 0;
            word.right_instruction = 0;
            instr_tree = insert_memory_map(instr_tree, memoryPosition, format_output(word.left_instruction, word.right_instruction, word.left_argument, word.right_argument));
        }
        if(argv[2] != NULL) {
            FILE* fWrite = fopen(argv[2], "w");
            print_memory_map_FILE(instr_tree, fWrite);
            fclose(fWrite);
        } else
            print_memory_map(instr_tree);
	}

    fclose(fRead);
	return 0;
}
