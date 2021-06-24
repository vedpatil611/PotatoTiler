#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <fcntl.h>
#define MAX_HEIGHT 10
#define MAX_NODE_NAME_LEN 255

class Data {
public:
    char const* child_name;
    int child_type;
};

class Node {
public:
    char name[MAX_NODE_NAME_LEN];
    Data data;
    Node* first_child;
    Node* parent;	// could be calculate so might not be needed
    Node* right_sibling;
    Node* left_sibling;
};


Node* insertNode(Node* root, char const* path_given, Data data);
int tokenizePath(char** path, char const* path_dir, const char* delimiter);
void printTree(Node* root, int depth);
Node* createNode(char const* name);
Node* searchNode(Node* root, char const* path_given);
void deleteTree(Node* root, char* path_given);
void saveNode(char* file_name, Node* node, FILE* file);
Node* loadNode(char* file_name, FILE* file);
void saveTree_r(char* file_name, Node* root, int depth, FILE* file);
void saveTree(char* file_name, Node* root);
Node* loadTree(char* file_name);

