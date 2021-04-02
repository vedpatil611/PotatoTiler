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
		printf("%s\t", token);
		path[i] = token;
	}
    printf("\n");
	return i;
}

void init_tree(Node* root) {
    root->name = "root";
    root->first_child = NULL;
    root->left_sibling = NULL;
    root->right_sibling = NULL;
    root->parent = NULL;
}

// path format /root/node1/node2/new_node
//this means root->node1->node2->new_node
void insert_node(Node* root, char* path_given, Data data) {
    Node new_node;
    char* path[MAX_HEIGHT];
    int path_count = tokenize_path(path, path_given, "/");
    new_node.name = path[path_count - 1];
    printf("%d\n", path_count);

    if (root == NULL) {
        printf("Root not initialized\n");
        exit(1);
    }
    int i;
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = root;
    if (temp == NULL) {
        printf("Root node Missing\n");
        exit(1);
    }
    for (i = 0; i < path_count - 1; i++) {
        printf("%dth child %s\n", i, path[i]);
        if (strcmp(path[i], temp->name) == 0) {
            printf("Parent Node : %d\t%s\n", path_count - i - 1, temp->name);
            temp = temp->first_child;
        }
        else {
            int j = 1;
            printf("Sibling of : %s\n", temp->name);
            if (temp && temp->right_sibling) {
                temp = temp->right_sibling;
            }
            else {
                printf("Incorrect path\n");
                exit(1);
            }
            while (temp != NULL) {
                if (strcmp(path[i], temp->name) == 0) {
                    printf("Parent node : %d\t%s\n", path_count - i - 1, temp->name);
                    temp = temp->first_child;
                    break;
                }
                else {
                    printf("Parent Sibling :%d\t%s\n", j, temp->name);
                    temp = temp->right_sibling;
                }
            }
        }
    }
    if (temp == NULL) {
        printf("Incomplete Path\n");
        exit(1);
    }
    if (strcmp(path[path_count - 1], temp->name) == 0) {
        printf("Child of %s\n", temp->name);
        temp->first_child = &new_node;
        new_node.parent = temp;
        new_node.name = temp->name;
        new_node.left_sibling = NULL;
        new_node.right_sibling = NULL;
        new_node.first_child = NULL;
        new_node.data = data;
        return;
    }
    else {
        printf("Sibling of : %s\n", temp->name);
        temp = temp->right_sibling;
        while (temp != NULL) {
            if (strcmp(path[path_count - 1], temp->name) == 0) {
                printf("Child of %s\n", temp->name);
                temp->right_sibling = &new_node;
                new_node.parent = temp->parent;
                new_node.left_sibling = temp;
                new_node.name = temp->name;
                new_node.right_sibling = NULL;
                new_node.first_child = NULL;
                new_node.data = data;
                break;
            }
            else {
                printf("Sibling of : %s\n", temp->name);
                temp = temp->right_sibling;
            }
        }
    }
}

void print_tree(Node* root) {
    //std::deque <Node*> queue;
    if (root == NULL) {
        printf("Empty tree\n");
        return;
    }
    Node* temp;
    temp = root;
    printf("Print Tree Output\n");
    while (temp != NULL) {
        printf("%s\n", temp->name);
        if (temp->first_child != NULL) {
            print_tree(temp->first_child);
        }
        else {
            if (temp->right_sibling != NULL) {
                temp = temp->right_sibling;
            }
        }

    }
}
