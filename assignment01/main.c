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
#include "reader.h"
#include "typeEnum.h"
#include "instructionBST.h"

#define MAXCHAR 4096

FILE *fRead;
treeNode *labels;
int memoryPosition;
char instructionPos;
instructionTree *instruction;

int main (int argc, char* argv[]) {
	inputType t;
	memoryPosition = 0;
	instructionPos = 'E';
	int lineCounter = 0;
	// The instruction, comment, directive or label it reads
	char input[MAXCHAR];
	// File
	fRead = fopen(argv[1], "r");

	if(fRead) {
		fscanf(fRead, "%s", input);

		// Reads 'till the end of file' (first cicle)
		while (!feof(fRead)) {
			t = identifyType(input);
			printf("%d\n", t);
			fscanf(fRead, "%s", input);
		}
	}

	PrintInorder(labels);

	return 0;
}
