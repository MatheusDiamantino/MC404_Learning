#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "typeEnum.h"


bool containsChar (char input[], char c) {
  int i;

	for(i = 0; i < strlen(input); i ++) {
		if(input[i] == c) {
			return true;
		}
	}

	return false;
}

/* Tells if the input is a label */
bool isLabel (char input[]) {
  int i;

  // Checks if it starts with a number
  if(input[0] >= '0' && input[strlen(input) - 1] <= '9') { return false; }

  // Checks if there's a colon in the middle of the input
  for(i = 0; i < strlen(input); i ++) {
  	if(input[i] == ':' && i != strlen(input) - 1) {
  		return false;
  	}
  }

  // After all the checks, if thereś a colon at the end, it is a Label
  if(input[strlen(input) - 1] == ':') { return true; }

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

type identifyType (char input[]) {
  type typeID;

  if (isDirective(input)) {
    typeID = DIRECTIVE;
  } else if (isLabel(input)) {
    typeID = LABEL;
  } else if (isComment(input)) {
    typeID = COMMENT;
  } else {
    typeID = INSTRUCTION;
  }

  return typeID;
}
