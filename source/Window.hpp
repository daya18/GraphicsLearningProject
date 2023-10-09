#pragma once

#include "Event.hpp"

class Window
{
public:
	Event <glm::vec2> framebufferResizeEvent;
	Event <int> keyDownEvent;
	Event <int> keyUpEvent;
	Event <glm::vec2> cursorMoveEvent;
	Event <int> mouseButtonPressEvent;
	Event <int> mouseButtonReleaseEvent;

	using FramebufferResizeCallback = std::function<void(glm::vec2)>;
	using KeyCallback = std::function <void(int) >;

	Window ( std::string const & name, glm::vec2 size, bool fullscreen = false );
	virtual ~Window ();

	glm::vec2 GetSize () const;
	bool ShouldClose ();
	void SwapBuffers ();

	glm::vec2 ScreenSpaceToNDC ( glm::vec2 );
	glm::vec2 GetCursorPosition () const;
	int GetMouseButton ( int button ) const;
	void MakeContextCurrent () const;

private:
	struct WindowData
	{
		Window * window;
	};
		
	static WindowData * GetWindowData ( GLFWwindow * window );

	static void glfwErrorCallback ( int errorCode, char const * desc );
	static void glfwFramebufferSizeCallback ( GLFWwindow * window, int width, int height );
	static void glfwKeyCallback ( GLFWwindow * window, int key, int scancode, int action, int mods );
	static void glfwCursorPosCallback ( GLFWwindow * window, double xpos, double ypos );
	static void glfwMouseButtonCallback ( GLFWwindow * window, int button, int action, int mods );
	static void glfwCursorEnterCallback ( GLFWwindow * window, int );

	GLFWwindow * window;
	glm::vec2 lastCursorPos { 0, 0 };
};

// Implementation
inline bool Window::ShouldClose () { return glfwWindowShouldClose ( window ); }
inline void Window::SwapBuffers () { glfwSwapBuffers ( window ); }