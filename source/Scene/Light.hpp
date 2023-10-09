#pragma once

#include "../OpenGL/UniformBuffer.hpp"

class Shader;

class Light
{
public:
	enum class Types { point, directional };

	Types type { Types::point };

	glm::vec3 position	{ 0.0f, 0.0f, 0.0f };
	glm::vec3 color		{ 1.0f, 1.0f, 1.0f };
	glm::vec3 direction { 0.0f, 0.0f, 0.0f };
	float attenuation	{ 0.01f };

	friend class LightSetup;
};

class LightSetup
{
public:
	LightSetup ();
	LightSetup ( std::vector <Light> const & );

	void Bind ( Shader & );

private:
	static inline constexpr int maxLights { 500 };
	
	struct UniformBlockLightData
	{
	public:
		glm::vec4 position_type;
		glm::vec4 color_attenuation;
		glm::vec4 direction;
	};

	struct UniformBlockData
	{
		glm::vec4 count { 0, 0, 0, 0 };
		UniformBlockLightData lights [ maxLights ];
	};

	int GetLightTypeInt ( Light::Types );

	UniformBuffer lightsUniformBuffer;
};