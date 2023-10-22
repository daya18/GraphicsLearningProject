#pragma once

#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "Scene/Mesh.hpp"

class Renderer;
class Camera;
class ShadowMap;

class DebugRenderer
{
public:
	DebugRenderer ( Assimp::Importer & );
	
	void SetCamera ( Camera * );
	void RenderSphere ( glm::vec3 const & position, float scale = 1.0f, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f } );
	void RenderTexture ( GLuint texture, glm::vec3 const & position, float scale = 1.0f );

private:
	Mesh LoadMesh ( Assimp::Importer &, std::string const & filePath );

	Camera * camera { nullptr };
	VertexArray vertexArray;
	Shader shader;
	Texture whiteTexture;
	Mesh sphereMesh;
	Mesh planeMesh;
};