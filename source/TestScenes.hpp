#pragma once

#include "Scene/Scene.hpp"

class Window;


class TestScene : public Scene
{
public:
	TestScene ( Window &, Assimp::Importer & importer );
};



class Sponza : public Scene
{
public:
	Sponza ( Window &, Assimp::Importer & importer );
};



class CornellBox : public Scene
{
public:
	CornellBox ( Window &, Assimp::Importer & importer );

	void DebugRender ( DebugRenderer & renderer ) override;

private:
	static constexpr glm::vec3 lightPosition { 0, 1, 2 };
};



class VokseliaSpawn : public Scene
{
public:
	VokseliaSpawn ( Window &, Assimp::Importer & importer );
};
