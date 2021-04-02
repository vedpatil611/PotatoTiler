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

    return 0;
}
/*
int main()
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Potato Tiler", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    bool d = true;
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.5;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();

        if (r > 1.0f) d = false;
        else if (r < 0.0f) d = true;

        if (d) r += 0.01;
        else r -= 0.01f;
        g = 1 - r;

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
*/