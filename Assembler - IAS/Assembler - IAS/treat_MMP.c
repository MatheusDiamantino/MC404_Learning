//
//  treat_MMP.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>

#include "treat_MMP.h"
#include "defines.h"

extern short int memoryPosition;
extern short int instructionPos;

void _increment() {
    if(instructionPos == LEFT) instructionPos = RIGHT;
    else {
        instructionPos = LEFT;
        memoryPosition++;
    }
}

void _change_position (short int new) { memoryPosition = new; }