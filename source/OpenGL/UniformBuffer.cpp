#include "UniformBuffer.hpp"

UniformBuffer::UniformBuffer () {}

UniformBuffer::~UniformBuffer ()
{
	if ( uniformBuffer )
		glDeleteBuffers ( 1, &uniformBuffer );
}

UniformBuffer::UniformBuffer ( UniformBuffer && r )
{
	operator = ( std::move ( r ) );
}

UniformBuffer & UniformBuffer::operator = ( UniformBuffer && r )
{
	uniformBuffer = std::exchange ( r.uniformBuffer, 0 );
	return *this;
}