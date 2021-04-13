#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <ImGui/imgui.h>
#include <imfilebrowser.h>
#include <Renderer/Buffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>
#include <Scene/Sprite.h>
#include <UI/DockableWindow.h>
#include <Camera.h>
#include <Window.h>

#include <Tree.h>

void filebrowser();
void drawMenuBar();
void drawSceneTree();
void traverseTree(Node* root);

ImGui::FileBrowser fileDialog;
Node* root = NULL;

Window* window;
Camera* camera;

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
    printTree(root, 0);

    printf("\n");

   /* Node* temp;
    strcpy(path_node, "/root");
    temp = searchNode(root, path_node);
    printTree(temp, 0);

    printf("\n");

    strcpy(path_node, "/root/node3");
    temp = searchNode(root, path_node);
    printTree(temp, 0);

    printf("\n");

    strcpy(path_node, "/root/node3");
    deleteTree(root, path_node);
    printTree(root, 0);*/

    char file_name[20] = "save.dat";
    int depth = 0;
    saveTree(file_name, root, depth);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float deltaTime = 0.0f, lastTime = 0.0f;

    window = new Window();
    camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 20.0f);
    DockableWindow::init(window);

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

    fileDialog.SetTitle("Assets");
    fileDialog.SetTypeFilters({ ".dat" });

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

        DockableWindow::begin();
        DockableWindow::draw("Asset Browser", filebrowser);
        DockableWindow::draw("Scene Tree", drawSceneTree);
        DockableWindow::draw("Menu", drawMenuBar);
        DockableWindow::end();

        window->swapBuffer();
    }

    DockableWindow::destroy();
    glfwTerminate();
    return 0;
}

void filebrowser()
{
    ImGui::Text("Files go here");
}

void drawMenuBar()
{
    //ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
                fileDialog.Open();
                fileDialog.Display();
            }
            if (ImGui::MenuItem("Save"))
            {
                char file_name[20] = "save.dat";
                int depth = 0;
                saveTree(file_name, root, depth);
            }
            if (ImGui::MenuItem("Exit"))
            {
                window->setShouldClose(true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //ImGui::End();
}

void drawSceneTree()
{
    traverseTree(root);
}

void traverseTree(Node* root)
{
    Node* temp = root;
    if (temp == nullptr)
    {
        return;
    }

    if (temp->first_child == nullptr)
    {
        ImGui::Selectable(temp->name);

        temp = temp->first_child;
    }
    else
    {
        if (ImGui::TreeNode(temp->name))
        {
            temp = temp->first_child;
            
            if(temp->first_child == nullptr)
                ImGui::Indent();

            while (temp != nullptr)
            {
                traverseTree(temp);
                temp = temp->right_sibling;
                if (temp == nullptr) {
                    ImGui::Unindent();
                    ImGui::TreePop();
                }
            }
        }
    }
}