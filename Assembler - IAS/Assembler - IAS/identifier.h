//
//  identifier.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/23/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#ifndef identifier_h
#define identifier_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "typeEnum.h"
#include "readInput.h"
#include "labelBST.h"
#include "instruction.h"
#include "treat_type.h"
#include "treat_MMP.h"

bool isInstruction(char input[]);
bool isLabel (char input[]);
bool isDirective (char input[]);
bool isComment (char input[]);
inputType identifyType (char input[]);
void main_process(char input[]);
void pre_process(char input[]);
void verify_order(inputType t);


#endif /* identifier_h */
