#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readInput.h"

extern FILE *fRead;

// Reads the rest of the line
void readJunk() {
  char c = ' ';

  while(c != '\n') { fscanf(fRead, "%c", &c); }

  return;
}

char* readInput() {
  char input[64], c;
  int i = 0;

  fscanf(fRead, "%c", &c);
  while(c != ' ' && c != '\n') {
    input[i] = c;
    i++;
    fscanf(fRead, "%c", &c);
  }
  input[i] = '\0';

  return input;
}

char* readNumber() {
  char input[11], c;
  int i = 0;

  fscanf(fRead, "%c", &c);
  fscanf(fRead, "%c", &c);

  while (c != '"') {
    input[i] = c;
    i++;
    fscanf(fRead, "%c", &c);
}
  input[i] = '\0';

  return input;
}
