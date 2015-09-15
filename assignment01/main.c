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

#define MAXCHAR 4096

bool isLabel (char command[]);

int main (int argc, char* argv[]) {
	// Labels found
	treeNode *labels;
	// Current memory position it's writting instructions
	int memoryPosition = 0;
	int lineCounter = 0;
	// The instruction, comment, directive or label it reads
	char command[MAXCHAR], instructionPos = 'E';
	// File
	FILE *fRead = fopen(argv[1], "r");

	if(fRead) {
		fscanf(fRead, "%s", command);

		// Reads 'till the end of file' (first cicle)
		while (!feof(fRead)) {

			// Insert label if it finds one
			if(isLabel(command)) {
				labels = Insert(labels, memoryPosition, command, instructionPos);
				}

			}
			fscanf(fRead, "%s", command);
		}

	}

	PrintInorder(labels);

	return 0;
}

bool isLabel (char command[]) {
	int i;
	char c = ':';

	for(i = 0; i < strlen(command); i ++) {
		if(command[i] == c) {
			return true;
		}
	}
	return false;
}
