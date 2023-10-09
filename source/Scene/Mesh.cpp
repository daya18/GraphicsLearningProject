#include "Mesh.hpp"

#include "../OpenGL/VertexArray.hpp"
										// "materialIndexOffset"?
Mesh::Mesh ( aiMesh & mesh, unsigned int firstMaterialIndex )
{
	std::vector <glm::vec3> vertexPositions;
	std::vector <GLuint> indices;

	vertexPositions.reserve ( vertexPositions.size () + mesh.mNumVertices );
	vertices.reserve ( vertices.size () + mesh.mNumVertices );
	indices.reserve ( indices.size () + mesh.mNumFaces * 3 );

	for (int vertexIndex { 0 }; vertexIndex < mesh.mNumVertices; ++vertexIndex)
	{
		auto aiVertex { mesh.mVertices[vertexIndex] };
		auto aiNormal { mesh.mNormals[vertexIndex] };

		glm::vec3 position { aiVertex.x, aiVertex.y, aiVertex.z };
		glm::vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec3 normal { aiNormal.x, aiNormal.y, aiNormal.z };
		glm::vec2 texCoords { 0.0f, 0.0f };

		if ( mesh.HasTextureCoords ( 0 ) )
		{
			aiVector3D aiTexCoords { mesh.mTextureCoords[0][vertexIndex] };
			texCoords = { aiTexCoords.x, aiTexCoords.y };
		}

		vertices.push_back ( { position, color, normal, texCoords } );
		vertexPositions.push_back ( position );
	}

	for (int faceIndex { 0 }; faceIndex < mesh.mNumFaces; ++faceIndex)
	{
		auto & face { mesh.mFaces[faceIndex] };
		for (int indexIndex { 0 }; indexIndex < face.mNumIndices; ++indexIndex)
			indices.push_back ( face.mIndices[indexIndex] );
	}
	
	boundingBox.Compute ( vertexPositions );

	vertexBuffer = VertexBuffer { vertices };
	indexBuffer = IndexBuffer { indices };
	materialIndex = firstMaterialIndex + mesh.mMaterialIndex;
}

void Mesh::Bind ( VertexArray & vertexArray )
{
	vertexArray.BindVertexBuffer ( vertexBuffer );
	indexBuffer.Bind ();
}

void Mesh::Draw ()
{
	glDrawElements ( GL_TRIANGLES, indexBuffer.GetIndexCount (), GL_UNSIGNED_INT, 0 );
}