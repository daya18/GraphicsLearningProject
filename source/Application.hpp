#pragma once

#include "OpenGL/Context.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "Scene/Scene.hpp"
#include "SceneRenderer.hpp"
#include "Window.hpp"
#include "Profiler.hpp"

class Application
{
public:
	Application ();
	
	void Run ();
	
private:
	bool quit { false };

	Window window;
	Assimp::Importer importer;
	OpenGLContext openGLContext;
	SceneRenderer sceneRenderer;
	VertexBuffer vertexBuffer;
	std::unique_ptr <Scene> scene;
	Profiler profiler;
};