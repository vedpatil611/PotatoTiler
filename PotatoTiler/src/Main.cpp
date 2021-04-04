#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer/Buffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>
#include <Scene/Sprite.h>

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

    float verticies[] = 
    {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };

    Shader shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
    Buffer* buffer = new Buffer(verticies, 2 * 4);

    Sprite sprite({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0 }, &shader);
    sprite.addVertexBuffer(0, 2, buffer);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        sprite.drawSprite();
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}