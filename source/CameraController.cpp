#include "CameraController.hpp"

#include "Window.hpp"
#include "Scene/Camera.hpp"

CameraController::CameraController () {}

CameraController::CameraController ( Window & window, Camera & camera )
	: window ( &window ), camera ( &camera )
{
	// Bind event listeners
	window.keyDownEvent.AddListener ( [this]( int key )
		{
			switch (key)
			{
			case GLFW_KEY_D: this->cameraMoveDirection.x -= 1.0f; break;
			case GLFW_KEY_A: this->cameraMoveDirection.x += 1.0f; break;
			case GLFW_KEY_W: this->cameraMoveDirection.z += 1.0f; break;
			case GLFW_KEY_S: this->cameraMoveDirection.z -= 1.0f; break;
			case GLFW_KEY_SPACE: this->cameraMoveDirection.y += 1.0f; break;
			case GLFW_KEY_LEFT_SHIFT: this->cameraMoveDirection.y -= 1.0f; break;
			}
		}
	);

	window.keyUpEvent.AddListener ( [this]( int key )
		{
			switch (key)
			{
			case GLFW_KEY_D: this->cameraMoveDirection.x += 1.0f; break;
			case GLFW_KEY_A: this->cameraMoveDirection.x -= 1.0f; break;
			case GLFW_KEY_W: this->cameraMoveDirection.z -= 1.0f; break;
			case GLFW_KEY_S: this->cameraMoveDirection.z += 1.0f; break;
			case GLFW_KEY_SPACE: this->cameraMoveDirection.y -= 1.0f; break;
			case GLFW_KEY_LEFT_SHIFT: this->cameraMoveDirection.y += 1.0f; break;
			}
		}
	);

	window.cursorMoveEvent.AddListener ( [this, &window]( glm::vec2 delta )
		{
			if (window.GetMouseButton ( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS)
				mouseMoveDelta = delta;
		}
	);

	window.framebufferResizeEvent.AddListener ( [this]( glm::vec2 size )
		{
			this->camera->SetViewportSize ( size );
		}
	);
}

void CameraController::Update ( float delta )
{
	if (cameraMoveDirection != glm::zero <glm::vec3> ())
		camera->Move ( glm::normalize ( cameraMoveDirection ) * cameraMoveSensitivity * delta );

	if ( mouseMoveDelta != glm::zero <glm::vec2> ())
	{
		this->camera->Rotate ( glm::vec3 { mouseMoveDelta.y, -mouseMoveDelta.x, 0 } *cameraRotationSensitivity * delta );
		mouseMoveDelta = glm::zero <glm::vec2> ();
	}
}