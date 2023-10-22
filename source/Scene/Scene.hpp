#pragma once

#include "../OpenGL/Cubemap.hpp"

#include "Camera.hpp"
#include "../CameraController.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Node.hpp"
#include "../BoundingBox.hpp"

class Renderer;
class DebugRenderer;
class Window;

// To Do: Implement move semantics

class Scene
{
public:
	Scene ();
	Scene ( Window & );

	Scene ( Scene const & ) = delete;
	Scene ( Scene && ) = delete;

	Scene & operator = ( Scene const & ) = delete;	
	Scene & operator = ( Scene && ) = delete;

	void AddFromFile ( Assimp::Importer & importer, std::string const & filePath );
	void Clear ();
	
	void Update ( float delta );
	virtual void DebugRender ( DebugRenderer & );

	Camera & GetCamera ();
	LightSetup & GetLightSetup ();
	Cubemap & GetSkybox ();
	std::vector <Mesh> & GetMeshes ();
	std::vector <Material> & GetMaterials ();
	BoundingBox const & GetBoundingBox () const;

private:
	void GetBoundingBoxesRecursively ( std::vector <BoundingBox> &, Node const * );
	void UpdateBoundingBox ();

	std::vector <Mesh> meshes;
	std::vector <Material> materials;
	std::vector <Node> nodes;
	Cubemap skybox;
	Camera camera;
	CameraController cameraController;
	LightSetup lightSetup;
	BoundingBox boundingBox;

	friend class SceneRenderer;
};

inline std::vector <Mesh> & Scene::GetMeshes () { return meshes; }
inline std::vector <Material> & Scene::GetMaterials () { return materials; }
inline Camera & Scene::GetCamera () { return camera; }
inline LightSetup & Scene::GetLightSetup () { return lightSetup; }
inline Cubemap & Scene::GetSkybox () { return skybox; }
inline BoundingBox const & Scene::GetBoundingBox () const { return boundingBox; }
