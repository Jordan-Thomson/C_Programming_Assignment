/*
 * c programming assignment: c code to produce functionality
 * relating to nodes and sales structures
 * Author: Jordan Thomson <jordan.thomson.2019@uni.strath.ac.uk>
 * Last updated: 04/03/2021
 */

#include "node.h"

/**
 * creates and returns a sale struct
 * @param sale_id integer representing the id of the sale
 * @param name the name of the item sold
 * @param type the type of sale (1=UNIT_SALE, 2=WEIGHT_SALE, 3=VOLUME_SALE)
 * @param amount the quantity being sold, should be representative of the type
 * @param price the price of one unit/Kg/Ltr of item
 * @return newly created sale struct
 **/
Sale set_sale(int sale_id, char name[], int type, float amount, float price) {
    Sale sale;
	sale.sale_id = sale_id;
	strcpy(sale.name,name);
	sale.sale_type = type;
	if (type==UNIT_SALE) {
		sale.amount.number = amount;
	}
	else if (type==WEIGHT_SALE) {
		sale.amount.weight = amount;
	}
	else {
		sale.amount.volume = amount;
	}
	sale.price = price;
	return sale;
}

/**
 * Creates and returns a node with a sale struct as its data
 * @param value the Sale struct to be held in the node
 * @return the newly created node
 **/
Node *new_node(Sale value) {
	Node *node = malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	return node;
}

/**
 * prints details of a node using print_sale
 * @param *node the node to print detail of
 **/
void print_node(Node *node) {
    if (node == NULL) {
        printf("No node to print!\n");
    }
    else {
        print_sale(node->value);
    }
}

/**
 * Prints a sales line, uses the sale_type field to decide output.
 * @param sale the sale struct to print detail of
 **/
void print_sale(Sale sale) {
	if (sale.sale_type == UNIT_SALE) {
		printf("Sale id %d: %d %s(s) at %c%.2f each = %c%.2f\n",
          sale.sale_id, sale.amount.number, sale.name, 156, sale.price, 156 ,sale.price * sale.amount.number);
	}
	else if (sale.sale_type == WEIGHT_SALE) {
		printf("Sale id %d: %.2f KG of %s at %c%.2f per KG = %c%.2f\n",
         sale.sale_id, sale.amount.weight, sale.name, 156, sale.price, 156, sale.price * sale.amount.weight);
	}
	else if (sale.sale_type == VOLUME_SALE) {
		printf("Sale id %d: %.2f L of %s at %c%.2f per L = %c%.2f\n",
         sale.sale_id, sale.amount.volume, sale.name, 156, sale.price, 156, sale.price * sale.amount.volume);
	}
}

/**
 * Retrieves input from terminal to create a sales struct
 * @return sales struct that was created from input
 **/
Sale get_info_sale() {
	Sale sale;
	printf("Enter sale_id: ");
	// must be a number
	sale.sale_id = (int) get_number();
	printf("Enter product name: ");
	clear();// remove the previous \n
	fgets(sale.name, 50, stdin);
	clear();// in case of a buffer overflow
	printf("Enter sale type: ");
    // must be value, 1, 2 or 3
	do {
		scanf(" %i", &sale.sale_type);
		clear();
		if (sale.sale_type == UNIT_SALE) {
            printf("Enter Quantity: ");
            // must be a number
            sale.amount.number = (int) get_number();
		}
		else if (sale.sale_type == WEIGHT_SALE) {
			printf("Enter weight: ");
			// must be a number
			sale.amount.weight = get_number();
		}
		else if (sale.sale_type == VOLUME_SALE) {
			printf("Enter volume: ");
			// must be a number
			sale.amount.volume = get_number();
		}
		else {
			printf("\aSale type must be a number between 1 and 3\n1 = UNIT_SALE; 2 = WEIGHT_SALE; 3 = VOLUME_SALE");
			printf("\n>>> ");
		}
	} while (sale.sale_type > 3 || sale.sale_type <= 0);
	printf("Enter sale price: ");
	// must be a number
	sale.price = get_number();
	print_sale(sale);
	return sale;
}

/**
 * Function to reduce code duplication in get_sale_info
 * @return float numeric greater than 0
 **/
float get_number() {
    float num;
    while (!(scanf(" %f", &num)) || num <= 0) {
        clear();
        printf("\aPlease enter a positive numeric value ");
        printf("\n>>> ");
    }
    return num;
}

/**
 * function to support data entry from scanf() by clearing
 * the buffer
 **/
void clear() {
	while ((getchar()) != '\n');
}
