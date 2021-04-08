#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
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

    glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to load opengl");
    }

    m_Proj = glm::ortho(-m_BufferWidth / 2, m_BufferWidth / 2, -m_BufferHeight / 2, m_BufferHeight / 2);

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetKeyCallback(m_Window, &Window::keyCallback);
    glfwSetMouseButtonCallback(m_Window, &Window::mouseKeyCallback);
    glfwSetCursorPosCallback(m_Window, &Window::mousePositionCallback);
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

float Window::getXChange()
{
    float change = m_xChange;
    m_xChange = 0;
    return change;
}

float Window::getYChange()
{
    float change = m_yChange;
    m_yChange = 0;
    return change;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            currentWindow->getKeys()[key] = true;
        }
        if (action == GLFW_RELEASE)
        {
            currentWindow->getKeys()[key] = false;
        }
    }
}

void Window::mouseKeyCallback(GLFWwindow* window, int key, int action, int mods)
{
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            currentWindow->getKeys()[key] = true;
        }
        if (action == GLFW_RELEASE)
        {
            currentWindow->getKeys()[key] = false;
        }
    }
}

void Window::mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    currentWindow->m_xChange = static_cast<float>(xPos) - currentWindow->m_LastX;
    currentWindow->m_yChange = currentWindow->m_LastY - static_cast<float>(yPos);

    currentWindow->m_LastX = static_cast<float>(xPos);
    currentWindow->m_LastY = static_cast<float>(yPos);
}
