#include "SceneRenderer.hpp"

#include "Window.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Mesh.hpp"
#include "Scene/Material.hpp"
#include "Scene/Light.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Node.hpp"
#include "BoundingBox.hpp"

SceneRenderer::SceneRenderer ( Assimp::Importer & importer, Window & window )
: 
	window ( & window ),
	debugRenderer ( importer ),

	vertexArray { {
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 4 },
		{ GL_FLOAT, 3 },
		{ GL_FLOAT, 2 },
	} },

	shader { "shaders/Shader.glsl" },
	shadowMapShader { "shaders/ShadowMapShader.glsl" },

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
	for ( auto const & light : scene->lightSetup.GetLights () )
		UpdateLightShadowMap ( light );

	glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
	auto windowSize { window->GetSize () };
	glViewport ( 0, 0, windowSize.x, windowSize.y );
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
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

	scene->DebugRender ( debugRenderer );
}

void SceneRenderer::UpdateLightShadowMap ( Light const & light )
{
	glm::vec3 viewPosition{ glm::normalize ( light.direction ) * -100.0f };
	
	//scene->camera.SetPosition ( viewPosition );
	//scene->camera.SetTargetDirection ( light.direction );

	glm::mat4 viewMatrix { glm::lookAt ( glm::zero <glm::vec3> (), light.direction, Directions::up)};

	glm::mat4 projectionMatrix { glm::ortho <float> ( -100, 100, -100, 100, -100, 100 ) };

	if ( light.type == Light::Types::directional )
	{
		light.shadowMap.BindFramebuffer ();
		
		glViewport ( 0, 0, 1000, 1000 );
		glClear ( GL_DEPTH_BUFFER_BIT );

		shadowMapShader.Bind ();
		vertexArray.Bind ();

		shadowMapShader.SetUniform ( "u_viewMatrix", viewMatrix );
		shadowMapShader.SetUniform ( "u_projectionMatrix", projectionMatrix );

		for ( auto const & node : scene->nodes )
			RenderNodeDepth ( node );

		vertexArray.Unbind ();
		shadowMapShader.Unbind ();

		light.shadowMap.UnbindFramebuffer ();
	}
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

void SceneRenderer::RenderNodeDepth ( Node const & node )
{
	// Render this node
	shadowMapShader.SetUniform ( "u_modelMatrix", node.transform );
	shadowMapShader.SetUniform ( "u_normalMatrix", node.normalMatrix );

	for ( auto meshIndex : node.meshIndices )
	{
		auto & mesh{ scene->GetMeshes ()[meshIndex] };

		mesh.Bind ( vertexArray );
		mesh.Draw ();
	}

	// Render children recursively
	for ( auto & child : node.children )
		RenderNodeDepth ( child );
}
