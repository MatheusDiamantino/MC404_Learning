#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labelBST.h"

label_tree * Insert(label_tree *node,long long int memPos, char label[], short int instruction)
{
        if(node==NULL)
        {
                label_tree *temp;
                temp = (label_tree *)malloc(sizeof(label_tree));
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

label_tree * Find(label_tree *node, char label[])
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

void print_labels (label_tree *node) {
    
    if(node != NULL) {
        print_labels(node -> left);
        printf("%0.3ld %s\n", node -> memPos, node -> label);
        print_labels(node -> right);
    }
    
}
