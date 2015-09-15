#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode
{
        int memPos;
        char *label;
        char instruction;
        struct treeNode *left;
        struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode *node);
treeNode* FindMax(treeNode *node);
treeNode * Insert(treeNode *node,int memPos, char label[], char instruction);
treeNode * Find(treeNode *node, char label[]);
void PrintInorder(treeNode *node);
void PrintPreorder(treeNode *node);
void PrintPostorder(treeNode *node);
