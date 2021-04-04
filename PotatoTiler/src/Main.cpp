#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer/Buffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Shader.h>

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

    unsigned short indicies[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    Buffer* buffer = new Buffer(verticies, 2 * 4);
    IndexBuffer ib(indicies, 2 * 3);
    VertexArray va;
    va.addBuffer(0, 2, buffer);

    Shader shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        va.bind();
        ib.bind();
        shader.bind();

        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_SHORT, nullptr);

        va.unbind();
        ib.unbind();
        shader.unbind();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}