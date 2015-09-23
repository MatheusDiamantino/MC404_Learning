#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct label_tree
{
        long int memPos;
        char *label;
        short int instruction;
        struct label_tree *left;
        struct label_tree *right;

}label_tree;

#define LEFT 1
#define RIGHT 0
#define NONE 2

label_tree * Insert(label_tree *node,long int memPos, char label[], short int instruction);
label_tree * Find(label_tree *node, char label[]);