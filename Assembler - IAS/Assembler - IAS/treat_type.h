//
//  treat_type.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#ifndef treat_type_h
#define treat_type_h

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "labelBST.h"
#include "defines.h"
#include "readInput.h"
#include "instruction.h"
#include "identifier.h"
#include "memory_map_BST.h"

typedef struct memory_word {
    long long int word;
    long long int left_instruction, left_argument;
    long long int right_instruction, right_argument;
}memory_word;

void treat_label(char input[]);
void treat_comment(char input[]);
void treat_directive(char input[]);
void treat_instruction(char input[]);

#endif /* treat_type_h */
