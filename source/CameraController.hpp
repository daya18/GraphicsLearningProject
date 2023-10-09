#pragma once

class Window;
class Camera;

class CameraController
{
public:
	CameraController ();
	CameraController ( Window &, Camera & );

	void Update ( float delta );

private:
	static constexpr float cameraMoveSensitivity { 0.006f };
	static constexpr float cameraRotationSensitivity { 0.006f };

	Window * window;
	Camera * camera;

	glm::vec3 cameraMoveDirection { 0, 0, 0 };
	glm::vec2 mouseMoveDelta { 0, 0 };
};