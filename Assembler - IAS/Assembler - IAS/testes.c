#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int main () {
    
        int i = 0;
        char c;
        char str[] = "Tutorials Point 34";
        
        while(str[i])
        {
            putchar (toupper(str[i]));
            i++;
        }
        
        return(0);
}