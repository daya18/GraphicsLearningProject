#shader vert

#version 460

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec4 i_color;
layout ( location = 2 ) in vec3 i_normal;
layout ( location = 3 ) in vec2 i_texCoords;

layout ( location = 0 ) out vec2 o_texCoords;

uniform vec3 u_position;
uniform float u_scale;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	vec3 positionModelSpace = ( u_scale * i_position ) + u_position;
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4 ( positionModelSpace, 1.0f );
	o_texCoords = i_texCoords;
}

#endshader



#shader frag

#version 460

layout ( location = 0 ) in vec2 i_texCoords;

layout ( location = 0 ) out vec4 o_color;

uniform vec4 u_color;
uniform vec3 u_cameraPosition;
uniform sampler2D u_texture;

void main ()
{
	vec4 textureColor = texture ( u_texture, i_texCoords );

	//if ( textureColor.r != 1.0 )
	//	o_color = vec4 ( 1.0f, 0.0f, 0.0f, 1.0f );
	//else
	//	o_color = vec4 ( 0.0f, 1.0f, 0.0f, 1.0f );

	o_color = vec4 ( vec3 ( textureColor.r ), 1.0f );
}

#endshader