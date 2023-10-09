#include "Application.hpp"

#include "Utility.hpp"

#include "TestScenes.hpp"

Application::Application ()
: 
	window ( "Graphics Learning Project", { 1280, 720 }),
	openGLContext ( window ),
	sceneRenderer { window },
	debugRenderer ( importer ),
	scene ( std::make_unique <CornellBox> ( window, importer ) )	
{
	sceneRenderer.SetScene ( *scene );
}

void Application::Run ()
{
	while ( ! quit )
	{
		profiler.BeginFrame ();

		glfwPollEvents ();

		if ( window.ShouldClose () ) quit = true;
		
		glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		scene->Update ( profiler.GetLastFrameDuration () );
		sceneRenderer.Render ();
		scene->DebugRender ( debugRenderer );

		window.SwapBuffers ();
		
		profiler.EndFrame ();
	}
}