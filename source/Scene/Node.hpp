#pragma once


class Renderer;
class Scene;

class Node
{
public:
	Node ();
	Node ( Scene &, aiNode *, unsigned int firstMeshIndex );
	
private:
	Scene * scene;
	std::string name;
	glm::mat4 transform;
	glm::mat3 normalMatrix;
	std::vector <unsigned int> meshIndices;
	std::vector <Node> children;

	friend class SceneRenderer;
	friend class Scene; // Temporary, for debugging
};