#include "Application.hpp"

#include "Utility.hpp"

#include "TestScenes.hpp"

Application::Application ()
: 
	window ( "Graphics Learning Project", { 1280, 720 }),
	openGLContext ( window ),
	sceneRenderer { importer, window },
	scene ( std::make_unique <Sponza> ( window, importer ) )	
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
		
		scene->Update ( profiler.GetLastFrameDuration () );
		sceneRenderer.Render ();
		//scene->DebugRender ( debugRenderer );

		window.SwapBuffers ();
		
		profiler.EndFrame ();
	}
}