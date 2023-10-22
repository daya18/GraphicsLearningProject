#pragma once

#include "../BoundingBox.hpp"

class Renderer;
class Scene;

class Node
{
public:
	Node ();
	Node ( Scene &, aiNode *, unsigned int firstMeshIndex );
	
	BoundingBox const & GetBoundingBox () const;

private:
	void GetBoundingBoxesRecursively ( std::vector <BoundingBox> & ) const;
	void UpdateBoundingBox ();

	//std::vector <BoundingBox> GetBoundingBoxesRecursively ( Node * );

	Scene * scene;
	std::string name;
	glm::mat4 transform;
	glm::mat3 normalMatrix;
	std::vector <unsigned int> meshIndices;
	std::vector <Node> children;
	BoundingBox boundingBox;

	friend class SceneRenderer;
	friend class Scene; // Temporary, for debugging
};

inline BoundingBox const & Node::GetBoundingBox () const { return boundingBox; }