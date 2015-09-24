//
//  memory_map_BST.h
//  Assembler - IAS
//
//  Created by Matheus Diamantino on 9/23/15.
//  Copyright © 2015 Matheus Diamantino. All rights reserved.
//

#ifndef memory_map_BST_h
#define memory_map_BST_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct memory_map_tree
{
    int                         memory_position;
    char                        word[13];
    struct memory_map_tree      *left;
    struct memory_map_tree      *right;
    
}memory_map_tree;

memory_map_tree * insert_memory_map(memory_map_tree *node,int memory_position, char *word);
memory_map_tree * find_memory_map(memory_map_tree *node, int memory_position);
void print_memory_map (memory_map_tree *node);
void print_memory_map_FILE (memory_map_tree *node, FILE* f);


#endif /* memory_map_BST_h */
