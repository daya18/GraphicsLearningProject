#pragma once

#include "../OpenGL/Texture.hpp"

class Scene;
class Shader;

class Material
{
public:
	Material ( std::filesystem::path textureDirectoryPath, aiMaterial & );

	void Bind ( Shader & );

private:
	glm::vec4 GetColor ( aiMaterial &, char const * key );

	glm::vec4 ambientColor { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 diffuseColor { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 specularColor { 1.0f, 1.0f, 1.0f, 1.0f };

	float shininess { 0 };
	float shininessStrength { 0 };

	Texture ambientTexture;
	Texture diffuseTexture;
};