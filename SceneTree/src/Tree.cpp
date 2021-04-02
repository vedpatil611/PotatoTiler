#include "Tree.h"


int tokenize_path(char** path, char* path_dir, const char* delimiter){
    char* str;
    char *token;
    token = (char *)malloc(sizeof(char) * 256);
	int i;
	for(i = 0, str = path_dir; ;i++, str = 0){
		token = strtok(str, delimiter);
		if(token == NULL){
			break;
		}
		printf("%s\n", token);
		path[i] = token;
	}
	return i;
}

void init_tree(Node* root) {
    root->name = "root";
    root->first_child = NULL;
    root->left_sibling = NULL;
    root->right_sibling = NULL;
}

// path format /root/node1/node2/new_node
//this means root->node1->node2->new_node
void insert_node(Node* root, char* path_given, Data data) {
    Node new_node;
    char* path[MAX_HEIGHT];
    //new_node = (Node*)malloc(sizeof(Node));
    new_node.data = data;
    new_node.first_child = NULL;
    new_node.right_sibling = NULL;
    new_node.left_sibling = NULL;
    new_node.parent = NULL;
    int path_count = tokenize_path(path, path_given, "/");
    new_node.name = path[path_count - 1];
    printf("%d\n", path_count);

    if (root == NULL) {
        if (path_count == 0) {
            printf("Root node to be created ?\n");
            //root = new_node;
            return;
        }
        else {
            printf("path root mismatch cannot insert node");
            exit(1);
        }
    }
    else {
        int i;
        Node* temp = (Node*)malloc(sizeof(Node));
        temp = root;
        for (i = 0; i < path_count - 1; i++) {
            printf("%dth child %s\n", i, path[i]);
            if (strcmp(path[i], temp->name) == 0) {
                printf("First child of %s\n", temp->name);
                temp = temp->first_child;
            }
            else {
                int j = 1;
                temp = temp->right_sibling;
                while (temp != NULL) {
                    if (strcmp(path[i], temp->name) == 0) {
                        printf("%dth sibling of %dth child %s\n", j, i, temp->name);
                        temp = temp->first_child;
                        break;
                    }
                    else {
                        printf("%s\n", temp->name);
                        temp = temp->right_sibling;
                    }
                }
            }
        }
        if (strcmp(path[path_count - 1], temp->name) == 0) {
            printf("Child of %s\n", temp->name);
            temp->first_child = &new_node;
            new_node.parent = temp;
            return;
        }
        else {
            temp = temp->right_sibling;
            while (temp != NULL) {
                if (strcmp(path[path_count - 1], temp->name) == 0) {
                    printf("Child of %s\n", temp->name);
                    temp->right_sibling = &new_node;
                    new_node.parent = temp->parent;
                    new_node.left_sibling = temp;
                    break;
                }
                else {
                    temp = temp->right_sibling;
                }
            }
        }
        
    }
}

