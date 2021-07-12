/*
 * c programming assignment: c code to implement functionality
 * of lists using nodes
 * Author: Jordan Thomson
 * Last updated: 13/03/2021
 */

#include "list.h"

/**
 * Returns a node at a position, if the position doesn't
 * exist returns NULL instead
 * @param *list  The list to search for the node
 * @param p The position of the node to return
 **/
Node * get_node (Node *list, int p) {
    int index =0; // so we don't look at anything beyond p
    // iterate through the list until we find the position or reach the end
    while (list != NULL && index <= p) {
        if (index == p) {
            return list; // return the found node
        }
        index ++;
        list = list->next;
    }
    return NULL; // return null if not found
}

/**
 * Inserts a node into the list at the supplied position if it exists
 * as position 0 is head of a list - will insert in an empty list
 * @param **plist The list to insert a node into
 * @param p The position in the list to insert the node at
 * @param *newNode   The node to be inserted into the list
 **/
void insert_at (Node **plist, int p, Node *newNode) {
    if (p == 0) {
        if (*plist != NULL) {
            newNode->next = *plist;
        }
        *plist = newNode;
    }
    else if (p > 0 && plist != NULL) {
        Node *prev = get_node(*plist, p-1);
        if (prev != NULL) {
            Node *next = prev->next;
            prev->next = newNode;
            newNode->next = next;
        }
        else {
            printf("\a\nInvalid insert Position\n");
        }
    }
    else {
        printf("\a\nInvalid insert Position\n");
    }
}

/**
 * Removes a node at a position in the list
 * @param **plist the list to remove item from
 * @param p the position of the node to be removed
 **/
void remove_at (Node **plist, int p) {
    // if the list isn't empty and the position isn't negative
    if (*plist != NULL && p >= 0) {
        Node *remove_node = NULL;
        // if the position is 0, (the head)
        if (p == 0) {
            remove_node = *plist;
            *plist = remove_node->next;
            remove_node->next = NULL;
            free(remove_node);
        }
        // otherwise use get_node() to find the node before the node we want to remove
        // as it is the one we need to update
        else if (p > 0) {
            Node *node = get_node(*plist, p-1);
            if (node != NULL && node->next != NULL) {
                remove_node = node->next;
                node->next = remove_node->next;
                remove_node->next = NULL;
                free(remove_node);
            }
            else {
                printf("\a\nInvalid Position\n");
            }
        }
    }
    else {
        printf("\a\nInvalid Position\n");
    }
}

/**
 * Removes all nodes from a list by calling remove_at on each node
 * in the list
 * @param **plist the list to be emptied
 **/
void remove_all(Node **plist) {
    while (*plist != NULL) {
        remove_at(plist,0);
    }
    *plist = NULL; // this may be redundant?
}

/**
 * Prints all nodes in a list, if the list is empty
 * displays text explaining this
 * @param *list the list to be printed
 **/
void print_list(Node *list) {
    if (list != NULL) {
        while (list != NULL) {
            print_node(list);
            list = list->next;
        }
    }
    else {
        printf("The list is empty!\n");
    }
}

/**
 * Restructures list in reverse of current
 * order such that 1->2->3 becomes 3->2->1
 * and swaps the value of order
 * @param **olist The list to re-ordered.
 **/
void reverse_list(Node **olist) {

    Node *previous = NULL;
    Node *next = NULL;
    Node *current = *olist;
    // iterate through the list, stores the next node, updates this node
    // then sets the precious node to this node
    // then updates this node to the next for the next iteration
    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    // update the head of the list then switch the order
    *olist = previous;
    order = order*-1;
}

/**
 * Inserts a node into a list by sale_id keeping
 * a sorted order to the list
 * @param **list  The list to add a node to
 * @param *newNode   The node to be inserted into the list
 **/
