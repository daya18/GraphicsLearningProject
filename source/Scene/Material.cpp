#include "Material.hpp"

#include "../OpenGL/Shader.hpp"
#include "Scene.hpp"
#include "../Utility.hpp"

Material::Material ( std::filesystem::path textureDirectoryPath, aiMaterial & material )
{
	aiString name;
	material.Get ( AI_MATKEY_NAME, name );
	//std::cout << "Material: " << name.C_Str () << std::endl;
	//<< " *********";
	//
	//for (int i = 0; i < material.mNumProperties; ++i)
	//{
	//	std::cout << material.mProperties[i]->mKey.C_Str () << std::endl;
	//}
	//
	//std::cout << "******************************" << std::endl << std::endl;
	

	// Get ambient color
	aiColor3D ambientColor; material.Get ( AI_MATKEY_COLOR_AMBIENT, ambientColor );
	this->ambientColor = { ambientColor.r, ambientColor.g, ambientColor.b, 1.0f };
	
	// Get diffuse color
	aiColor3D diffuseColor; material.Get ( AI_MATKEY_COLOR_DIFFUSE, diffuseColor );
	this->diffuseColor = { diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0f };
	
	// Get specular color
	aiColor3D specularColor; material.Get ( AI_MATKEY_COLOR_SPECULAR, specularColor );
	this->specularColor = { specularColor.r, specularColor.g, specularColor.b, 1.0f };

	material.Get ( AI_MATKEY_SHININESS, shininess );
	material.Get ( AI_MATKEY_SHININESS_STRENGTH, shininessStrength );

	ambientTexture = Texture { { Colors::white }, 1 };
	diffuseTexture = Texture { { Colors::white }, 1 };
	
	// Ambient texture
	if (material.GetTextureCount ( aiTextureType_AMBIENT ) == 1)
	{
		aiString relPath;
		aiTextureMapping mapping;
		unsigned int uvIndex;
		material.GetTexture ( aiTextureType_AMBIENT, 0, &relPath, &mapping, &uvIndex );
		

		if (relPath.length != 0)
		{
			auto path { textureDirectoryPath / relPath.C_Str () };

			if (std::filesystem::exists ( path ))
				ambientTexture = Texture { path.string () };
		}
	}

	// Diffuse texture
	if ( material.GetTextureCount ( aiTextureType_DIFFUSE ) == 1 )
	{
		aiString relPath;
		aiTextureMapping mapping;
		unsigned int uvIndex;

		material.GetTexture ( aiTextureType_DIFFUSE, 0, &relPath, &mapping, &uvIndex );
		
		if ( relPath.length != 0 )
		{
			auto path { textureDirectoryPath / relPath.C_Str () };

			if ( std::filesystem::exists ( path ) )
				diffuseTexture = Texture { path.string () };
		}
	}

}

void Material::Bind ( Shader & shader )
{
	shader.SetUniform ( "u_ambientColor", ambientColor );
	shader.SetUniform ( "u_diffuseColor", diffuseColor );
	shader.SetUniform ( "u_specularColor", specularColor );
	
	shader.SetUniform ( "u_shininess", shininess * shininessStrength );

	// Ambient Texture
	shader.SetUniform ( "u_ambientTexture", 0 );
	ambientTexture.Bind ( 0 );

	// Diffuse Texture
	shader.SetUniform ( "u_diffuseTexture", 1 );
	diffuseTexture.Bind ( 1 );
}