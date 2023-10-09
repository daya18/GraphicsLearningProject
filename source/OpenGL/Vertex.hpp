#pragma once

struct Vertex
{
	glm::vec3 position	{ 0.0f, 0.0f, 0.0f };
	glm::vec4 color		{ 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec3 normal	{ 0.0f, 0.0f, 0.0f };
	glm::vec2 uv		{ 0.0f, 0.0f };
};