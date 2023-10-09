#include "Context.hpp"

#include "../Window.hpp"

OpenGLContext::OpenGLContext ( Window & window )
{
	window.MakeContextCurrent ();

	if (gladLoadGL () == GL_FALSE)
		std::cout << "Failed to load OpenGL" << std::endl;

	// Setup OpenGL debugging
	glEnable ( GL_DEBUG_OUTPUT );
	glDebugMessageCallback ( GLDebugMessageCallback, nullptr );

	//glEnable ( GL_CULL_FACE );
	
	glEnable ( GL_DEPTH_TEST );

	//// Setup blending
	//glEnable ( GL_BLEND );
	//glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void OpenGLContext::GLDebugMessageCallback ( GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar * message,
	const void * userParam )
{
	std::cout << message << std::endl;
}
