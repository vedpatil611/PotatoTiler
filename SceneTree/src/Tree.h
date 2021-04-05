#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <deque>

#define MAX_HEIGHT 10
class Data {
public:
    char* child_name;
    int child_type;
};

class Node {
public:
    char name[256];
    Data data;
    Node* first_child;
    Node* parent;	// could be calculate so might not be needed
    Node* right_sibling;
    Node* left_sibling;
};


Node* insert_node(Node* root, char* path_given, Data data);
int tokenize_path(char** path, char* path_dir, const char* delimiter);
void print_tree(Node* root);
Node* create_node(char* name);
Node* searchNode(Node* root, char* path_given);