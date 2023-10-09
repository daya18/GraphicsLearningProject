#pragma once

class UniformBuffer
{
public:
	UniformBuffer ();

	template < class Type >
	UniformBuffer ( Type const & );
	
	~UniformBuffer ();

	UniformBuffer ( UniformBuffer const & ) = delete;
	UniformBuffer ( UniformBuffer && );

	UniformBuffer & operator = ( UniformBuffer const & ) = delete;
	UniformBuffer & operator = ( UniformBuffer && );

private:
	GLuint uniformBuffer	{ 0 };

	friend class Shader;
};

// Implementation

template < class Type >
UniformBuffer::UniformBuffer ( Type const & data )
{
	glGenBuffers ( 1, &uniformBuffer );
	glBindBuffer ( GL_UNIFORM_BUFFER, uniformBuffer );
	glBufferData ( GL_UNIFORM_BUFFER, sizeof ( Type ), &data, GL_STATIC_DRAW );
	glBindBuffer ( GL_UNIFORM_BUFFER, 0 );
}