#pragma once

class Texture
{
public:
	Texture ();
	Texture ( std::string const & );
	Texture ( std::vector <glm::vec4> const &, unsigned int width );
	Texture ( Texture const & ) = delete;
	Texture ( Texture && ) noexcept;
	~Texture ();

	Texture & operator = ( Texture const & ) = delete;
	Texture & operator = ( Texture && ) noexcept;

	void Bind ( GLuint unit = 0 );
	void Unbind ( GLuint unit = 0 );

private:
	void LoadFromFile ( std::string const & );
	void LoadFromData ( std::vector <glm::vec4> const &, unsigned int width );

	glm::vec2 size { 0, 0 };
	GLuint texture { 0 };
};