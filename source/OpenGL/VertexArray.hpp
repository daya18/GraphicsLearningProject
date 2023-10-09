#pragma once

class VertexBuffer;

class VertexArray
{
public:
	struct Attribute { GLenum type; GLuint count; };

	VertexArray ();
	VertexArray ( std::vector <Attribute> const & );
	~VertexArray ();

	VertexArray ( VertexArray const & ) = delete;
	VertexArray ( VertexArray && );

	VertexArray & operator = ( VertexArray const & ) = delete;
	VertexArray & operator = ( VertexArray && );

	void Bind ();
	void Unbind ();

	void BindVertexBuffer ( VertexBuffer const & );
	void BindVertexBuffer ( VertexBuffer const &, GLsizei vertexSize );

private:
	GLuint vertexArray { 0 };
	GLuint vertexSize { 0 };
};