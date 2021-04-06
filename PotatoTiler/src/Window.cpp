#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

Window::Window()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to init glfw");

    m_Window = glfwCreateWindow(640, 480, "Potato Tiler", nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to load opengl");
    }

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetKeyCallback(m_Window, &Window::keyCallback);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::clearBuffer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::pollInput()
{
    glfwPollEvents();
}

void Window::swapBuffer()
{
    glfwSwapBuffers(m_Window);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void Window::keyCallback(GLFWwindow* m_Window, int key, int scancode, int action, int mods)
{
}
