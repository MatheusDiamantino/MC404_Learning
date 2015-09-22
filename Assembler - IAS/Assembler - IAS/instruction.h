//
//  instruction.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>

#ifndef instruction_h
#define instruction_h

typedef struct instruction {
    
    char mnemonic[8];
    short int code;
    short int lr_instr;
    bool expect_argument;
    
} instruction;


#endif /* instruction_h */
