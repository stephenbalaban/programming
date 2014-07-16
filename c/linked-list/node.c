#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "node.h"
// A-z
#define ARRAY_SIZE 26*2 + 6

void print_array(char array[], int size) 
{
    for(int i = 0; i < size; i++) {
        printf("Element: %c\n", array[i]);
    }
}

void print_node(Node* n) {
    Node* next = n->next;
    if (next != NULL) {
        printf("Node(%c)->Node(%c)\n", n->val, n->next->val);
    } else {
        printf("Node(%c)->NULL\n", n->val);
    }
}

void print_node_array(Node* array[], int size)
{
    for(int i = 0; i < size; i++)
        print_node(array[i]);
}

void increment_array(char array[], int size) {
    for(int i = 0; i < size; i++)
        array[i] += i;
}

Node* Node_create(char contents) {
    Node *n = malloc(sizeof(Node));
    assert(n != NULL);

    n->val = contents;

    return n;
}

void connect_nodes(Node* node_array[], int size) {
    // connect up all but the last
    for(int i = 0; i < size - 1; i ++) {
        node_array[i]->next = node_array[i+1];
    }
}

Node** make_nodes(char array[], int size) {
    Node **node_array = malloc(sizeof(Node*) * size);
    for(int i = 0; i < size; i++) {
        node_array[i] = Node_create(array[i]);
    }
    connect_nodes(node_array, size);
    return node_array;
}

void print_linked_list(Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        printf("Node(%c) -> ", curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

Node* reverse_linked_list(Node* head, Node* prev) {
    if (head == NULL) {
        return prev;
    } else {
        Node* next = head->next;
        head->next = prev;
        return reverse_linked_list(next, head);
    }
}

int main(int argc, char *argv[])
{
    char characters[ARRAY_SIZE] = { [0 ... ARRAY_SIZE - 1] = 'A' };
    increment_array(characters, ARRAY_SIZE);
    //print_array(characters, ARRAY_SIZE);
    Node** nodes = make_nodes(characters, ARRAY_SIZE);
    Node* HEAD = nodes[0];
    print_linked_list(HEAD);
    HEAD = reverse_linked_list(HEAD, NULL);
    printf("*********\n\n");
    print_linked_list(HEAD);
    HEAD = reverse_linked_list(HEAD, NULL);
    printf("*********\n\n");
    print_linked_list(HEAD);
}
