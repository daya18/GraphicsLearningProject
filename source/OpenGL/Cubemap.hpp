#pragma once

#include "../Utility.hpp"

class Cubemap
{
public:
	Cubemap ();
	Cubemap ( std::unordered_map <Sides, std::string> const & imagePaths );
	Cubemap ( Cubemap const & ) = delete;
	Cubemap ( Cubemap && ) noexcept;
	~Cubemap ();

	Cubemap & operator = ( Cubemap const & ) = delete;
	Cubemap & operator = ( Cubemap && ) noexcept;

	void Bind ( GLuint unit = 0 );
	void Unbind ( GLuint unit = 0 );

private:
	void LoadFromFile ( std::unordered_map <Sides, std::string> const & imagePaths );

	GLuint texture;
};