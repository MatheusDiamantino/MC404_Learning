#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructionBST.h"

instructionTree* FindMin(treeNode *node) {
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
instructionTree* FindMax(instructionTree *node) {
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

instructionTree * Insert(instructionTree *node,int code, char mnemonic[]) {
        if(node==NULL)
        {
                treeNode *temp;
                temp = (instructionTree *)malloc(sizeof(instructionTree));
                temp -> code = code;
                temp -> mnemonic = mnemonic;
                temp -> left = temp -> right = NULL;
                return temp;
        }

        if(node -> code < code)
        {
                node->right = Insert(node->right, code, mnemonic);
        }
        else if(node -> code > code)
        {
                node->left = Insert(node->left,code, mnemonic);
        }
        /* Else there is nothing to do as the memPos is already in the tree. */
        return node;

}

instructionTree * Find(instructionTree *node, int code) {
        if(node==NULL)
        {
                /* Element is not found */
                return NULL;
        }
        if(node -> code < code)
        {
                /* Search in the right sub tree. */
                return Find(node->right,code);
        }
        else if(node -> code > code)
        {
                /* Search in the left sub tree. */
                return Find(node->left,code);
        }
        else
        {
                /* Element Found */
                return node;
        }
}

void PrintInorder(instructionTree *node) {
        if(node==NULL)
        {
                return;
        }
        PrintInorder(node->left);
        printf("%d %s\n", node -> code, node -> mnemonic);
        PrintInorder(node->right);
}

void PrintPreorder(instructionTree *node) {
        if(node==NULL)
        {
                return;
        }
        printf("%d ",node->code);
        PrintPreorder(node->left);
        PrintPreorder(node->right);
}

void PrintPostorder(instructionTree *node) {
        if(node==NULL)
        {
                return;
        }
        PrintPostorder(node->left);
        PrintPostorder(node->right);
        printf("%d ",node->code);
}
