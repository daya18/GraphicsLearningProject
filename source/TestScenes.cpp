#include "TestScenes.hpp"

#include "DebugRenderer.hpp"

TestScene::TestScene ( Window& window, Assimp::Importer& importer )
	: Scene ( window )
{
	AddFromFile ( importer, "scenes/living_room/living_room.obj" );

	GetCamera ().SetPosition ( { 0, 0, 0 } );
	GetCamera ().SetTargetDirection ( { 0, 0, -1 } );

	/*Light light1 {
		Light::Types::point,
		{ -6.0f, 10.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{},
		0.05f
	};

	Light light2 {
		Light::Types::point,
		{ 6.0f, 10.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{},
		0.05f
	};*/

	;
	std::vector <Light> lights;
	
	lights.emplace_back ( Light{
			Light::Types::directional,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.99f, 0.98f, 0.82f },
			{ 0.0f, -1.0f, -1.0f },
			0.0f
	} );

	GetLightSetup () = LightSetup { std::move ( lights ) };
}



Sponza::Sponza ( Window & window, Assimp::Importer & importer )
	: Scene ( window )
{
	AddFromFile ( importer, "scenes/sponza/sponza.obj" );

	GetCamera ().SetPosition ( { 0, 10, 0 } );
	GetCamera ().SetTargetDirection ( { 1, 0, 0 } );

	/*Light light1 {
		Light::Types::point,
		{ -6.0f, 10.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{},
		0.05f
	};

	Light light2 {
		Light::Types::point,
		{ 6.0f, 10.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{},
		0.05f
	};*/

	std::vector <Light> lights;

	lights.emplace_back ( Light{
			Light::Types::directional,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.99f, 0.98f, 0.82f },
			{ 0.0f, -1.0f, -1.0f },
			0.0f
		} );

	GetLightSetup () = LightSetup { std::move ( lights ) };
}

void Sponza::DebugRender ( DebugRenderer & renderer )
{
	Scene::DebugRender ( renderer );

	renderer.SetCamera ( nullptr );
	renderer.RenderTexture ( GetLightSetup ().GetLights ()[0].shadowMap.texture, { 0, 0, 0 }, 0.3f );
}



CornellBox::CornellBox ( Window & window, Assimp::Importer & importer )
	: Scene ( window ), texture ( "images/clouds1/clouds1_down.bmp" )
{
	AddFromFile ( importer, "scenes/CornellBox/CornellBox-Original.obj" );

	GetCamera ().SetPosition ( { 0, 1, 2 } );
	GetCamera ().SetTargetDirection ( { 0, 0, -1 } );
	
	std::vector <Light> lights;

	lights.emplace_back ( Light { Light::Types::point, lightPosition, { 1.0f, 1.0f, 1.0f } } ),

	GetLightSetup () = LightSetup { std::move ( lights ) };
}

void CornellBox::DebugRender ( DebugRenderer & renderer )
{
	Scene::DebugRender ( renderer );

	renderer.SetCamera ( &GetCamera () );
	renderer.RenderSphere ( lightPosition, 0.1f );
	
	renderer.SetCamera ( nullptr );
	renderer.RenderTexture ( GetLightSetup ().GetLights()[0].shadowMap.texture, {0, 0, 0}, 0.3f);
}



VokseliaSpawn::VokseliaSpawn ( Window & window, Assimp::Importer & importer )
	: Scene ( window )
{
	AddFromFile ( importer, "scenes/vokselia_spawn/vokselia_spawn.obj" );

	GetCamera ().SetPosition ( { 0, 0, 0 } );
	GetCamera ().SetTargetDirection ( { 0, 0, -1 } );

	std::vector <Light> lights;

	lights.emplace_back ( Light {
		Light::Types::directional,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.99f, 0.98f, 0.82f },
			{ 0.0f, -1.0f, -1.0f },
			0.0f
	} );

	GetLightSetup () = LightSetup { std::move ( lights ) };
}