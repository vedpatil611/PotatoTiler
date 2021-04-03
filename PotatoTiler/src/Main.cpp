#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../SceneTree/src/Tree.h"

int main(int argc, char* argv[]) {
    //Node* root = create_node("root");
    //root->first_child = create_node("Node1");
    //root->first_child->first_child = create_node("Node11");
    //root->first_child->first_child->right_sibling = create_node("Node12");
    //root->first_child->right_sibling = create_node("Node2");
    //root->first_child->right_sibling->right_sibling = create_node("Node3");
    //root->first_child->right_sibling->right_sibling->first_child = create_node("Node31");
    //root->first_child->right_sibling->right_sibling->first_child->right_sibling = create_node("Node32");
    //root->first_child->right_sibling->right_sibling->first_child->right_sibling->first_child = create_node("Node321");
    //print_tree(root);

    Node* root = NULL;
    //root = create_node("root");
    //init_tree(&root);
    Data data;
    data.child_name = "new";
    data.child_type = 1;
    char path_node[256];

    strcpy(path_node, "root");
    root = insert_node(root, path_node, data);
    
    printf("Printing Tree\n");
    print_tree(root);

    strcpy(path_node, "/root/node1");
    root = insert_node(root, path_node, data);

    printf("Printing Tree\n");
    print_tree(root);

    strcpy(path_node, "/root/node1/node11");
    root = insert_node(root, path_node, data);

    printf("Printing Tree\n");
    print_tree(root);

    strcpy(path_node, "/root/node1/node12");
    root = insert_node(root, path_node, data);

    printf("Printing Tree\n");
    print_tree(root);
    
    strcpy(path_node, "/root/node2/");
    root = insert_node(root, path_node, data);
    
    printf("Printing Tree\n");
    print_tree(root);

    return 0;
}
