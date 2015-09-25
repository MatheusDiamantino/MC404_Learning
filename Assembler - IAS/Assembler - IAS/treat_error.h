//
//  treat_error.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/25/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#ifndef treat_error_h
#define treat_error_h

#include <stdio.h>
#include <string.h>

#include "defines.h"

void _error_bounds(long long int low_bound, long long int high_bound, long long int to_treat);
void _error_instruction_not_found(char *instruction);
void _error_no_argument_instruction(char *instruction, bool has_argument, bool is_comment);
void _error_word_on_right_instruction(char *instruction);
void _error_not_10_digit_HEX_number(char *number);
void _error_not_valid_number(char *number);

#endif /* treat_error_h */
