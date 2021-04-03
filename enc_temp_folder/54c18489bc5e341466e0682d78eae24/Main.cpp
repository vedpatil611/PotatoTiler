#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../SceneTree/src/Tree.h"

int main(int argc, char* argv[]) {
    Node root;
    //root = (Node*)malloc(sizeof(Node));
    init_tree(&root);
    root.name = "root";
    root.first_child = NULL;
    root.left_sibling = NULL;
    root.right_sibling = NULL;
    root.parent = NULL;
    Data data;
    printf("Code Started\n");
    char path_node[256];
    data.child_name = "new";
    data.child_type = 1;



    printf("%s\n\n", root.name);

    strcpy(path_node, "root");
    insert_node(&root, path_node, data);
    print_tree(&root);

    strcpy(path_node, "/root/new");
    insert_node(&root, path_node, data);
    print_tree(&root);

    strcpy(path_node, "/root/old");
    insert_node(&root, path_node, data);
    print_tree(&root);

    strcpy(path_node, "/root/new/newshit");
    insert_node(&root, path_node, data);
    print_tree(&root);
    
    strcpy(path_node, "/root/old/shit");
    insert_node(&root, path_node, data);
    print_tree(&root);

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
    return 0;
}
