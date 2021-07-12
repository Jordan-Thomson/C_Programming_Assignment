/*
 * c programming assignment: header file for nodes
 * Author: Jordan Thomson <jordan.thomson.2019@uni.strath.ac.uk>
 * Last updated: 27/02/2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNIT_SALE 1
#define WEIGHT_SALE 2
#define VOLUME_SALE 3

// struct of a sales line
typedef struct {
	int sale_id;
	char name[50];
	int sale_type;
	union {
		int number;
		float weight;
		float volume;
	} amount;
	float price;
} Sale;

// struct of a node for a linked list
typedef struct NODE {
	Sale value;
	struct NODE *next;
} Node;

// print a node, calls print sale
void print_node(Node *node);
// print a sale
void print_sale(Sale sale);
// create a new node
Node *new_node(Sale value);
// create a new sale
Sale set_sale(int sale_id, char name[], int type, float amount, float price);
// create a new sale with input from terminal
Sale get_info_sale();
// helper function for input from terminal
void clear();
// helper function to get a positive numeric value
float get_number();
