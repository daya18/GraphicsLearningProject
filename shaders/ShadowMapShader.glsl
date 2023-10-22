#shader vert

#version 460

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec4 i_color;
layout ( location = 2 ) in vec3 i_normal;
layout ( location = 3 ) in vec2 i_texCoords;

uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4 ( i_position, 1.0f );
}

#endshader



#shader frag

#version 460

uniform vec3 u_cameraPosition;

void main ()
{
}

#endshader