#include "SceneRenderer.hpp"

#include "Window.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Mesh.hpp"
#include "Scene/Material.hpp"
#include "Scene/Light.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Node.hpp"
#include "BoundingBox.hpp"

SceneRenderer::SceneRenderer () {}

SceneRenderer::SceneRenderer ( Window & window )
: 
	window ( & window ),

	vertexArray { {
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 4 },
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 2 },
	} },

	shader { "shaders/Shader.glsl" },

	cubeVertexArray { { { GL_FLOAT, 3 } } },

	cubeVertexBuffer ( {
	// Front face
	-0.5f, -0.5f,  0.5f,  // Bottom-left
	 0.5f, -0.5f,  0.5f,  // Bottom-right
	 0.5f,  0.5f,  0.5f,  // Top-right
	 0.5f,  0.5f,  0.5f,  // Top-right
	-0.5f,  0.5f,  0.5f,  // Top-left
	-0.5f, -0.5f,  0.5f,  // Bottom-left

	// Back face
	-0.5f, -0.5f, -0.5f,  // Bottom-left
	 0.5f, -0.5f, -0.5f,  // Bottom-right
	 0.5f,  0.5f, -0.5f,  // Top-right
	 0.5f,  0.5f, -0.5f,  // Top-right
	-0.5f,  0.5f, -0.5f,  // Top-left
	-0.5f, -0.5f, -0.5f,  // Bottom-left

	// Right face
	 0.5f, -0.5f, -0.5f,  // Bottom-back
	 0.5f, -0.5f,  0.5f,  // Bottom-front
	 0.5f,  0.5f,  0.5f,  // Top-front
	 0.5f,  0.5f,  0.5f,  // Top-front
	 0.5f,  0.5f, -0.5f,  // Top-back
	 0.5f, -0.5f, -0.5f,  // Bottom-back

	 // Left face
	 -0.5f, -0.5f, -0.5f,  // Bottom-back
	 -0.5f, -0.5f,  0.5f,  // Bottom-front
	 -0.5f,  0.5f,  0.5f,  // Top-front
	 -0.5f,  0.5f,  0.5f,  // Top-front
	 -0.5f,  0.5f, -0.5f,  // Top-back
	 -0.5f, -0.5f, -0.5f,  // Bottom-back

	 // Top face
	 -0.5f,  0.5f, -0.5f,  // Back-left
	  0.5f,  0.5f, -0.5f,  // Back-right
	  0.5f,  0.5f,  0.5f,  // Front-right
	  0.5f,  0.5f,  0.5f,  // Front-right
	 -0.5f,  0.5f,  0.5f,  // Front-left
	 -0.5f,  0.5f, -0.5f,  // Back-left

	 // Bottom face
	 -0.5f, -0.5f, -0.5f,  // Back-left
	  0.5f, -0.5f, -0.5f,  // Back-right
	  0.5f, -0.5f,  0.5f,  // Front-right
	  0.5f, -0.5f,  0.5f,  // Front-right
	 -0.5f, -0.5f,  0.5f,  // Front-left
	 -0.5f, -0.5f, -0.5f,  // Back-left
		} ),

	cubeShader ( "shaders/SkyboxShader.glsl" )
{
}

void SceneRenderer::SetScene ( Scene & scene )
{
	this->scene = &scene;	
	
	for ( auto const & node : scene.nodes )
		AddNode ( node );
}

void SceneRenderer::Render ()
{
	RenderSkybox ();
	
	shader.Bind ();
	vertexArray.Bind ();

	scene->camera.Bind ( shader );
	scene->lightSetup.Bind ( shader );

	c = 0;

	for (auto & node : scene->nodes)
		RenderNode ( node );
	
	//std::cout << "culled draw count: " << c << std::endl;

	vertexArray.Unbind ();
	shader.Unbind ();
}

bool SceneRenderer::CheckInView ( Node const & node, unsigned int meshIndex )
{
	auto const & mesh { scene->GetMeshes ()[meshIndex] };
	BoundingBox nodebbViewSpace { mesh.GetBoundingBox () };

	nodebbViewSpace.Transform ( scene->camera.GetViewMatrix () * node.transform );

	float width { 20 };
	float height { 20 };

	BoundingBox frustumBoundingBox;
	
	frustumBoundingBox.Compute ( {
		{ - width / 2.0f, -height / 2.0f, -10000.0f },
		{ width / 2.0f,  height / 2.0f, 0.1f }
	} );

	return frustumBoundingBox.Intersects ( nodebbViewSpace );
}

void SceneRenderer::AddNode ( Node const & node )
{
	for (auto meshIndex : node.meshIndices)
	{
		auto & mesh { scene->GetMeshes ()[meshIndex] };
		auto & material { scene->GetMaterials ()[mesh.GetMaterialIndex ()] };
	}

	for (auto const & child : node.children )
		AddNode ( child );
}

void SceneRenderer::RenderNode ( Node const & node )
{
	// Render this node
	shader.SetUniform ( "u_modelMatrix", node.transform );
	shader.SetUniform ( "u_normalMatrix", node.normalMatrix );

	for (auto meshIndex : node.meshIndices)
	{
		auto & mesh { scene->GetMeshes ()[meshIndex] };
		auto & material { scene->GetMaterials ()[mesh.GetMaterialIndex ()] };

		if ( CheckInView ( node, meshIndex ) )
		{
			mesh.Bind ( vertexArray );
			material.Bind ( shader );
			mesh.Draw ();
		}
		else {
			++c;
		}
	}

	// Render children recursively
	for ( auto & child : node.children )
		RenderNode ( child );
}

void SceneRenderer::RenderSkybox ()
{
	glDepthMask ( GL_FALSE );

	cubeVertexArray.Bind ();
	cubeShader.Bind ();

	scene->camera.Bind ( cubeShader );

	cubeShader.SetUniform ( "u_texture", 0 );
	scene->skybox.Bind ( 0 );

	cubeVertexArray.BindVertexBuffer ( cubeVertexBuffer, sizeof ( float ) * 3 );

	glDrawArrays ( GL_TRIANGLES, 0, 36 );

	cubeVertexArray.Unbind ();
	cubeShader.Unbind ();

	glDepthMask ( GL_TRUE );
}