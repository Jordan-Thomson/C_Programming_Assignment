/*
 * c programming assignment: provide a user-friendly text menu for
 * the user to interact with the system and provide functionalities
 * to work with a list of sale items.
 * Part 3 of the assignment
 * Author: Jordan Thomson <jordan.thomson.2019@uni.strath.ac.uk>
 * Last updated: 19/03/2021
 */

#include "list.h"

typedef Node** List;

/* Display unsorted menu */
void unsorted_menu(List list);
/* Display sorted menu */
void sorted_menu(List list);
/* Get user input with prompt */
int get_value(char *text);

/**
 * Main function, asks user for list type and calls appropriate
 * function for that list.
 **/
int main(void) {
    printf("would you like to work with a sorted or unsorted list of sale items?\n");
    printf("1. Unsorted List\n");
    printf("2. Sorted List\n");
    printf("\n0. Quit\n");
    printf("\n>>>");
    int type = -1;
    List list = malloc(sizeof(List));
    *list = NULL;
    while (!scanf("%d", &type) || type > 2 || type < 0) {
        clear();
        printf("\aPlease enter a valid number: ");
    }
    if (type == 1) {
        unsorted_menu(list);
    }
    else if (type == 2) {
        sorted_menu(list);
    }
    // remove_all to call free on all nodes;
    remove_all(list);
    // free the list;
    free(list);
    return 0;
}

/**
 * Function to act as menu for an unsorted list
 * @param list  The list the menu will adapt
 **/
void unsorted_menu(List list) {
    int choice = -1;
    do {
        printf("\nChoose an option for an unsorted list of sale items:\n");
        printf("1. Add a new sale item at a specified position of the list\n");
        printf("2. Remove a sale item from a specified position of the list\n");
        printf("3. Print a sale item at a specified position\n");
        printf("4. Change position of a sale item\n");
        printf("5. Print all sale items\n");
        printf("6. Remove all sale items\n");
        printf("\n0. Quit\n");
        printf("\n>>> ");
        while (!(scanf("%d", &choice)) || choice > 6 || choice < 0) {
            clear();
            printf("\aPlease enter a valid number\n");
            printf("\n>>> ");
        }
        switch (choice) {
            case 1:
                insert_at(list, get_value("Position to insert: "), new_node(get_info_sale()));
                break;
            case 2:
                remove_at(list, get_value("Position to remove: "));
                break;
            case 3:
                print_node(get_node(*list,get_value("Position to print: ")));
                break;
            case 4:
                change_position(list,get_value("Position to place node at: "),get_value("Position of node to move: "));
                break;
            case 5:
                print_list(*list);
                break;
            case 6:
                remove_all(list);
                break;
            case 0:
                //System should continue back to main and quit;
                break;
            default:
                // we shouldn't get here but lets print something just in case :)
                printf("\n***Something went wrong***\n");
        }
    } while (choice != 0);
}

/**
 * Function to act as menu for a sorted list
 * @param list  The list the menu will adapt
 **/
void sorted_menu(List list) {
    int choice = -1;
    order = 1;
    do {
        printf("\nChoose an option for a sorted list of sale items in %s order:\n", order == 1 ? "ASCENDING" : "DESCENDING");
        printf("1. Add a new sale item\n");
        printf("2. Remove a sale item\n");
        printf("3. Print sale items in a range of sale ids\n");
        printf("4. Reverse the order\n");
        printf("5. Remove duplicates\n");
        printf("6. Print all sale items\n");
        printf("7. Remove all sale items\n");
        printf("\n0. Quit\n");
        printf("\n>>> ");
        while (!(scanf("%d", &choice)) || choice > 7 || choice < 0) {
                clear();
            printf("\aPlease enter a valid number\n");
            printf("\n>>> ");
        }
        switch (choice) {
            case 1:
                insert_byval(list, new_node(get_info_sale()));
                break;
            case 2:
                remove_byval(list, get_value("Sales ID to remove: "));
                break;
            case 3:
                print_range(*list, get_value("Enter sale id to: "), get_value("Enter sale id from: "));
                break;
            case 4:
                reverse_list(list);
                break;
            case 5:
                remove_duplicates(list);
                break;
            case 6:
                print_list(*list);
                break;
            case 7:
                remove_all(list);
                break;
            case 0:
                //System should continue back to main and quit;
                break;
            default:
                // we shouldn't get here but lets print something just in case :)
                printf("\n***Something went wrong***\n");
        }
    } while (choice != 0);
}

/**
 * returns an int value from the user using supplied string as
 * a prompt.
 * @param *text The string to prompt the user
 * @return int value the user entered.
 **/
int get_value(char *text) {
    int pos;
    printf("\n%s ", text);
    while (!scanf("%d", &pos)) {
        printf("\aMust be an integer: ");
        clear();
    }
    return pos;
}
