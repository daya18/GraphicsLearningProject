#include "DebugRenderer.hpp"

//#include "Renderer.hpp"
#include "Scene/Camera.hpp"

DebugRenderer::DebugRenderer ( Assimp::Importer & importer )
: 
	vertexArray { {
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 4 },
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 2 },
	} },

	shader ( "shaders/DebugShader.glsl" ),
	
	sphereMesh ( LoadMesh ( importer, "scenes/Sphere.obj" ) )
{
}

void DebugRenderer::SetCamera ( Camera & camera )
{
	this->camera = &camera;
}

void DebugRenderer::RenderSphere ( glm::vec3 const & position, float scale, glm::vec4 color )
{
	vertexArray.Bind ();
	shader.Bind ();

	if ( camera ) camera->Bind ( shader );

	shader.SetUniform ( "u_position", position );
	shader.SetUniform ( "u_scale", scale );
	shader.SetUniform ( "u_color", color );

	sphereMesh.Bind ( vertexArray );
	sphereMesh.Draw ();

	shader.Unbind ();
	vertexArray.Unbind ();
}

Mesh DebugRenderer::LoadMesh ( Assimp::Importer & importer, std::string const & filePath )
{
	aiScene const * scene { importer.ReadFile ( "scenes/Sphere.obj", aiProcess_Triangulate ) };
	return { *scene->mMeshes[0], 0 };
}
