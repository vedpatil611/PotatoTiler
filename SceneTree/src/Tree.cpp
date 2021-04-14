#include "Tree.h"

const char* NODE_FORMAT_IN = "(%[^,]s, %[^,]s, %d)";
const char* NODE_FORMAT_OUT = "(%s, %s, %d)\n";

int tokenizePath(char** path, char* path_dir, const char* delimiter) {
    char* str;
    char* token;
    token = (char*)malloc(sizeof(char) * 256);
    int i;
    for (i = 0, str = path_dir; ; i++, str = 0) {
        token = strtok(str, delimiter);
        if (token == NULL) {
            break;
        }
        //printf("%s\t", token);
        path[i] = token;
    }
    //printf("\n");
    return i;
}

void deleteNode(Node* root) {
    // tree path something like root->(node1->node11, node12), (node2), (node3->(node31, node32 -> node321))
    // To check if temp is first child
    // eg. to remove node1 we must first assign node2 or node3 as first child of root

    if (root->parent != NULL) {
        if (root->parent->first_child == root) {
            root->parent->first_child = root->right_sibling;
            //root->parent->first_child = NULL;
        }
    }
    if (root->right_sibling != NULL) {
        root->right_sibling->left_sibling = root->left_sibling;
    }
    if (root->left_sibling != NULL) {
        root->left_sibling->right_sibling = root->right_sibling;
    }
    delete root;
}

void deleteTree_r(Node* root) {
    Node* temp, * temp2;
    temp = root;
    if (temp == NULL) {
        return;
    }

    temp = temp->first_child;
    while (temp != NULL) {
        // Leaf node
        if (temp->first_child == NULL) {
            deleteNode(temp);
            return;
        }
        else {
            // Single child
            if (temp->first_child->right_sibling == NULL) {
                deleteTree_r(temp->first_child);
                break;
            }
            // Multiple chilren
            else {
                temp = temp->first_child;
                temp2 = temp;
                while (temp != NULL) {
                    while (temp2->right_sibling != NULL) {
                        temp2 = temp2->right_sibling;
                    }
                    deleteTree_r(temp2);
                    temp2 = temp;
                }
            }
        }
    }
}

void deleteTree(Node* root, char* path_given) {
    Node* temp = searchNode(root, path_given);
    // Removes every child of temp
    deleteTree_r(temp);

    deleteNode(temp);
}

Node* searchNode(Node* root, char* path_given) {
    char* path[MAX_HEIGHT];
    int path_count;
    path_count = tokenizePath(path, path_given, "/");
    //starting from 0
    path_count = path_count - 1;
    // Empty tree or empty path
    if (root == NULL || path_count == -1) {
        printf("Empty tree or empty path\n");
        return NULL;
    }
    Node* temp = root;
    int i = 0;
    while (temp != NULL && i < path_count + 1) {
        if (strcmp(temp->name, path[i]) == 0) {
            // Reched end of path
            if (i == path_count) {
                return temp;
            }
            else {
                // No child
                // eg. path root/node1/node2
                // Here, root or node1 doesn't have first child which isn't possible
                if (temp->first_child == NULL) {
                    printf("Incomplete Path\n");
                    return NULL;
                }
                else {
                    // Single child
                    if (temp->first_child->right_sibling == NULL) {
                        if (strcmp(temp->first_child->name, path[i + 1]) == 0) {
                            temp = temp->first_child;
                            i++;
                        }
                        // Single child
                        // eg. path root/node1/node2
                        // Here, root has a child but its name is not node1
                        // Or, node1 has a child but its name is not node 2 which is not possible
                        else {
                            printf("Incorrect path\n");
                            return NULL;
                        }
                    }
                    // Multiple children
                    else {
                        temp = temp->first_child;
                        while (temp != NULL) {
                            // First child matches path name
                            if (strcmp(temp->name, path[i + 1]) == 0) {
                                i++;
                                break;
                            }
                            else {
                                temp = temp->right_sibling;
                            }
                        }
                        if (temp == NULL) {
                            printf("Wrong path\n");
                            return NULL;
                        }

                    }

                }
            }

        }
        else {
            printf("Path not found\n");
            return NULL;
        }
    }
}

