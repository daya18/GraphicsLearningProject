#include "Cubemap.hpp"

Cubemap::Cubemap () {}

Cubemap::Cubemap ( std::unordered_map <Sides, std::string> const & imagePaths )
{
	glGenTextures ( 1, &texture );

	Bind ();

	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	Unbind ();

	LoadFromFile ( imagePaths );
}

Cubemap::Cubemap ( Cubemap && r ) noexcept
{
	operator = ( std::move ( r ) );
}

Cubemap::~Cubemap ()
{
	if (texture)
		glDeleteTextures ( 1, &texture );
}

Cubemap & Cubemap::operator = ( Cubemap && r ) noexcept
{
	this->texture = std::exchange ( r.texture, 0 );
	return *this;
}

void Cubemap::Bind ( GLuint unit )
{
	glActiveTexture ( GL_TEXTURE0 + unit );
	glBindTexture ( GL_TEXTURE_CUBE_MAP, texture );
}

void Cubemap::Unbind ( GLuint unit )
{
	glActiveTexture ( GL_TEXTURE0 + unit );
	glBindTexture ( GL_TEXTURE_CUBE_MAP, 0 );
}

void Cubemap::LoadFromFile ( std::unordered_map <Sides, std::string> const & imagePaths )
{
	Bind ();

	std::unordered_map <GLenum, std::string> targetPaths
	{
		{ GL_TEXTURE_CUBE_MAP_POSITIVE_X, imagePaths.at ( Sides::right ) },
		{ GL_TEXTURE_CUBE_MAP_NEGATIVE_X, imagePaths.at ( Sides::left ) },
		{ GL_TEXTURE_CUBE_MAP_POSITIVE_Y, imagePaths.at ( Sides::top ) },
		{ GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, imagePaths.at ( Sides::bottom ) },
		{ GL_TEXTURE_CUBE_MAP_POSITIVE_Z, imagePaths.at ( Sides::front ) },
		{ GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, imagePaths.at ( Sides::back ) }
	};

	for ( auto const & [target, path] : targetPaths )
	{
		//stbi_set_flip_vertically_on_load ( 1 );
		glm::ivec2 size { 0, 0 };
		auto data { stbi_load ( path.data (), &size.x, &size.y, nullptr, 4 ) };
		glTexImage2D ( target, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		stbi_image_free ( data );
	}

	Unbind ();
}
