#pragma once

#include "Vertex.hpp"

class VertexBuffer
{
public:
	VertexBuffer ();
	VertexBuffer ( std::vector <Vertex> const & );
	VertexBuffer ( std::vector <float> const & );
	~VertexBuffer ();

	VertexBuffer ( VertexBuffer const & ) = delete;
	VertexBuffer ( VertexBuffer && );

	VertexBuffer & operator = ( VertexBuffer const & ) = delete;
	VertexBuffer & operator = ( VertexBuffer && );

private:
	GLuint vertexBuffer { 0 };

	friend class VertexArray;
};