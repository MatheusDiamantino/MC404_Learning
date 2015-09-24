#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readInput.h"

extern char     *line;
extern FILE     *fRead;
extern int      lineCounter;

// Reads the rest of the line
void read_junk() {
    char *c = strtok(NULL, " ");

    while(c != NULL) { c = strtok(NULL, " "); }

  return;
}

// Reads a generic input and return if it has reached the ond of a line or not
bool read_input(char input[]) {
    char *str = strtok(NULL, " \t\n\"");
    if(str != NULL) {
        strcpy(input, str);
        return true;
    }
    else {
        input[0] = '\0';
        return false;
    }
    
}

/*
 * Reads a number and returns if it has reached the end of a line or not (VERIFIES IF ITS NOT IN THE FORMAT SPECIFIED!!!!)
 */
bool read_number_generic(long long int *n) {
    char    *c,
            *str,
            *ptr = NULL;
    
    str = strtok(NULL, " \"\t\n");
    
    if(str == NULL) return false;
    
    if(strlen(str) != 12 && str[1] == 'x') {
        fprintf(stderr, "ERROR on line %d\n%s is not a 10 digit HEX number\n", lineCounter, str);
        exit(1);
    }
    
    *n = strtoll(str, &ptr, 0);
    
    if(strcmp(ptr, "\0")) {
        if(strlen(c) > 2 && c[0] == '0' && c[1] == 'x')
            fprintf(stderr, "ERROR on line %d\n%s is not a valid HEX number1\n", lineCounter, str);
        else if (strlen(c) > 2 && c[1] != 'x')
            fprintf(stderr, "ERROR on line %d\n%s is not a valid DEC number2\n", lineCounter, str);
        exit(1);
    }
    
    return true;
}

long long int convert_string_number(char input[]) {
    char *ptr = NULL;
    long long int n;
    n = strtoll(input, &ptr, 0);
    
    if(strcmp(ptr, "\0")) {
        if(strlen(input) > 2 && input[0] == '0' && input[1] == 'x')
            fprintf(stderr, "ERROR on line %d\n%s is not a valid HEX number3\n", lineCounter, input);
        else if (strlen(input) > 2 && input[1] != 'x') {
            fprintf(stderr, "ERROR on line %d\n%s is not a valid DEC number4\n", lineCounter, input);
        }
        exit(1);
    }
    
    return n;
}

void read_number(int *n) {
    fscanf(fRead, "%d", n);
    return;
}

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
