#pragma once

class Shader;
class Node;

class Camera
{
public:
	Camera ( glm::vec3 const & position = glm::vec3 { 0, 0, -1 }, glm::vec3 const & targetDirection = glm::vec3 { 0, 0, 1 } );

	void Move ( glm::vec3 const & );
	void Rotate ( glm::vec3 const & );

	void SetPosition ( glm::vec3 const & );
	void SetTargetDirection ( glm::vec3 const & targetDirection );
	void SetViewportSize ( glm::uvec2 const & );
	void SetFOV ( float );

	float GetFOV () const;

	void Bind ( Shader & shader );
	
	glm::mat4 const & GetViewMatrix () const;

private:
	void UpdateViewMatrix ();
	void UpdateProjectionMatrix ();

	float fov					{ 45.0f };
	float viewportAspect		{ 1.0f };
	float near					{ 0.1f };
	float far					{ 10000.0f };
	glm::vec3 position			{ 0, 0, 0 };
	glm::vec3 targetDirection	{ 0, 0, -1 };

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

// Implementation
inline float Camera::GetFOV () const { return fov; }
inline glm::mat4 const & Camera::GetViewMatrix () const { return viewMatrix; }
