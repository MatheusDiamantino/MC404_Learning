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

FILE                *fRead;
label_tree          *labels;
short int           memoryPosition;
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
    {"JMP+", 16, RIGHT, true},
    {"ADD", 5, NONE, true},
    {"ADD|", 7, NONE, true},
    {"SUB", 6, NONE, true},
    {"SUB|", 8, NONE, true},
    {"MUL", 11, NONE, true},
    {"DIF", 12, NONE, true},
    {"LSH", 14, NONE, false},
    {"RSH", 15, NONE, false},
    {"STaddr", 12, LEFT, true},
    {"STaddr", 13, RIGHT, true},
};

int main (int argc, char* argv[]) {
	inputType t;
	memoryPosition = 0;
	instructionPos = LEFT;
    lineCounter = 0;
	// The instruction, comment, directive or label it reads
	char input[MAXCHAR];
	// File
	fRead = fopen(argv[1], "r");

	if(fRead) {
		fscanf(fRead, "%s", input);

		// Reads 'till the end of file (first cicle)
		while (!feof(fRead)) {
			t = identifyType(input);
			fscanf(fRead, "%s", input);
		}
	}
    
    printf("%s", instruction_list[0].mnemonic);

	PrintInorder(labels);

	return 0;
}
