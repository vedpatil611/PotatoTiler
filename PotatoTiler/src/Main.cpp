#include <glad/glad.h>
#include <GLFW/glfw3.h>

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