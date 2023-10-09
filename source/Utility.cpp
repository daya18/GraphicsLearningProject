#include "Utility.hpp"

int GetGLTypeSize ( GLenum type )
{
	switch (type)
	{
	case GL_FLOAT: return sizeof ( GLfloat );
	case GL_INT: return sizeof ( GLint );
	case GL_UNSIGNED_INT: sizeof ( GLuint );
	case GL_UNSIGNED_BYTE: sizeof ( GLubyte );
	}
}

glm::mat4 AssimpToGlmMatrix ( const aiMatrix4x4 & assimpMatrix )
{
	glm::mat4 glmMatrix;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			glmMatrix[j][i] = assimpMatrix[i][j]; // Note the swapped indices
		}
	}

	return glmMatrix;
}

void AssertFunction ( bool exp, std::string const & message )
{
	if ( ! exp )
	{
		std::cerr << "Assertion failed: " << message << std::endl;
		std::abort ();
	}
}