#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>
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

void drawAssetBrowser();
void drawSceneTree();
void drawMenuBar();
void traverseTree(Node* root);

ImGui::FileBrowser fileDialog;
Node* root = NULL;
Window* window;
Camera* camera;

Node* createTree() {
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

    return root;
}

int main(int argc, char* argv[])
{
    char file_name[20] = "save.dat";
    root = createTree();
    saveTree(file_name, root);
    delete root;
    root = loadTree(file_name);

    printTree(root, 0);

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

        DockableWindow::begin();
        DockableWindow::draw("File Browser", drawAssetBrowser);
        DockableWindow::draw("Scene Tree", drawSceneTree);
        DockableWindow::draw("Main Menu", drawMenuBar);
        DockableWindow::end();

        sprite.drawSprite();

        window->swapBuffer();
    }

    DockableWindow::destroy();
    glfwTerminate();
    return 0;
}

void getDirectoryTree(char* path)
{
    for (auto& entry : std::filesystem::directory_iterator(path))
    {
        auto t = entry.path();
        if (entry.is_directory()) 
        {
            std::string s = t.string();
            char newPath[MAX_PATH];
            strcpy(newPath, s.c_str());
            if (ImGui::TreeNode(t.relative_path().filename().string().c_str()))
            {
                ImGui::Indent();
                getDirectoryTree(newPath);
                ImGui::Unindent();
                ImGui::TreePop();
            }
        }
        else
        {
            ImGui::Text(t.relative_path().filename().string().c_str());
        }
    }
}

void drawAssetBrowser()
{
    ImGui::Begin("Asset Browser");
    char* path = ".\\";
    getDirectoryTree(path);
    ImGui::End();
}

void drawSceneTree()
{
    ImGui::Begin("Scene Tree");
    traverseTree(root);
    ImGui::End();
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
        ImGui::Text(temp->name);

        temp = temp->first_child;
    }
    else
    {
        if (ImGui::TreeNode(temp->name))
        {
            temp = temp->first_child;

            if (temp->first_child == nullptr)
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

void drawMenuBar()
{
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
                saveTree(file_name, root);
            }
            if (ImGui::MenuItem("Exit"))
            {
                window->setShouldClose(true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

