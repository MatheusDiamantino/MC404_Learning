//
//  treat_type.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/22/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#ifndef treat_type_h
#define treat_type_h

void treat_label(char input[]);
void treat_comment(char input[]);
void treat_directive(char input[]);
void treat_instruction(char input[]);

#endif /* treat_type_h */
