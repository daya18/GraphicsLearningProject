#pragma once

#include "../OpenGL/UniformBuffer.hpp"
#include "../OpenGL/ShadowMap.hpp"

class Shader;

class Light
{
public:
	enum class Types { point, directional };

	Light ( 
		Types						=	{ Types::point },
		glm::vec3 const & position	=	{ 0.0f, 0.0f, 0.0f },
		glm::vec3 const & color		=	{ 1.0f, 1.0f, 1.0f },
		glm::vec3 const & direction =	{ 0.0f, 0.0f, 0.0f },
		float attenuation			=	{ 0.01f }
	);
	
	Light ( Light && ) = default;

	Types type;

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float attenuation;

//private:
	ShadowMap shadowMap;

	friend class LightSetup;
	friend class SceneRenderer;
};

class LightSetup
{
public:
	LightSetup ();
	LightSetup ( std::vector <Light> && );

	void Bind ( Shader & );

	std::vector <Light> const& GetLights () const;

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

	std::vector <Light> lights;
	UniformBuffer lightsUniformBuffer;
};


// Implementation
inline std::vector <Light> const & LightSetup::GetLights () const { return lights; }
