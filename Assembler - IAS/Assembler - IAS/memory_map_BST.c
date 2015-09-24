//
//  memory_map_BST.c
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/23/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "memory_map_BST.h"

memory_map_tree * insert_memory_map(memory_map_tree *node,int memory_position, char *word)
{
    int i = 0;
    if(node==NULL)
    {
        memory_map_tree *temp;
        temp = (memory_map_tree *)malloc(sizeof(memory_map_tree));
        temp -> memory_position = memory_position;
        
        while(word[i])
        {
            
            word[i] = toupper(word[i]);
            i++;
        }
        
        strcpy(temp -> word, word);
        temp -> left = temp -> right = NULL;
        return temp;
    }
    
    if(memory_position > node -> memory_position)
    {
        node->right = insert_memory_map(node->right,memory_position, word);
    }
    else if(memory_position < node -> memory_position)
    {
        node->left = insert_memory_map(node->left,memory_position, word);
    }
    /* Else there is nothing to do as the memPos is already in the tree. */
    return node;
    
}

memory_map_tree * find_memory_map(memory_map_tree *node, int memory_position)
{
    if(node==NULL)
    {
        /* Element is not found */
        return NULL;
    }
    if(memory_position > node -> memory_position)
    {
        /* Search in the right sub tree. */
        return find_memory_map(node->right,memory_position);
    }
    else if(memory_position < node -> memory_position)
    {
        /* Search in the left sub tree. */
        return find_memory_map(node->left,memory_position);
    }
    else
    {
        /* Element Found */
        return node;
    }
}

void print_memory_map (memory_map_tree *node) {
    
    if(node != NULL) {
        print_memory_map(node -> left);
        printf("%0.3X %s\n", node -> memory_position, node -> word);
        print_memory_map(node -> right);
    }
    
}

void print_memory_map_FILE (memory_map_tree *node, FILE* f) {
    
    if(node != NULL) {
        print_memory_map_FILE(node -> left, f);
        fprintf(f, "%0.3X %s\n", node -> memory_position, node -> word);
        print_memory_map_FILE(node -> right, f);
    }
    
}
