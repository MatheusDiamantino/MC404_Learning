#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "typeEnum.h"
#include "readInput.h"
#include "labelBST.h"
#include "instruction.h"

extern treeNode *labels;
extern int memoryPosition;
extern short int instructionPos;
extern instruction instruction_list[20];

void identifyDirective(char input[]) {

}

void identifyInstruction(char input[]) {

}

void storeLabel(char input[]) {

}

bool containsChar (char input[], char c) {
  int i;
  int size_str = strlen(input);

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
    
    return false;
}

/* Checks if the input is a label */
bool isLabel (char input[]) {
  int i;
  int size_str = strlen(input);

  // Checks if it starts with a number
  if(input[0] >= '0' && input[0] <= '9') { return false; }

  // Checks if there's a colon in the middle of the input
  for(i = 0; i < size_str; i ++) {
  	if(input[i] == ':' && i != size_str - 1) {
  		return false;
  	}
  }

  // After all the checks, if there's a colon at the end, it is a Label
  if(input[size_str - 1] == ':') { return true; }

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
        if(instructionPos == RIGHT) {
            instructionPos = LEFT;
            memoryPosition++;
        } else instructionPos = RIGHT;
        
      return INSTRUCTION;
    }

    return ERROR;

}

void reader(char input[]) {
  inputType type;

  type =  identifyType(input);

  switch (type) {
    case DIRECTIVE:
      identifyDirective(input);
      break;
    case COMMENT:
      read_junk();
      break;
    case LABEL:
      // Store label found
      Insert(labels, memoryPosition, input, instructionPos);
      break;
    case INSTRUCTION:
      identifyInstruction(input);
      break;
  }

}
