#pragma once

class BoundingBox
{
public:
	BoundingBox ();

	// Compute from a set of points
	void Compute ( std::vector <glm::vec3> const & );
	void Compute ( std::vector <BoundingBox> const & );

	// Check intersection with another bounding box
	bool Intersects ( BoundingBox const & ) const;

	void Transform ( glm::mat4 const & );
	std::array <glm::vec3, 8> const & GetVertices () const;

private:
	void UpdateMinMax ();
	//glm::vec3 const & GetMin () const;
	//glm::vec3 const & GetMax () const;

	std::array <glm::vec3, 8>  vertices;

public:
	glm::vec3 min;
	glm::vec3 max;
};
//
//inline glm::vec3 const & BoundingBox::GetMin () const { return vertices [0]; };
//inline glm::vec3 const & BoundingBox::GetMax () const { return vertices [1]; };
inline std::array <glm::vec3, 8> const & BoundingBox::GetVertices () const { return vertices; }