void insert_byval(Node **list, Node *newNode) {
    Node *current = *list;
    // if the list is empty or the new node should be entered before the head
    if (current == NULL ||
       (current->value.sale_id > newNode->value.sale_id && order == ASC) ||
       (current->value.sale_id < newNode->value.sale_id && order == DESC)) {
        newNode->next = current;
        *list = newNode;
    }
    // otherwise iterate through the list until insert position is found.
    else {
        while (current->next != NULL &&
              ((current->next->value.sale_id < newNode->value.sale_id && order == ASC) ||
               (current->next->value.sale_id > newNode->value.sale_id && order == DESC))) {
            current = current->next;
        }
        // we either reach the desired point in the list or the end of the list
        newNode->next = current->next;
        current->next = newNode;
    }
}

/**
 * Removes a node from the list by sale_id keeping
 * a sorted order to the list.
 * @param **list  The list to remove an item from.
 * @param value The sale_id of a node to be removed.
 **/
void remove_byval(Node **list, int value) {
    // if the list is empty we don't need to do this
    if (*list != NULL) {
        Node *current = *list;
        // iterate through the list to find a match
        while (current->next != NULL &&
              ((current->next->value.sale_id <= value && order == ASC) ||
               (current->next->value.sale_id >= value && order == DESC))) {
            // if the next node would be a match
            // store the node to be removed temporarily
            // update the next node of the current node, to be the next next node
            // de-reference the removed node to help tidy up
            if (current->next->value.sale_id == value) {
                Node *remnode = current->next;
                current->next = current->next->next;
                remnode->next = NULL;
                remnode = NULL;
            }
        current = current->next;
        }
    }
}

/**
 * Prints a range of nodes between the supplied values,
 * the values are inclusive of the range
 * @param *list  The list to display a range of nodes from
 * @param val1  The sale_id of the first item to display
 * @param val2  The sale_id of the last item to display
 **/
void print_range(Node *list, int val1, int val2) {
    // check for valid values (val1 must be less than val2)
    int min = (val1 < val2 ? val1 : val2);
    int max = (val1 < val2 ? val2 : val1);
    Node *current = list;
    int anyFound = 0;
    // iterate through the list until end or we meet the last value wanted
    while (current != NULL &&
          ((current->value.sale_id <= max && order == ASC) ||
           (current->value.sale_id >= min && order == DESC))) {
        if (current->value.sale_id >= min && current->value.sale_id <= max) {
            print_node(current);
            anyFound++;
        }
    current = current->next;
    }
    // if there were no items displayed
    if (anyFound == 0) {
        printf("There are no sale id's between %d and %d.\n",val2,val1);
    }
}

/**
 * Removes duplicates by testing the next node for equality
 * if equal remove it, and continue checking, when not equal
 * move onto next node.
 * @param list  The list to remove duplicates from
 **/
void remove_duplicates(Node **list) {
    // if list is empty, lets not bother
    if (*list == NULL) {
        return;
    }

    Node *current = *list; // current position in the list
    Node *next; // pointer for the next node of current position

    while (current->next != NULL) {
        // if this and the next have the same sale_id
        if (current->value.sale_id == current->next->value.sale_id) {
            next = current->next->next; // get the next from the node we are deleting
            free(current->next); // remove the next node
            current->next = next; // transfer the removed nodes next to the currents next.
        }
        else {
            current = current->next; // no duplicates found, move to next node.
        }
    }
}

/**
 * Moves a node in the list from one position to another by
 * using insert_at to place in new position
 * @param list  The list to change positions of a node in
 **/
void change_position(Node **list, int to_pos, int from_pos) {
    Node *to_move = NULL; // pointer for the node to move
    Node *prev = NULL; // pointer to the node prior to the node to move
    // if we are moving the head
    if (from_pos == 0) {
        to_move = *list;
    }
    // if we are moving anything else
    else {
        prev = get_node(*list, from_pos-1);
        // prev will be null if invalid position chosen
        if (prev != NULL) {
            to_move = prev->next;
        }
    }
    // if to_move position is valid proceed
    if (to_move != NULL) {
        // update previous to point to the moving nodes next if not the head
        if (from_pos > 0) {
            prev->next = to_move->next;
        }
        // update the head
        else {
            *list = to_move->next;
        }
        // use insert at to handle update of to_move
        insert_at(list,to_pos,to_move);
    }
    // otherwise inform of incorrect input
    else {
        printf("\n\aInvalid from position chosen\n");
    }
}
