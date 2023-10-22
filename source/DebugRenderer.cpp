#include "DebugRenderer.hpp"

#include "Utility.hpp"

//#include "Renderer.hpp"
#include "Scene/Camera.hpp"

DebugRenderer::DebugRenderer ( Assimp::Importer & importer )
	:
	vertexArray{ {
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 4 },
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 2 },
	} },

	shader ( "shaders/DebugShader.glsl" ),
	whiteTexture ( { Colors::white }, 1),

	sphereMesh ( LoadMesh ( importer, "scenes/Sphere.obj" ) ),
	planeMesh ( LoadMesh ( importer, "scenes/Plane.obj" ) )
{
}

void DebugRenderer::SetCamera ( Camera * camera )
{
	if ( this->camera )
		this->camera->Unbind ( shader );

	this->camera = camera;
	
	if ( this->camera ) 
		this->camera->Bind ( shader );
}

void DebugRenderer::RenderSphere ( glm::vec3 const & position, float scale, glm::vec4 color )
{
	vertexArray.Bind ();
	shader.Bind ();

	shader.SetUniform ( "u_texture", 0 );
	whiteTexture.Bind ( 0 );

	shader.SetUniform ( "u_position", position );
	shader.SetUniform ( "u_scale", scale );
	shader.SetUniform ( "u_color", color );

	sphereMesh.Bind ( vertexArray );
	sphereMesh.Draw ();

	shader.Unbind ();
	vertexArray.Unbind ();
}

void DebugRenderer::RenderTexture ( GLuint texture, glm::vec3 const & position, float scale )
{
	vertexArray.Bind ();
	shader.Bind ();

	//if ( camera ) camera->Bind ( shader );
	
	shader.SetUniform ( "u_texture", 0 );
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, texture );

	shader.SetUniform ( "u_position", position );
	shader.SetUniform ( "u_scale", scale );
	shader.SetUniform ( "u_color", Colors::white );

	planeMesh.Bind ( vertexArray );
	planeMesh.Draw ();

	shader.Unbind ();
	vertexArray.Unbind ();
}

Mesh DebugRenderer::LoadMesh ( Assimp::Importer & importer, std::string const & filePath )
{
	aiScene const * scene { importer.ReadFile ( filePath, aiProcess_Triangulate ) };
	return { *scene->mMeshes[0], 0 };
}
