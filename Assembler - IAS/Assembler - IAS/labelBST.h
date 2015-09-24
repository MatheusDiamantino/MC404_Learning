#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

typedef struct label_tree
{
        long int memPos;
        char *label;
        short int instruction;
        struct label_tree *left;
        struct label_tree *right;

}label_tree;

label_tree * Insert(label_tree *node,long long int memPos, char label[], short int instruction);
label_tree * Find(label_tree *node, char label[]);
void print_labels (label_tree *node);