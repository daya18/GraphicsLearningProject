#pragma once

#include "../OpenGL/VertexBuffer.hpp"
#include "../OpenGL/IndexBuffer.hpp"
#include "../BoundingBox.hpp"

class VertexArray;

class Mesh
{
public:
	Mesh ();
	Mesh ( aiMesh &, unsigned int firstMaterialIndex );

	void Bind ( VertexArray & );
	void Draw ();

	unsigned int GetMaterialIndex () const;
	BoundingBox const & GetBoundingBox () const;
	std::vector <Vertex> const & GetVertices () const;

private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	unsigned int materialIndex;
	BoundingBox boundingBox;
	std::vector <Vertex> vertices;
};

// Implementation
inline Mesh::Mesh () {}
inline unsigned int Mesh::GetMaterialIndex () const { return materialIndex; }
inline BoundingBox const & Mesh::GetBoundingBox () const { return boundingBox; }
inline std::vector <Vertex> const & Mesh::GetVertices () const { return vertices; }
