#shader vert

#version 460

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec4 i_color;
layout ( location = 2 ) in vec3 i_normal;
layout ( location = 3 ) in vec2 i_texCoords;

layout ( location = 0 ) out vec4 o_color;
layout ( location = 1 ) out vec3 o_normal;
layout ( location = 2 ) out vec3 o_fragPosWorldSpace;
layout ( location = 3 ) out vec2 o_texCoords;

uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4 ( i_position, 1.0f );
	o_color = i_color;
	o_normal = u_normalMatrix * i_normal;
	o_fragPosWorldSpace = vec3 ( u_modelMatrix * vec4 ( i_position, 1.0f ) );
	o_texCoords = i_texCoords;
}

#endshader



#shader frag

#version 460

layout ( location = 0 ) in vec4 i_color;
layout ( location = 1 ) in vec3 i_normal;
layout ( location = 2 ) in vec3 i_fragPosWorldSpace;
layout ( location = 3 ) in vec2 i_texCoords;

layout ( location = 0 ) out vec4 o_color;

uniform vec3 u_cameraPosition;

uniform vec4 u_ambientLight = vec4 ( 0.1f, 0.1f, 0.1f, 1.0f );

uniform vec4 u_ambientColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;

uniform float u_shininess;

uniform sampler2D u_ambientTexture;
uniform sampler2D u_diffuseTexture;

struct Light
{
	vec4 position_type;
	vec4 color_attenuation;
	vec4 direction;
};

uniform LightsBlock
{
	vec4 count;
	Light lights [ 500 ];
} 
lights;

vec3 CalculatePointLight ( Light light )
{
	vec3 fragNormal = normalize ( i_normal );

	vec3 color = vec3 ( 0, 0, 0 );

	float lightToFragDistance = length ( light.position_type.xyz - i_fragPosWorldSpace  );
	float attenuationFactor = 1.0f / ( 1.0f + light.color_attenuation.w * pow ( lightToFragDistance, 2.0f ) );

	vec3 lightDir = normalize ( light.position_type.xyz - i_fragPosWorldSpace );
	vec3 reflectDir = reflect ( -lightDir, fragNormal );
	vec3 fragViewDir = normalize ( u_cameraPosition - i_fragPosWorldSpace );

	// Diffuse
	float diffuseStrength = max ( dot ( fragNormal, lightDir ), 0.0f );
	color += diffuseStrength * attenuationFactor * light.color_attenuation.xyz * u_diffuseColor.rgb * texture ( u_diffuseTexture, i_texCoords ).rgb;
		
	// Specular
	float specularStrength = pow ( max ( dot ( fragViewDir, reflectDir ), 0.0f ), u_shininess );
	color += specularStrength * attenuationFactor * u_specularColor.rgb;
	
	return color;
}

vec3 CalculateDirectionalLight ( Light light )
{
	vec3 fragNormal = normalize ( i_normal );

	vec3 color = vec3 ( 0, 0, 0 );

	vec3 lightDir = normalize ( -light.direction.xyz );
	vec3 reflectDir = reflect ( -lightDir, fragNormal );
	vec3 fragViewDir = normalize ( u_cameraPosition - i_fragPosWorldSpace );

	// Diffuse
	float diffuseStrength = max ( dot ( fragNormal, lightDir ), 0.0f );
	color += diffuseStrength * light.color_attenuation.xyz * u_diffuseColor.rgb * texture ( u_diffuseTexture, i_texCoords ).rgb;
		
	// Specular
	float specularStrength = pow ( max ( dot ( fragViewDir, reflectDir ), 0.0f ), u_shininess );
	color += specularStrength * u_specularColor.rgb;
	
	return color;
}

void main ()
{

	// Ambient
	vec3 color = u_ambientLight.rgb * texture ( u_ambientTexture, i_texCoords ).rgb;

	for ( int i = 0; i < lights.count.x; ++i )
	{
		Light light = lights.lights [i];
		float lightType = light.position_type.w;

		if ( lightType == 0 )
			color += CalculatePointLight ( light );
		else if ( lightType == 1 )
			color += CalculateDirectionalLight ( light );
	}

	float alpha = texture ( u_diffuseTexture, i_texCoords ).a;

	o_color = vec4 ( color, alpha );	
}

#endshader