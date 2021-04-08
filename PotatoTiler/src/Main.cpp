#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <Renderer/Buffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>
#include <Scene/Sprite.h>
#include <Camera.h>
#include <Window.h>

#include <Tree.h>

int main(int argc, char* argv[]) 
{
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
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node1");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node1/node11");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node3/");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node1/node12");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node2/");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node3/node31");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node3/node32");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node3/node32/node321");
    root = insertNode(root, path_node, data);

    strcpy(path_node, "/root/node3/node32/node322");
    root = insertNode(root, path_node, data);

    printf("Printing Tree\n");
    printTree(root);

    printf("\n");

    Node* temp;
    strcpy(path_node, "/root");
    temp = searchNode(root, path_node);
    printTree(temp);

    printf("\n");

    strcpy(path_node, "/root/node3");
    temp = searchNode(root, path_node);
    printTree(temp);

    printf("\n");

    strcpy(path_node, "/root/node3");
    deleteTree(root, path_node);
    printTree(root);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float deltaTime = 0.0f, lastTime = 0.0f;

    Window* window = new Window();
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 20.0f);

    /*float verticies[] =
    {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };*/

    float verticies[] =
    {
        -50.0f, -50.0f,
        -50.0f,  50.0f,
         50.0f,  50.0f,
         50.0f, -50.0f
    };

    Shader shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
    Buffer* buffer = new Buffer(verticies, 2 * 4);

    Sprite sprite({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0 }, &shader);
    sprite.addVertexBuffer(0, 2, buffer);

    while (!window->shouldClose())
    {
        float now = static_cast<float>(glfwGetTime());
        deltaTime = now - lastTime;
        lastTime = now;

        window->clearBuffer();
        window->pollInput();

        camera->handleInputs(window->getKeys(), window->getXChange(), window->getYChange(), deltaTime);
        shader.bind();
        shader.setUniformMat4("uProj", window->getProjMatrix());
        shader.setUniformMat4("uView", camera->getViewMatrix());

        sprite.drawSprite();

        window->swapBuffer();
    }

    glfwTerminate();
    return 0;
}
