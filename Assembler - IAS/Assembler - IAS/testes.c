#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main () {
    
    char s[100];
    
    scanf("%s", s);
    char *c = strtok(s, " ");
    
    while(c != NULL) { c = strtok(NULL, " "); }
}