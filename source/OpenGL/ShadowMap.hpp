#pragma once

class ShadowMap
{
public:
	ShadowMap ( glm::uvec2 const & size );

	ShadowMap ( ShadowMap const & ) = delete;
	ShadowMap ( ShadowMap && );

	~ShadowMap ();

	ShadowMap & operator = ( ShadowMap const & ) = delete;
	ShadowMap & operator = ( ShadowMap && );

	void BindFramebuffer () const;
	void UnbindFramebuffer () const;

	void BindTexture () const;
	void UnbindTexture () const;

	GLuint texture;
private:
	GLuint framebuffer;
};