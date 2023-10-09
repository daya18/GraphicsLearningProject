#include "VertexArray.hpp"

#include "../Utility.hpp"
#include "VertexBuffer.hpp"

VertexArray::VertexArray () {}

VertexArray::VertexArray ( std::vector <Attribute> const & attributes )
{
	glGenVertexArrays ( 1, &vertexArray );
	glBindVertexArray ( vertexArray );

	int attributeIndex { 0 };
	int attributeOffset { 0 };

	for (auto const & attribute : attributes)
	{
		glEnableVertexAttribArray ( attributeIndex );
		glVertexAttribFormat ( attributeIndex, attribute.count, attribute.type, GL_FALSE, attributeOffset );
		glVertexAttribBinding ( attributeIndex, 0 );

		++attributeIndex;
		attributeOffset += GetGLTypeSize ( attribute.type ) * attribute.count;
		vertexSize += GetGLTypeSize ( attribute.type ) * attribute.count;
	}

	glBindVertexArray ( 0 );
}

VertexArray::VertexArray ( VertexArray && r )
{
	operator = ( std::move ( r ) );
}

VertexArray::~VertexArray ()
{
	if ( vertexArray )
		glDeleteVertexArrays ( 1, &vertexArray );
}

VertexArray & VertexArray::operator = ( VertexArray && r )
{
	vertexArray = std::exchange ( r.vertexArray, 0 );
	vertexSize = r.vertexSize;
	return *this;
}

void VertexArray::Bind ()
{
	glBindVertexArray ( vertexArray );
}

void VertexArray::Unbind ()
{
	glBindVertexArray ( 0 );
}

void VertexArray::BindVertexBuffer ( VertexBuffer const & vertexBuffer )
{
	glBindVertexBuffer ( 0, vertexBuffer.vertexBuffer, 0, vertexSize );
}

void VertexArray::BindVertexBuffer ( VertexBuffer const & vertexBuffer, GLsizei vertexSize )
{
	glBindVertexBuffer ( 0, vertexBuffer.vertexBuffer, 0, vertexSize );
}