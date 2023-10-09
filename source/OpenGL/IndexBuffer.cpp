#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer () {}

IndexBuffer::IndexBuffer ( std::vector <GLuint> const & indices )
	: indexCount ( indices.size () )
{
	glGenBuffers ( 1, &indexBuffer );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 
		indices.size () * sizeof ( GLuint ), indices.data (), GL_STATIC_DRAW );
	
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

IndexBuffer::~IndexBuffer ()
{
	if (indexBuffer)
		glDeleteBuffers ( 1, &indexBuffer );
}

IndexBuffer::IndexBuffer ( IndexBuffer && r )
{
	operator = ( std::move ( r ) );
}

IndexBuffer & IndexBuffer::operator = ( IndexBuffer && r )
{
	indexBuffer = std::exchange ( r.indexBuffer, 0 );
	indexCount = r.indexCount;

	return *this;
}

void IndexBuffer::Bind ()
{
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
}

void IndexBuffer::Unbind ()
{
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

