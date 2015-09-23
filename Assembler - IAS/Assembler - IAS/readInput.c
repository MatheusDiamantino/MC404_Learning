#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "readInput.h"

extern FILE *fRead;
extern int lineCounter;

// Reads the rest of the line
void read_junk() {
  char c = ' ';

  while(c != '\n') { c = fgetc(fRead); }

  return;
}

// Reads a generic input and return if it has reached the ond of a line or not
bool read_input(char input[]) {
    int line_break;
    fscanf(fRead, "%s", input);
    
    /* char c;
    int i = 0;

    c = fgetc(fRead);

    while(c == ' ' || c == '\t') { c = fgetc(fRead); }

    while(c != ' ' && c != '\n' && c != EOF && c != '\t' && i < strlen(input)) {
        input[i] = c;
        i++;
        c = fgetc(fRead);
    }
    input[i] = '\0';*/
    
    line_break = fgetc(fRead);

    if(line_break == '\n') return true;
    else return false;
}

// Reads a number and returns if it has reached the end of a line or not (VERIFIES IF ITS NOT IN THE FORMAT SPECIFIED!!!!)
bool read_number_generic(long long int *n) {
    char *c, *str, *ptr = NULL;
    int line_break;
    
    fscanf(fRead, "%s", c);
    str = strtok(c, "\"");
    
    *n = strtoll(str, &ptr, 0);
    
    if(ptr != NULL) {
        if(strlen(c) > 2 && c[0] == '0' && c[1] == 'x')
            fprintf(stderr, "ERROR on line %d\n%s is not a valid HEX number", lineCounter, str);
        else
            fprintf(stderr, "ERROR on line %d\n%s is not a valid DEC number", lineCounter, str);
        exit(1);
    }
    
    /* char c;
    int i = 0, size = strlen(input);

    fscanf(fRead, "%c", &c);
    while(c == ' ') { fscanf(fRead, "%c", &c); }
    fscanf(fRead, "%c", &c);

    while (c != '"' && c != EOF && i < size) {
        input[i] = c;
        i++;
        fscanf(fRead, "%c", &c);
    }
    input[i] = '\0';*/
    
    line_break = fgetc(fRead);
    
    if(line_break == '\n') { lineCounter++; return true; }
    else { return false; }
    
}

void read_number(int *n) {
    fscanf(fRead, "%d", n);
    return;
}
