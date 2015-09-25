#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool string_is_number(char *input);
void read_junk();
bool read_input(char input[]);
long long int convert_string_number(char input[]);
bool read_number_generic(long long int *n);
char* format_output_HEX(long long int num);
char* format_output(long long int l_instr, long long int r_instr, long long int l_arg, long long int r_arg);