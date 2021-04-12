#pragma once

#include <Window.h>

typedef void (*DrawFunc)();

class DockableWindow
{
private:
	inline static Window* m_Window = nullptr;
public:
	static void init(class Window* window);
	static void destroy();
	
	static void draw(const char* windowName, DrawFunc func);
private:
	static void begin();
	static void end();
};