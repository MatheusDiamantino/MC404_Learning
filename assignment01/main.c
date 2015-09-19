/****************************************************************
* First Assignment: Assembler for the IAS Architecture          *
*                                                               *
* Written by: Matheus Mortatti Diamantino     RA: 156740        *
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bst.h"
#include "reader.h"
#include "typeEnum.h"

#define MAXCHAR 4096

int main (int argc, char* argv[]) {
	type t;
	// Labels found
	treeNode *labels;
	// Current memory position it's writting instructions
	int memoryPosition = 0;
	int lineCounter = 0;
	// The instruction, comment, directive or label it reads
	char input[MAXCHAR], instructionPos = 'E';
	// File
	FILE *fRead = fopen(argv[1], "r");

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
