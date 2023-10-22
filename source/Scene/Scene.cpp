#include "Scene.hpp"

#include "../DebugRenderer.hpp"
#include "../Window.hpp"
#include "../Utility.hpp"
#include "Node.hpp"

Scene::Scene () {}

Scene::Scene ( Window & window )
:  
	skybox ( {
		{ Sides::left,		"images/envmap_miramar/miramar_lf.tga" },
		{ Sides::right,		"images/envmap_miramar/miramar_rt.tga" },
		{ Sides::top,		"images/envmap_miramar/miramar_up.tga" },
		{ Sides::bottom,	"images/envmap_miramar/miramar_dn.tga" },
		{ Sides::front,		"images/envmap_miramar/miramar_bk.tga" },
		{ Sides::back,		"images/envmap_miramar/miramar_ft.tga" }
	} ),

	camera ( { 0, 0, 10 }, { 0, 0, -1 } ),
	cameraController ( window, camera )
{
	camera.SetViewportSize ( window.GetSize () );
	

	// --------------------
}

void Scene::AddFromFile ( Assimp::Importer & importer, std::string const & filePath )
{
	Assert ( std::filesystem::exists ( filePath ), "Scene file " + filePath + " doesnt exist" );

	aiScene const * scene { importer.ReadFile ( 
		filePath, 
		  aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices
		/*| aiProcess_OptimizeMeshes | aiProcess_RemoveRedundantMaterials 
		| aiProcess_OptimizeGraph  
		| aiProcess_ImproveCacheLocality | aiProcessPreset_TargetRealtime_Fast*/ ) };
	
	std::cout << "Scene file parsed: " << filePath << std::endl;

	unsigned int firstMeshIndex { static_cast <unsigned int> ( meshes.size () ) };
	unsigned int firstMaterialIndex { static_cast <unsigned int> ( materials.size () ) };

	meshes.reserve ( meshes.size () + scene->mNumMeshes );
	for (int i { 0 }; i < scene->mNumMeshes; ++i)
		meshes.push_back ( { *scene->mMeshes[i], firstMaterialIndex } );

	materials.reserve ( materials.size () + scene->mNumMaterials );
	for (int i { 0 }; i < scene->mNumMaterials; ++i )
		materials.push_back ( { std::filesystem::path { filePath }.parent_path (), *scene->mMaterials[i] } );

	nodes.push_back ( { Node { *this, scene->mRootNode, firstMeshIndex } } );

	importer.FreeScene ();
	
	std::cout << "Scene file loaded: " << filePath << std::endl;
}

void Scene::Clear ()
{
	meshes.clear ();
	materials.clear ();
	nodes.clear ();
}

void Scene::Update ( float delta )
{
	cameraController.Update ( delta );
}

void Scene::DebugRender ( DebugRenderer & renderer )
{
	renderer.SetCamera ( &camera );
}