#pragma once

#include <glm/glm.hpp>

class Window
{
private:
	struct GLFWwindow* m_Window;
	bool m_Keys[1024] = { 0 };
	int m_BufferWidth, m_BufferHeight;
	float m_LastX = 0.0f, m_LastY = 0.0f;
	float m_xChange = 0.0f, m_yChange = 0.0f;
	glm::mat4 m_Proj;
public:
	Window();
	~Window();

	void clearBuffer();
	void pollInput();
	void swapBuffer();

	bool shouldClose() const;
	bool* getKeys() { return m_Keys; }
	inline struct GLFWwindow* getWindow() const { return m_Window; };

	float getXChange();
	float getYChange();

	inline float getWidth() const { return 1280.0f; }
	inline float getHeight() const { return 720.0f; }
	
	glm::mat4 getProjMatrix() const { return m_Proj; }

	void setShouldClose(bool v);

	static void keyCallback(GLFWwindow* m_Window, int key, int scancode, int action, int mods);
	static void mouseKeyCallback(GLFWwindow* window, int key, int action, int mods);
	static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);
};