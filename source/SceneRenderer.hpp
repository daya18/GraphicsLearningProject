#pragma once

#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/UniformBuffer.hpp"
#include "DebugRenderer.hpp"

class Window;

class Node;
class Mesh;
class Material;
class Camera;
class LightSetup;
class Cubemap;
class Scene;
class Light;

class SceneRenderer
{
public:
	SceneRenderer ( Assimp::Importer &, Window & );

	void SetScene ( Scene & );

	void Render ();

private:
	void UpdateLightShadowMap ( Light const & );
	bool CheckInView ( Node const &, unsigned int mesh );
	void AddNode ( Node const & );
	void RenderNode ( Node const & );
	void RenderSkybox ();
	void RenderNodeDepth ( Node const & );

	Window * window;
	DebugRenderer debugRenderer;
	Scene * scene;
	VertexArray vertexArray;
	Shader shader;
	Shader shadowMapShader;
	UniformBuffer pointLightBuffer;
	VertexArray cubeVertexArray;
	VertexBuffer cubeVertexBuffer;
	Shader cubeShader;
	int c;
};