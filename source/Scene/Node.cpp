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

	UpdateBoundingBox ();
}

void Node::GetBoundingBoxesRecursively ( std::vector <BoundingBox> & boundingBoxes ) const
{
	boundingBoxes.reserve ( boundingBoxes.size () + meshIndices.size () );

	for ( auto meshIndex : meshIndices )
		boundingBoxes.push_back ( scene->GetMeshes ()[meshIndex].GetBoundingBox () );
	
	for ( auto & child : children )
		child.GetBoundingBoxesRecursively ( boundingBoxes );
}

void Node::UpdateBoundingBox ()
{
	std::vector <BoundingBox> boundingBoxes;
	GetBoundingBoxesRecursively ( boundingBoxes );

	this->boundingBox.Compute ( boundingBoxes );
	this->boundingBox.Transform ( transform );

}