#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labelBST.h"

treeNode* FindMin(treeNode *node)
{
        if(node==NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(node->left) /* Go to the left sub tree to find the min element */
                return FindMin(node->left);
        else
                return node;
}
treeNode* FindMax(treeNode *node)
{
        if(node==NULL)
        {
                /* There is no element in the tree */
                return NULL;
        }
        if(node->right) /* Go to the left sub tree to find the min element */
                FindMax(node->right);
        else
                return node;
}

treeNode * Insert(treeNode *node,int memPos, char label[], char instruction)
{
        if(node==NULL)
        {
                treeNode *temp;
                temp = (treeNode *)malloc(sizeof(treeNode));
                temp -> memPos = memPos;
                temp -> label = malloc(sizeof(strlen(label)));
                strcpy((temp -> label), label);
                temp -> instruction = instruction;
                temp -> left = temp -> right = NULL;
                return temp;
        }

        if(strcmp(label, node->label) > 0)
        {
                node->right = Insert(node->right,memPos, label, instruction);
        }
        else if(strcmp(label, node->label) < 0)
        {
                node->left = Insert(node->left,memPos, label, instruction);
        }
        /* Else there is nothing to do as the memPos is already in the tree. */
        return node;

}

treeNode * Find(treeNode *node, char label[])
{
        if(node==NULL)
        {
                /* Element is not found */
                return NULL;
        }
        if(strcmp(label, node->label) > 0)
        {
                /* Search in the right sub tree. */
                return Find(node->right,label);
        }
        else if(strcmp(label, node->label) < 0)
        {
                /* Search in the left sub tree. */
                return Find(node->left,label);
        }
        else
        {
                /* Element Found */
                return node;
        }
}

void PrintInorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        PrintInorder(node->left);
        printf("%d %s %c\n", node -> memPos, node -> label, node -> instruction );
        PrintInorder(node->right);
}

void PrintPreorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        printf("%d ",node->memPos);
        PrintPreorder(node->left);
        PrintPreorder(node->right);
}

void PrintPostorder(treeNode *node)
{
        if(node==NULL)
        {
                return;
        }
        PrintPostorder(node->left);
        PrintPostorder(node->right);
        printf("%d ",node->memPos);
}

/*
int main(){

  treeNode *node = NULL;
  node = Insert(node, 1, "Rótulo1", 'E');
  node = Insert(node, 1, "Rótulo2", 'D');
  PrintPostorder(node);
  PrintInorder(node);
  PrintPreorder(node);

  return 0;
}*/
