#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer () {}

VertexBuffer::VertexBuffer ( std::vector <Vertex> const & vertices )
{
	glGenBuffers ( 1, &vertexBuffer );

	glBindBuffer ( GL_ARRAY_BUFFER, vertexBuffer );
	
	glBufferData ( GL_ARRAY_BUFFER, 
		vertices.size () * sizeof ( Vertex ), vertices.data (), GL_STATIC_DRAW );
	
	glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}

VertexBuffer::VertexBuffer ( std::vector <float> const & vertices )
{
	glGenBuffers ( 1, &vertexBuffer );

	glBindBuffer ( GL_ARRAY_BUFFER, vertexBuffer );

	glBufferData ( GL_ARRAY_BUFFER,
		vertices.size () * sizeof ( float ), vertices.data (), GL_STATIC_DRAW );

	glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}

VertexBuffer::~VertexBuffer ()
{
	if (vertexBuffer)
		glDeleteBuffers ( 1, &vertexBuffer );
}

VertexBuffer::VertexBuffer ( VertexBuffer && r )
{
	operator = ( std::move ( r ) );
}

VertexBuffer & VertexBuffer::operator = ( VertexBuffer && r )
{
	vertexBuffer = std::exchange ( r.vertexBuffer, 0 );
	return *this;
}