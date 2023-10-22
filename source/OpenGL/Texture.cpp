#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture ()
{
	glGenTextures ( 1, &texture );
	
	Bind ();
	
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	Unbind ();
}

Texture::Texture ( std::string const & filePath )
	: Texture ()
{
	LoadFromFile ( filePath );
}

Texture::Texture ( std::vector <glm::vec4> const & data, unsigned int width )
	: Texture ()
{
	LoadFromData ( data, width );
}

Texture::Texture ( Texture && r ) noexcept
{
	operator = ( std::move ( r ) );
}

Texture::~Texture ()
{
	if ( texture )
		glDeleteTextures ( 1, &texture );
}

Texture & Texture::operator = ( Texture && r ) noexcept
{
	this->texture = std::exchange ( r.texture, 0 );
	this->size = r.size;
	return *this;
}

void Texture::Bind ( GLuint unit )
{
	glActiveTexture ( GL_TEXTURE0 + unit );
	glBindTexture ( GL_TEXTURE_2D, texture );
}

void Texture::Unbind ( GLuint unit )
{
	glActiveTexture ( GL_TEXTURE0 + unit );
	glBindTexture ( GL_TEXTURE_2D, 0 );
}

void Texture::LoadFromFile ( std::string const & filePath )
{
	Bind ();

	stbi_set_flip_vertically_on_load ( 1 );

	glm::ivec2 size { 0, 0 };
	auto data { stbi_load ( filePath.data (), &size.x, &size.y, nullptr, 4 ) };
	
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap ( GL_TEXTURE_2D );
	Unbind ();
}

void Texture::LoadFromData ( std::vector <glm::vec4> const & pixels, unsigned int width )
{
	Bind ();
	
	std::vector <GLubyte> data;
	data.reserve ( pixels.size () * 4 );

	for (auto const & pixel : pixels )
	{
		data.push_back ( pixel.r * 255 );
		data.push_back ( pixel.g * 255 );
		data.push_back ( pixel.b * 255 );
		data.push_back ( pixel.a * 255 );
	}

	unsigned int height { static_cast <unsigned int> ( pixels.size () ) / width };

	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data () );

	Unbind ();
}
