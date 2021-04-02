#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_HEIGHT 10
class Data {
public:
    char* child_name;
    int child_type;
};

class Node {
public:
    char* name;
    Data data;
    Node* first_child;
    Node* parent;	// could be calculate so might not be needed
    Node* right_sibling;
    Node* left_sibling;
};


void init_tree(Node* root);
void insert_node(Node* root, char* path_given, Data data);
int tokenize_path(char** path, char* path_dir, const char* delimiter);