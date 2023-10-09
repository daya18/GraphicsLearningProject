#include "Node.hpp"

#include "../Utility.hpp"
#include "Scene.hpp"
//#include "../Renderer.hpp"

Node::Node () {}

														// "meshIndexOffset"?
Node::Node ( Scene & scene, aiNode * node, unsigned int firstMeshIndex )
:
	scene ( &scene ),
	name ( node->mName.C_Str () ),
	transform ( AssimpToGlmMatrix ( node->mTransformation ) ),
	normalMatrix { glm::transpose ( glm::inverse ( glm::mat3 { transform } ) ) }
{
	// Add mesh indices
	for (int meshIndex { 0 }; meshIndex < node->mNumMeshes; ++meshIndex)
		meshIndices.push_back ( firstMeshIndex + node->mMeshes [ meshIndex ] );

	// Add children
	children.reserve ( node->mNumChildren );
	for (int childIndex { 0 }; childIndex < node->mNumChildren; ++childIndex)
		children.push_back ( { scene, node->mChildren[childIndex], firstMeshIndex } );

}
