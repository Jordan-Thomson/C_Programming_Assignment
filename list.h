/*
 * c programming assignment: The provided list.h code from the
 * assignment. All original code still here, commented out pragma once
 *
 * Author: Jordan Thomson 
 * Last updated: 12/03/2021
 */
 //#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

// Obtains and returns the node at the given position
// If the given position doesn't exist returns NULL
Node * get_node (Node *, int position);

// Inserts a new node at the given position
// if the given position exists
void insert_at (Node **, int , Node *);

// Removes and frees the node at the given position
// if the given position exists
void remove_at (Node **, int position);

// Removes all nodes by calling remove_at
void remove_all(Node **);

// Prints all nodes by calling print_node
void print_list(Node *);

//////////////////////////////////////////
// NEW FOR PART 2 AND 3                 //
//////////////////////////////////////////
#define ASC 1  // constant for ascending order
#define DESC -1  // constant for descending order

int order;  // ASC or DESC
void reverse_list(Node ** olist) ;
void insert_byval(Node **, Node *newNode);
void remove_byval(Node **list, int value);
void print_range(Node *list, int val1, int val2);

/* Change position of a node */
void change_position(Node **list, int to_pos, int from_pos);
/* Removes duplicates in a sorted list */
void remove_duplicates(Node **list);
