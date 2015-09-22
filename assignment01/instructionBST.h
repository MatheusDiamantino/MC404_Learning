#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct instructionTree
{
        int code;
        char mnemonic;
        struct treeNode *left;
        struct treeNode *right;

}instructionTree;

instructionTree* FindMin(instructionTree *node);
instructionTree* FindMax(instructionTree *node);
instructionTree * Insert(instructionTree *node,int code, char mnemonic[]);
instructionTree * Find(instructionTree *node, int code);
void PrintInorder(instructionTree *node);
void PrintPreorder(instructionTree *node);
void PrintPostorder(instructionTree *node);
