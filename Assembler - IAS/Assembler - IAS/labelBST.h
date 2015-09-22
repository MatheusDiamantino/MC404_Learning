#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode
{
        int memPos;
        char *label;
        short int instruction;
        struct treeNode *left;
        struct treeNode *right;

}treeNode;

#define LEFT 1
#define RIGHT 0
#define NONE 2

treeNode* FindMin(treeNode *node);
treeNode* FindMax(treeNode *node);
treeNode * Insert(treeNode *node,int memPos, char label[], short int instruction);
treeNode * Find(treeNode *node, char label[]);
void PrintInorder(treeNode *node);
void PrintPreorder(treeNode *node);
void PrintPostorder(treeNode *node);