Node* insertNode(Node* root, char* path_given, Data data) {
    char* path[MAX_HEIGHT];
    int path_count = 0;
    path_count = tokenizePath(path, path_given, "/");
    //starting from 0
    path_count = path_count - 1;
    if (path_count == 0) {
        printf("Initalizing Root, Overwrinting given path\n");
        root = createNode("root");
        return root;
    }
    Node* temp = root;
    //printf("Name : %s\t%s\n", temp->name, path[0]);
    int i = 0;
    while (temp != NULL && i < path_count) {
        if (strcmp(temp->name, path[i]) == 0) {
            //printf("path[%d] : %s\n", i, temp->name);
            i++;
            // If first child of path is NULL
            if (temp->first_child == NULL) {
                // If parent of new node to be added has no child
                // e.g path root/node1/node2/new_node
                // Here, first child of node2 doesn't exist
                if (i == path_count) {
                    temp->first_child = createNode(path[path_count]);
                    temp->first_child->parent = temp;
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
                Node* temp2 = temp;
                temp = temp->first_child;
                //printf("First Child name : %s\n", temp->name);

                while (temp != NULL) {
                    if (temp->right_sibling == NULL) {
                        // e.g path root/node1/node2/new_node
                        // Here node2 has one other child besides new_node
                        if (i == path_count) {
                            //printf("sibling name : %s\n", temp->name);
                            temp->right_sibling = createNode(path[path_count]);
                            temp->right_sibling->left_sibling = temp;
                            temp->right_sibling->parent = temp2;
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

Node* createNode(char* name) {
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

void printTree(Node* root, int depth) {
    // tree path something like root->(node1->node11, node12), (node2), (node3->(node31, node32 -> node321))
    Node* temp = root;
    if (temp == NULL) {
        //printf("Empty Tree\n");
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", temp->name);
    temp = temp->first_child;

    while (temp != NULL) {
        printTree(temp, depth + 1);
        temp = temp->right_sibling;
    }
    return;
}

// Only to be called in saveTree
void saveNode(char* file_name, Node* node, FILE* file) {
    fprintf(file, NODE_FORMAT_OUT, node->name, node->data.child_name, node->data.child_type);
}

void saveTree_r(char* file_name, Node* root, int depth, FILE* file) {
    // tree path something like root->(node1->node11, node12), (node2), (node3->(node31, node32 -> node321))
    Node* temp = root;
    if (temp == NULL) {
        //printf("Empty Tree\n");
        return;
    }
    for (int i = 0; i < depth; i++) {
        fprintf(file, ">");
    }
    saveNode(file_name, temp, file);
    temp = temp->first_child;

    while (temp != NULL) {
        saveTree_r(file_name, temp, depth + 1, file);
        temp = temp->right_sibling;
    }
    return;
}

void saveTree(char* file_name, Node* root) {
    FILE* file;
    fopen_s(&file, file_name, "w+");
    if (file == NULL) {
        printf("File not opened, save failed\n");
        return;
    }
    saveTree_r(file_name, root, 0, file);
    fclose(file);
}

Node* loadNode(char* file_name, FILE* file) {
    Node* node;
    char* node_data[3]; // Change this according to number of data elements in file
    char line[1024];    // More space might be needed
    fscanf(file, "(%[^)]s", line);
    //fscanf(file, NODE_FORMAT_IN, node.name, node.data.child_name, &node.data.child_type);
    int n = tokenizePath(node_data, line, ", ");
    if (n != 3) {
        if (n != 0) {
            printf("Incorrect format or Corrupt data\n");
        }
        return NULL;
    }
    node = createNode(node_data[0]);
    strncpy(node->name, node_data[0], strlen(node_data[0]));
    //strncpy(node->data.child_name, node_data[1], strlen(node_data[1]));
    node->data.child_type = atoi(node_data[2]);
    return node;
}

Node* loadTree(char* file_name) {
    FILE* file;
    char* arg[MAX_HEIGHT];
    char path[MAX_NODE_NAME_LEN];
    char ch;
    int depth = 0;
    fopen_s(&file, file_name, "r");
    if (file == NULL) {
        printf("File not opened, load failed\n");
        return NULL;
    }
    Node* root, * temp;
    root = nullptr;
    while (fscanf(file, "%c", &ch) != EOF) {
        if (ch == '<') {
            depth++;
        }
        else {
            strcpy(path, "");
            fseek(file, -1, SEEK_CUR);
            for (int i = 0; i < depth; i++) {
                strcat(path, arg[i]);
            }
            temp = loadNode(file_name, file);
            if (temp != NULL) {
                strcat(path, temp->name);
                root = insertNode(root, path, temp->data);
            }
        }
    }
    fclose(file);
    return root;
}
