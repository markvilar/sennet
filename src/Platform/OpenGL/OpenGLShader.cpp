#include <Sennet/pch.hpp>
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Sennet
{

OpenGLShader::OpenGLShader(const std::string& vertexSrc, 
	const std::string& fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(max_length);
		glGetShaderInfoLog(vertexShader, max_length, &max_length, 
			&infoLog[0]);
		
		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		SN_CORE_ERROR("{0}", infoLog.data());
		SN_CORE_ASSERT(false, "Vertex shader compilation failure!")
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(max_length);
		glGetShaderInfoLog(fragmentShader, max_length, &max_length, 
			&infoLog[0]);
		
		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		SN_CORE_ERROR("{0}", infoLog.data());
		SN_CORE_ASSERT(false, "Fragment shader compilation failure!")
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link our program
	glLinkProgram(m_RendererID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint is_linked = 0;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&is_linked);
	if (is_linked == GL_FALSE)
	{
		GLint max_length = 0;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &max_length);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(max_length);
		glGetProgramInfoLog(m_RendererID, max_length, &max_length, 
			&infoLog[0]);
		
		// We don't need the program anymore.
		glDeleteProgram(m_RendererID);

		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		SN_CORE_ERROR("{0}", infoLog.data());
		SN_CORE_ASSERT(false, "Shader link failure!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_RendererID, vertexShader);
	glDetachShader(m_RendererID, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
	glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const
{
	glUseProgram(0);
}

void OpenGLShader::UploadUniformInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}

void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string& name, 
	const glm::vec2& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform2f(location, values.x, values.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string& name, 
	const glm::vec3& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, values.x, values.y, values.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string& name, 
	const glm::vec4& values)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, values.x, values.y, values.z, values.w);
}

void OpenGLShader::UploadUniformMat3(const std::string& name, 
	const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string& name, 
	const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

}
