#pragma once

class IndexBuffer
{
public:
	IndexBuffer ();
	IndexBuffer ( std::vector <GLuint> const & );
	~IndexBuffer ();

	IndexBuffer ( IndexBuffer const & ) = delete;
	IndexBuffer ( IndexBuffer && );

	IndexBuffer & operator = ( IndexBuffer const & ) = delete;
	IndexBuffer & operator = ( IndexBuffer && );

	void Bind ();
	void Unbind ();

	GLuint GetIndexCount () const;

private:
	GLuint indexBuffer	{ 0 };
	GLuint indexCount	{ 0 };

	friend class VertexArray;
};

// Implementation
inline GLuint IndexBuffer::GetIndexCount () const { return indexCount; }
