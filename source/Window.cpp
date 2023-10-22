#include "Window.hpp"

Window::Window ( std::string const & name, glm::vec2 size, bool fullscreen )
{
	glfwSetErrorCallback ( glfwErrorCallback );

	glfwInit ();

	//GLFWmonitor * monitor { nullptr };

	//auto videoMode { glfwGetVideoMode ( monitor ) };

	glfwWindowHint ( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );
	window = glfwCreateWindow ( 1280, 720, /*videoMode->width, videoMode->height*/ name.data (), nullptr, nullptr);

	glfwSetWindowUserPointer ( window, new WindowData { this } );

	glfwSetFramebufferSizeCallback ( window, glfwFramebufferSizeCallback );
	glfwSetKeyCallback ( window, glfwKeyCallback );
	glfwSetCursorPosCallback ( window, glfwCursorPosCallback );
	glfwSetMouseButtonCallback ( window, glfwMouseButtonCallback );
	glfwSetCursorEnterCallback ( window, glfwCursorEnterCallback );

	glfwMakeContextCurrent ( window );
		
	//glfwSwapInterval ( 1 );
}

Window::~Window ()
{
	delete glfwGetWindowUserPointer ( window );
	glfwDestroyWindow ( window );
	glfwTerminate ();
}

glm::vec2 Window::GetSize () const
{
	glm::ivec2 size;
	glfwGetFramebufferSize ( window, &size.x, &size.y );
	return size;
}

Window::WindowData * Window::GetWindowData (GLFWwindow * window)
{
	return reinterpret_cast <WindowData *> (glfwGetWindowUserPointer ( window ));
}
	
glm::vec2 Window::ScreenSpaceToNDC ( glm::vec2 point )
{
	auto size { GetSize () };

	point.y = size.y - point.y; // Invert y
	point /= size;				// Normalize point
	point -= 0.5f;				// Shift origin to center
	point *= 2.0f;				// Normalize point

	return point;
}
	
glm::vec2 Window::GetCursorPosition () const
{
	glm::dvec2 pos { 0.0, 0.0 };
	glfwGetCursorPos ( window, &pos.x, &pos.y );
	return pos;
}

int Window::GetMouseButton ( int button ) const
{
	return glfwGetMouseButton ( window, button );
}

void Window::MakeContextCurrent () const
{
	glfwMakeContextCurrent ( window );
}

// -------------| GLFW Callbacks |-----------------

void  Window::glfwErrorCallback ( int errorCode, char const * desc )
{
	std::cout << "-------| GLFW ERROR |--------" << std::endl;
	std::cout << "code: " << errorCode << std::endl;
	std::cout << "description: " << desc << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void  Window::glfwFramebufferSizeCallback ( GLFWwindow * glfwWindow, int width, int height )
{
	/*glfwMakeContextCurrent ( glfwWindow );
	glViewport ( 0, 0, width, height );
	*/	
	Window & window { *GetWindowData ( glfwWindow )->window };

	window.framebufferResizeEvent.Dispatch ( { width, height } );
}

void Window::glfwKeyCallback ( GLFWwindow * glfwWindow, int key, int scancode, int action, int mods )
{
	Window & window { *GetWindowData ( glfwWindow )->window };

	if (action == GLFW_PRESS)
	{
		window.keyDownEvent.Dispatch ( key );
	}

	else if (action == GLFW_RELEASE)
	{
		window.keyUpEvent.Dispatch ( key );
	}
}
	
void Window::glfwCursorPosCallback ( GLFWwindow * glfwWindow, double xpos, double ypos )
{
	Window & window { *GetWindowData ( glfwWindow )->window };
	
	glm::vec2 currentCursorPos { static_cast <float> (xpos), static_cast <float> (ypos) };
	
	window.cursorMoveEvent.Dispatch ( currentCursorPos - window.lastCursorPos );

	window.lastCursorPos = currentCursorPos;
}

void Window::glfwCursorEnterCallback ( GLFWwindow * glfwWindow, int entered )
{
	if (entered)
	{
		Window & window { *GetWindowData ( glfwWindow )->window };
		window.lastCursorPos = window.GetCursorPosition ();
	}
}

void Window::glfwMouseButtonCallback ( GLFWwindow * glfwWindow, int button, int action, int mods )
{
	Window & window { *GetWindowData ( glfwWindow )->window };

	if ( action == GLFW_PRESS )
		window.mouseButtonPressEvent.Dispatch ( button );
	else
		window.mouseButtonReleaseEvent.Dispatch ( button );
}

// ----------------------------------------------