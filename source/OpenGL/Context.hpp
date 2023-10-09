#pragma once

class Window;

// OpenGL context specific setup, including loading
class OpenGLContext
{
public:
	OpenGLContext ( Window & );

private:
	static void GLDebugMessageCallback ( GLenum source,
		GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void * );
};
