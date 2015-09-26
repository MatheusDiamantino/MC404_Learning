#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "readInput.h"
#include "treat_error.h"

extern char     *line;
extern FILE     *fRead;
extern int      lineCounter;

/* --------------------------------------------------
 *
 * Read rest of the line
 *
 * ------------------------------------------------- */
void read_junk() {
    char *c = strtok(NULL, " ");

    while(c != NULL) { c = strtok(NULL, " "); }

  return;
}

/* --------------------------------------------------
 *
 * Reads a generic input and returns whether it has 
 * next input or not
 *
 * ------------------------------------------------- */
bool read_input(char input[]) {
    char *str = strtok(NULL, " \t\n\"");
    
    
    
    if(str != NULL) {
        _error_not_10_digit_HEX_number(str);        // In case input is a HEX not valid
        strcpy(input, str);
        return true;
    }
    else {
        input[0] = '\0';
        return false;
    }
    
}

/* --------------------------------------------------
 *
 * Reads either a HEX or DEC number and returns if succeeded
 *
 * ------------------------------------------------- */
bool read_number_generic(long long int *n) {
    char    *str,
            *ptr = NULL;
    
    str = strtok(NULL, " \"\t\n");
    
    if(str == NULL) return false;
    
    _error_not_10_digit_HEX_number(str);                // Verifies if it's a valid 10 digit HEX
    
    *n = strtoll(str, &ptr, 0);
    
    if(strcmp(ptr, "\0")) {
        
        _error_not_valid_number(str);                   // It's not a valid number
        
    }
    
    return true;
}

/* --------------------------------------------------
 *
 * Transform a string input into a long long int number
 *
 * ------------------------------------------------- */
long long int convert_string_number(char input[]) {
    char                *ptr = NULL;
    long long int       n;
    
    n = strtoll(input, &ptr, 0);
    
    if(strcmp(ptr, "\0")) {                             // Func strtoll returned a pointer that's not the end of array given
        
        _error_not_valid_number(input);                 // It's not a valid number
        
    }
    
    return n;
}

/* --------------------------------------------------
 *
 * Verifies if string given is a number
 *
 * ------------------------------------------------- */
bool string_is_number(char *input) {
    char *ptr = NULL;
    
    strtoll(input, &ptr, 0);
    
    return !strcmp(ptr, "\0");
}


/* --------------------------------------------------
 *
 * Receives a number and returns it in the string output format
 *
 * ------------------------------------------------- */
char* format_output_HEX(long long int num) {
    char hex[18], *aux = malloc(14 * sizeof(char));
    
    sprintf(hex, "%.17llx", num);
    
    
    aux[0] = hex[7];
    aux[1] = hex[8];
    aux[2] = ' ';
    aux[3] = hex[9];
    aux[4] = hex[10];
    aux[5] = hex[11];
    aux[6] = ' ';
    aux[7] = hex[12];
    aux[8] = hex[13];
    aux[9] = ' ';
    aux[10] = hex[14];
    aux[11] = hex[15];
    aux[12] = hex[16];
    aux[13] = '\0';
    
    return aux;
}


/* --------------------------------------------------
 *
 * Receives instructions and arguments and formats into output string
 *
 * ------------------------------------------------- */
char* format_output(long long int l_instr, long long int r_instr, long long int l_arg, long long int r_arg) {
    char *aux, *str = malloc(14 * sizeof(char));
    aux = str;
    
    sprintf(str, "%.2llx", l_instr);
    str[2] = ' ';
    str += 3;
    sprintf(str, "%.3llx", l_arg);
    str[3] = ' ';
    str += 4;
    sprintf(str, "%.2llx", r_instr);
    str[2] = ' ';
    str += 3;
    sprintf(str, "%.3llx", r_arg);
    aux[13] = '\0';
    
    return aux;
    
}
