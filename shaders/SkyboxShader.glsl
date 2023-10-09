#shader vert

#version 460

layout ( location = 0 ) in vec3 i_position;

layout ( location = 0 ) out vec3 o_texCoords;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	mat4 viewRotationScaleMatrix = mat4 ( mat3 ( u_viewMatrix ) );
	gl_Position = u_projectionMatrix * viewRotationScaleMatrix * vec4 ( i_position, 1.0f );
	o_texCoords = i_position;
}

#endshader



#shader frag

#version 460

layout ( location = 0 ) in vec3 i_texCoords;

layout ( location = 0 ) out vec4 o_color;

uniform samplerCube u_texture;

void main ()
{
	o_color = texture ( u_texture, i_texCoords );
	//o_color = vec4 ( 0.0f, 1.0f, 0.0f, 1.0f );
}

#endshader