//
//  treat_MMP.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

#include "treat_MMP.h"
#include "defines.h"

extern short int memoryPosition;
extern short int instructionPos;

void _increment(bool is_word) {
    if(!is_word) {
        if(instructionPos == LEFT) instructionPos = RIGHT;
        else {
            instructionPos = LEFT;
            memoryPosition++;
        }
    } else memoryPosition++;
}

void _change_position (short int new) { memoryPosition = new; }