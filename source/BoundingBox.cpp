#include "BoundingBox.hpp"

BoundingBox::BoundingBox ()
	: vertices {}
{
}

void BoundingBox::Compute ( std::vector <glm::vec3> const & vertices )
{
	glm::vec3 min = { std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity () };
	glm::vec3 max = { -std::numeric_limits<float>::infinity (), -std::numeric_limits<float>::infinity (), -std::numeric_limits<float>::infinity () };

	for (auto const & vertex : vertices)
	{
		min = glm::min ( min, vertex );
		max = glm::max ( max, vertex );
	}

	this->vertices = {
		min,
		max,
		{ min.x, min.y, max.z},
		{ max.x, min.y, max.z },
		{ min.x, max.y, max.z },
		{ max.x, min.y, min.z },
		{ max.x, max.y, min.z },
		{ min.x, max.y, min.z }
	};

	UpdateMinMax ();
}

bool BoundingBox::Intersects ( BoundingBox const & rhs ) const
{
	if ( rhs.min.x > max.x || min.x > rhs.max.x )
		return false;
	
	if ( rhs.min.y > max.y || min.y > rhs.max.y )
		return false;

	if ( rhs.min.z > max.z || min.z > rhs.max.z )
		return false;

	return true;
}

void BoundingBox::Transform ( glm::mat4 const & transform )
{
	for ( auto & vertex : vertices)
		vertex = glm::vec3 ( transform * glm::vec4 ( vertex, 1.0f ) );

	UpdateMinMax ();
}

void BoundingBox::UpdateMinMax ()
{
	min = { std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity () };
	max = { -std::numeric_limits<float>::infinity (), -std::numeric_limits<float>::infinity (), -std::numeric_limits<float>::infinity () };

	for (auto const & vertex : vertices)
	{
		//if (vertex < min) min = vertex;

		min = glm::min ( min, vertex );
		max = glm::max ( max, vertex );
	}
}
