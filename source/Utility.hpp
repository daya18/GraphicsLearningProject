#pragma once

#define Assert(x,message) AssertFunction ( x, message )

namespace Colors
{
	constexpr glm::vec4 white	{ 1.0f, 1.0f, 1.0f, 1.0f };
	constexpr glm::vec4 red		{ 1.0f, 0.0f, 0.0f, 1.0f };
	constexpr glm::vec4 green	{ 0.0f, 1.0f, 0.0f, 1.0f };
	constexpr glm::vec4 blue	{ 0.0f, 0.0f, 1.0f, 1.0f };
}

namespace Directions
{
	constexpr glm::vec3 up		{  0.0f,  1.0f,  0.0f };
	constexpr glm::vec3 down	{  0.0f, -1.0f,  0.0f };
	constexpr glm::vec3 left	{ -1.0f,  0.0f,  0.0f };
	constexpr glm::vec3 right	{  1.0f,  0.0f,  0.0f };
	constexpr glm::vec3 forward	{  0.0f,  0.0f, -1.0f };
	constexpr glm::vec3 back	{  0.0f,  0.0f,  1.0f };
}

enum class Sides { left, right, top, bottom, front, back };

glm::mat4 AssimpToGlmMatrix ( const aiMatrix4x4 & assimpMatrix );
int GetGLTypeSize ( GLenum type );
void AssertFunction ( bool exp, std::string const & message );
