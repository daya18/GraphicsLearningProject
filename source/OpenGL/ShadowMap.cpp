#include "ShadowMap.hpp"

ShadowMap::ShadowMap ( glm::uvec2 const & size )
{
    // Create a framebuffer object (FBO)
    glGenFramebuffers ( 1, &framebuffer );
    glBindFramebuffer ( GL_FRAMEBUFFER, framebuffer );

    // Create a texture
    glGenTextures ( 1, &texture );
    glBindTexture ( GL_TEXTURE_2D, texture );

    // Set texture parameters (you can customize these as needed)
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // Allocate memory for the texture
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );

    // Attach the texture to the framebuffer
    glFramebufferTexture2D ( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0 );

    // Check if the framebuffer is complete
    if ( glCheckFramebufferStatus ( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ) {
        std::cerr << "Framebuffer is not complete" << std::endl;
    }

    // Unbind the framebuffer and texture
    glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
    glBindTexture ( GL_TEXTURE_2D, 0 );
}

ShadowMap::ShadowMap ( ShadowMap&& r )
{
    operator = ( std::move ( r ) );
}

ShadowMap::~ShadowMap ()
{
    if ( texture )
	    glDeleteTextures ( 1, &texture );
	
    if ( framebuffer )
        glDeleteFramebuffers ( 1, &framebuffer );
}

ShadowMap & ShadowMap::operator = ( ShadowMap&& r )
{
    texture = std::exchange ( r.texture, 0 );
    framebuffer = std::exchange ( r.framebuffer, 0 );
    return *this;
}

void ShadowMap::BindFramebuffer () const
{
    glBindFramebuffer ( GL_FRAMEBUFFER, framebuffer );
}

void ShadowMap::UnbindFramebuffer () const
{
    glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
}

void ShadowMap::BindTexture () const
{
    glBindTexture ( GL_TEXTURE_2D, texture );
}

void ShadowMap::UnbindTexture () const
{
    glBindTexture ( GL_TEXTURE_2D, 0 );
}
