#include "Camera.hpp"

#include "../OpenGL/Shader.hpp"
#include "Node.hpp"

Camera::Camera ( glm::vec3 const & position, glm::vec3 const & targetDirection )
:
	position ( position ),
	targetDirection ( targetDirection ),
	viewMatrix ( glm::lookAt ( position, position + targetDirection, { 0, 1, 0 } ) ),
	projectionMatrix ( glm::perspective ( fov, viewportAspect, 0.1f, 10000.0f ) )
{
}

void Camera::SetPosition ( glm::vec3 const & position )
{
	this->position = position;
	UpdateViewMatrix ();
}

void Camera::SetTargetDirection ( glm::vec3 const & targetDirection )
{
	this->targetDirection = targetDirection;
	UpdateViewMatrix ();
}

void Camera::Move ( glm::vec3 const & delta )
{
	auto up { -glm::cross ( glm::cross ( glm::vec3 { 0.0f, 1.0f, 0.0f }, targetDirection ), targetDirection ) };

	this->position += glm::cross ( glm::vec3 { 0.0f, 1.0f, 0.0f }, targetDirection ) * delta.x;
	this->position += up * delta.y;
	this->position += targetDirection * delta.z;

	viewMatrix = glm::lookAt ( position, position + targetDirection, { 0, 1, 0 } );
}

void Camera::Rotate ( glm::vec3 const & delta )
{
	glm::vec3 newTargetDirection = glm::rotate ( targetDirection, glm::radians ( delta.x ), glm::cross ( glm::vec3 { 0.0f, 1.0f, 0.0f }, targetDirection ) );
	newTargetDirection = glm::rotate ( newTargetDirection, glm::radians ( delta.y ), glm::vec3 { 0.0f, 1.0f, 0.0f } );
	newTargetDirection = glm::rotate ( newTargetDirection, glm::radians ( delta.z ), newTargetDirection );

	if (glm::dot ( glm::abs ( newTargetDirection ), glm::vec3 { 0, 1, 0 } ) > 0.9f)
		return;

	targetDirection = newTargetDirection;

	viewMatrix = glm::lookAt ( position, position + targetDirection, { 0, 1, 0 } );
}

void Camera::SetViewportSize ( glm::uvec2 const & viewportSize )
{
	viewportAspect = static_cast <float> (viewportSize.x) / static_cast <float> (viewportSize.y);
	projectionMatrix = glm::perspective ( fov, viewportAspect, 0.1f, 10000.0f );
}

void Camera::SetFOV ( float fov )
{
	this->fov = fov;
	projectionMatrix = glm::perspective ( fov, viewportAspect, 0.1f, 10000.0f );
}

void Camera::Bind ( Shader & shader )
{
	shader.SetUniform ( "u_viewMatrix", viewMatrix );
	shader.SetUniform ( "u_projectionMatrix", projectionMatrix );
	shader.SetUniform ( "u_cameraPosition", position );
}

void Camera::Unbind ( Shader & shader )
{
	shader.SetUniform ( "u_viewMatrix", glm::identity <glm::mat4> () );
	shader.SetUniform ( "u_projectionMatrix", glm::identity <glm::mat4> () );
	shader.SetUniform ( "u_cameraPosition", glm::zero <glm::vec3> () );
}

void Camera::UpdateViewMatrix ()
{
	viewMatrix = glm::lookAt ( position, position + targetDirection, { 0, 1, 0 } );
}

void Camera::UpdateProjectionMatrix ()
{
	projectionMatrix = glm::perspective ( fov, viewportAspect, near, far );
}