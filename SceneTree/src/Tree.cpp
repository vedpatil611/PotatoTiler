#include "Tree.h"


int tokenize_path(char** path, char* path_dir, const char* delimiter){
    char* str;
    char *token;
    token = (char *)malloc(sizeof(char) * 256);
	int i;
    printf("\n");
    for(i = 0, str = path_dir; ;i++, str = 0){
		token = strtok(str, delimiter);
		if(token == NULL){
			break;
		}
		printf("%s\t", token);
		path[i] = token;
	}
    printf("\n");
	return i;
}

Node* insert_node(Node* root, char* path_given, Data data) {
    char* path[MAX_HEIGHT];
    int path_count = 0;
    path_count = tokenize_path(path, path_given, "/");
    //starting from 0
    path_count = path_count - 1;
    if (path_count == 0) {
        printf("Initalizing Root, Overwrinting given path\n");
        root = create_node("root");
        return root;
    }
    Node* temp = root;
    //printf("Name : %s\t%s\n", temp->name, path[0]);
    int i = 0;
    while (temp != NULL && i < path_count) {
        if (strcmp(temp->name, path[i]) == 0) {
            printf("path[%d] : %s\n", i, temp->name);
            i++;
            // If first child of path is NULL
            if (temp->first_child == NULL) {
                // If parent of new node to be added has no child
                // e.g path root/node1/node2/new_node
                // Here, first child of node2 doesn't exist
                if (i == path_count) {
                    temp->first_child = create_node(path[path_count]);
                    return root;
                }
                // Child of intermediate parent doesn't exist
                // e.g path root/node1/node2/new_node
                // Here, first child of root or node1 doesn't exist which shouldn't be possible in case of correct path
                else {
                    printf("Incomplete path\n");
                    return NULL;
                }
            }
            // If first child of path exists go to child and append node to its siblings
            else {
                temp = temp->first_child;
                printf("First Child name : %s\n", temp->name);

                while (temp != NULL) {
                    if (temp->right_sibling == NULL) {
                        // e.g path root/node1/node2/new_node
                        // Here node2 has one other child besides new_node
                        if (i == path_count) {
                            printf("sibling name : %s\n", temp->name);
                            temp->right_sibling = create_node(path[path_count]);
                            return root;
                        }
                        else {
                            // e.g path root/node1/node2/new_node
                            // root or node1 has single child
                            if (strcmp(temp->name, path[i]) == 0) {
                                break;
                            }
                            else {
                                printf("Wrong path\n");
                                return NULL;
                            }
                        }
                    }
                    // Contain multiple child
                    else {
                        if (i == path_count) {
                            temp = temp->right_sibling;
                        }
                        else {
                            // e.g path root/node1/node2/new_node
                            // root or node1 has multiple children
                            if (strcmp(temp->name, path[i]) == 0) {
                                break;
                            }
                            else {
                                temp = temp->right_sibling;
                            }
                        }
                    }
                }
            }
        }
        else {
            // temp->name != path[i]
            printf("Incorrect path\n");
            return NULL;
        }
    }
}

Node* create_node(char* name) {
    Node* new_node = new Node();
    if (new_node == NULL) {
        std::cout << "Memory Error\n";
        return NULL;
    }
    Data data;
    data.child_name = "empty";
    data.child_type = 0;
    strcpy(new_node->name, name);
    new_node->parent = NULL;
    new_node->left_sibling = NULL;
    new_node->right_sibling = NULL;
    new_node->first_child = NULL;
    new_node->data = data;
    return new_node;
}

void print_tree(Node* root) {
    if (root == NULL) {
        printf("Empty tree\n");
        return;
    }
    Node* temp;
    temp = root;
    while (temp != NULL) {
        printf("%s\n", temp->name);
        if (temp->first_child != NULL) {
            print_tree(temp->first_child);
            temp = temp->right_sibling;
        }
        else {
            if (temp->right_sibling != NULL) {
                temp = temp->right_sibling;
            }
            else{
                return;
            }
        }

    }
}
