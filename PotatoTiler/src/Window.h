#pragma once

class Window
{
private:
	struct GLFWwindow* m_Window;
	bool m_Keys[1024] = { 0 };
public:
	Window();
	~Window();

	void clearBuffer();
	void pollInput();
	void swapBuffer();

	bool shouldClose() const;

	static void keyCallback(GLFWwindow* m_Window, int key, int scancode, int action, int mods);
};