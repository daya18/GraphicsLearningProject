#include "Shader.hpp"

#include "UniformBuffer.hpp"

Shader::Shader ()
	: program ( 0 )
{
}

Shader::Shader ( std::string const & filePath )
{
	auto shaders { CreateShaders ( filePath ) };

	program = glCreateProgram ();
	
	for (auto shader : shaders)	
	glAttachShader ( program, shader );

	glLinkProgram ( program );
	
	for (auto shader : shaders)
		glDeleteShader ( shader );
}

Shader::Shader ( Shader && r ) noexcept
{
	operator = ( std::move ( r ) );
}

Shader::~Shader ()
{
	if ( program )
		glDeleteProgram ( program );
}

Shader & Shader::operator = ( Shader && r ) noexcept
{
	program = std::exchange ( r.program, 0 );
	return *this;
}

void Shader::Bind ()
{
	glUseProgram ( program );
}

void Shader::Unbind ()
{
	glUseProgram ( 0 );
}

void Shader::SetUniform ( std::string const & name, float val )
{
	Bind ();
	glUniform1f ( GetUniformLocation ( name ), val );
}

void Shader::SetUniform ( std::string const & name, int val )
{
	Bind ();
	glUniform1i ( GetUniformLocation ( name ), val );
}

void Shader::SetUniform ( std::string const & name, glm::mat4 const & matrix )
{
	Bind ();

	glUniformMatrix4fv ( 
		GetUniformLocation ( name ),
		1,
		GL_FALSE,
		glm::value_ptr ( matrix )
	);
}

void Shader::SetUniform ( std::string const & name, glm::mat3 const & matrix )
{
	Bind ();

	glUniformMatrix3fv (
		GetUniformLocation ( name ),
		1,
		GL_FALSE,
		glm::value_ptr ( matrix )
	);
}

void Shader::SetUniform ( std::string const & name, glm::vec3 const & vec )
{
	Bind ();
	glUniform3f ( GetUniformLocation ( name ), vec.x, vec.y, vec.z );
}

void Shader::SetUniform ( std::string const & name, glm::vec4 const & vec )
{
	Bind ();
	glUniform4f ( GetUniformLocation ( name ), vec.x, vec.y, vec.z, vec.w );
}

void Shader::BindUniformBuffer ( std::string const & name, UniformBuffer & uniformBuffer )
{
	auto blockIndex { GetUniformBlockIndex ( name ) };
	glUniformBlockBinding ( program, blockIndex, blockIndex );
	glBindBufferBase ( GL_UNIFORM_BUFFER, blockIndex, uniformBuffer.uniformBuffer );
}

std::vector <GLuint> Shader::CreateShaders ( std::string const & filePath )
{
	std::vector <GLuint> shaders;

	std::ifstream file { filePath };

	std::string currentShaderType;
	std::ostringstream currentShaderStream;

	while (file.good ())
	{
		std::string line;
		std::getline ( file, line );

		if (CheckPreprocessorDirective ( line, "#shader", currentShaderType ))
			continue;

		if (CheckPreprocessorDirective ( line, "#endshader" ))
		{
			shaders.push_back ( glCreateShader ( GetShaderType ( currentShaderType ) ) );

			std::string source { currentShaderStream.str () };
			GLint length { static_cast <GLint> (source.size ()) };
			GLchar * data { source.data () };
			
			glShaderSource ( shaders.back(), 1, &data, &length );
			glCompileShader ( shaders.back () );
			
			currentShaderStream = {};

			continue;
		}

		currentShaderStream << line << std::endl;
	}

	return shaders;
}

bool Shader::CheckPreprocessorDirective ( std::string const & line, std::string const & directive )
{
	return line.substr ( 0, directive.size () ) == directive;
}

bool Shader::CheckPreprocessorDirective ( std::string const & line, std::string const & directive, std::string & operand )
{
	if ( line.substr ( 0, directive.size () ) == directive )
	{
		operand = line.substr ( directive.size () + 1 );
		return true;
	}

	return false;
}

GLenum Shader::GetShaderType ( std::string const & type )
{
	return
		  type == "vert" ? GL_VERTEX_SHADER
		: type == "frag" ? GL_FRAGMENT_SHADER
		: throw std::runtime_error { "Unknown shader type: " + type };
}


GLint Shader::GetUniformLocation ( std::string const & name )
{
	return glGetUniformLocation ( program, name.data () );
}

GLuint Shader::GetUniformBlockIndex ( std::string const & name )
{
	return glGetUniformBlockIndex ( program, name.data () );
}
