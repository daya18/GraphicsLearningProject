#include "Light.hpp"

#include "../OpenGL/Shader.hpp"

LightSetup::LightSetup () 
{
	std::unique_ptr <UniformBlockData> data { std::make_unique <UniformBlockData> () };
	data->count.x = 0;
	lightsUniformBuffer = UniformBuffer { *data };
}

LightSetup::LightSetup ( std::vector <Light> const & lights )
{
	if (lights.size () <= maxLights)
	{
		std::unique_ptr <UniformBlockData> data { std::make_unique <UniformBlockData> () };

		data->count.x = lights.size ();

		int index { 0 };
		for (auto const & light : lights)
		{
			auto & lightData { data->lights[index] };
			lightData.position_type = { light.position, GetLightTypeInt ( light.type ) };
			lightData.direction = glm::vec4 ( light.direction, 1.0f );
			lightData.color_attenuation = glm::vec4 ( light.color, light.attenuation );
			++index;
		}

		lightsUniformBuffer = UniformBuffer { *data };
	}
}

void LightSetup::Bind ( Shader & shader )
{
	shader.BindUniformBuffer ( "LightsBlock", lightsUniformBuffer );
}

int LightSetup::GetLightTypeInt ( Light::Types type )
{
	switch (type)
	{
	case Light::Types::point:		return 0;
	case Light::Types::directional: return 1;
	}
}
