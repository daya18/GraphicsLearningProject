#pragma once

class UniformBuffer;

class Shader
{
public:
	Shader ();
	Shader ( std::string const & filePath );
	Shader ( Shader const & ) = delete;
	Shader ( Shader && ) noexcept;

	~Shader ();

	Shader & operator = ( Shader && ) noexcept;
	
	void Bind ();
	void Unbind ();
	
	void SetUniform ( std::string const &, float );
	void SetUniform ( std::string const &, int );
	void SetUniform ( std::string const &, glm::mat4 const & );
	void SetUniform ( std::string const &, glm::mat3 const & );
	void SetUniform ( std::string const &, glm::vec3 const & );
	void SetUniform ( std::string const &, glm::vec4 const & );

	void BindUniformBuffer ( std::string const &, UniformBuffer & );

private:
	GLint GetUniformLocation ( std::string const & );
	GLuint GetUniformBlockIndex ( std::string const & );

	std::vector <GLuint> CreateShaders ( std::string const & filePath );

	bool CheckPreprocessorDirective ( std::string const & line, std::string const & directive );
	bool CheckPreprocessorDirective ( std::string const & line, std::string const & directive, std::string & operand );
	GLenum GetShaderType ( std::string const & );

	GLuint program { 0 };

	std::unordered_map <std::string, GLint> uniformLocations;
};