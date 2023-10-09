#pragma once

#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/UniformBuffer.hpp"

class Window;

class Node;
class Mesh;
class Material;
class Camera;
class LightSetup;
class Cubemap;
class Scene;

class SceneRenderer
{
public:
	SceneRenderer ();
	SceneRenderer ( Window & );

	void SetScene ( Scene & );

	void Render ();

private:
	bool CheckInView ( Node const &, unsigned int mesh );
	void AddNode ( Node const & );
	void RenderNode ( Node const & );
	void RenderSkybox ();

	Window * window;
	Scene * scene;
	VertexArray vertexArray;
	Shader shader;
	UniformBuffer pointLightBuffer;
	VertexArray cubeVertexArray;
	VertexBuffer cubeVertexBuffer;
	Shader cubeShader;
	int c;
};

// Implementation
//inline VertexArray & Renderer::GetVertexArray () { return vertexArray; }
//inline Shader & Renderer::GetShader () { return shader; }
//inline Window & Renderer::GetWindow () const { return *window; }
//inline void Renderer::SetSkybox ( Cubemap & skybox ) { this->skybox = &skybox; }
//inline void Renderer::SetCamera ( Camera & camera ) { this->camera = &camera; }
//inline void Renderer::SetLightSetup ( LightSetup & lightSetup ) { this->lightSetup = &lightSetup; }